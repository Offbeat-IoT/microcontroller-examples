#pragma once

#include <Arduino.h>

namespace offbeat::camera::examples {

// The device asks for this protocol on the WebSocket upgrade request:
//   X-Offbeat-Camera-Stream: chunked-v1
// The server accepts only that exact token and confirms it in the handshake response.
constexpr const char* kChunkedV1 = "chunked-v1";

// Text message the server sends once the connection negotiated chunked-v1:
//   {"cameraStream":"chunked-v1"}
// The Arduino WebSockets client does not expose the upgrade response headers on
// WStype_CONNECTED, so the in-band confirmation is what the device can check.
constexpr const char* kStreamKey = "cameraStream";

// Ends an agreed stream. The server discards any partially buffered image, so a device sends
// this before it switches back to whole-JPEG messages.
constexpr const char* kEndStreamJson = "{\"cameraStream\":null}";

// One chunk has to fit the server's camera.stream.max-chunk-bytes (32768) and a whole image its
// camera.stream.max-image-bytes (262144). The defaults below stay well inside both bounds.
constexpr size_t kDefaultChunkBytes = 4096;
constexpr size_t kMaxChunkBytes = 32768;
constexpr size_t kMaxChunks = 128;
constexpr size_t kMaxImageBytes = 256UL * 1024UL;

// Every chunkCount consecutive binary messages are one image, so the device has to know the
// chunk count of the frame it is about to send.
inline size_t chunkCountFor(size_t imageBytes, size_t chunkBytes) {
  if (chunkBytes == 0) {
    return 0;
  }
  return (imageBytes + chunkBytes - 1) / chunkBytes;
}

// Writes {"cameraStream":{"chunkSize":N,"chunkCount":M}} and returns the length written.
inline size_t buildAgreement(char* buffer, size_t capacity, size_t chunkBytes, size_t chunkCount) {
  int written = snprintf(buffer, capacity,
                         "{\"cameraStream\":{\"chunkSize\":%u,\"chunkCount\":%u}}",
                         static_cast<unsigned>(chunkBytes), static_cast<unsigned>(chunkCount));
  if (written < 0) {
    return 0;
  }
  return static_cast<size_t>(written) < capacity ? static_cast<size_t>(written) : 0;
}

// The server validates the agreement before accepting any chunk, so the device only offers
// framings it knows the server accepts.
inline bool fitsServerLimits(size_t imageBytes, size_t chunkBytes) {
  if (imageBytes == 0 || chunkBytes == 0 || chunkBytes > kMaxChunkBytes) {
    return false;
  }
  size_t chunkCount = chunkCountFor(imageBytes, chunkBytes);
  return chunkCount <= kMaxChunks && chunkBytes * chunkCount <= kMaxImageBytes;
}

inline bool hasKey(const String& message, const char* key) {
  return message.indexOf(String("\"") + key + "\"") >= 0;
}

// True for {"cameraStream":"chunked-v1"}.
inline bool isChunkedConfirmation(const String& message) {
  int key = message.indexOf(String("\"") + kStreamKey + "\"");
  if (key < 0) {
    return false;
  }
  return message.indexOf(kChunkedV1, key) > key;
}

// True for {"cameraStream":null} - the end-of-stream marker the server also accepts from a
// device. Kept here so a sketch never confuses it with a confirmation.
inline bool isEndOfStream(const String& message) {
  int key = message.indexOf(String("\"") + kStreamKey + "\"");
  if (key < 0) {
    return false;
  }
  return message.indexOf("null", key) > key;
}

}  // namespace offbeat::camera::examples
