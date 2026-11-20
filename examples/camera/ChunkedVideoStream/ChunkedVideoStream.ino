// Streams JPEG frames from an ESP32-CAM to Offbeat with the chunked camera protocol.
//
// One image is sent as several complete binary WebSocket messages: every `chunkCount`
// consecutive messages are one image, in order, and only the last chunk is allowed to be
// shorter than `chunkSize`. WebSocket fragmentation cannot do this - fragments reassemble into
// one message and cannot interleave with control traffic - so the device writes chunk by chunk
// and runs the WebSocket loop in between. That is what lets `startVideo` / `stopVideo` (and
// keep-alive pings) be handled in the middle of an image instead of after it.
//
// The device asks for the protocol on the upgrade request and only sends agreements once the
// server has confirmed it. An older server that does not confirm keeps working unchanged: the
// sketch falls back to one binary message per whole JPEG.

#include <WiFi.h>
#include <WebSocketsClient.h>
#include <esp_camera.h>

#include <CameraChunkedStreamExampleSupport.h>

#include "offbeat_test_config.h"

#ifndef OFFBEAT_CAMERA_CHUNK_BYTES
#define OFFBEAT_CAMERA_CHUNK_BYTES 4096
#endif

const size_t kChunkBytes = OFFBEAT_CAMERA_CHUNK_BYTES;
const uint32_t kDefaultFps = 5;
const uint32_t kMinFps = 1;
const uint32_t kMaxFps = 20;

WebSocketsClient webSocket;

bool chunkedConfirmed = false;
bool videoStreaming = false;
size_t agreedChunkCount = 0;
uint32_t frameIntervalMs = 1000UL / kDefaultFps;
unsigned long lastFrameAt = 0;

// tag::camera-chunked-stream-docs[]
// Opt into the protocol on the upgrade request. It is negotiated per connection, so this has to
// be set again after a reconnect and the confirmation has to be awaited again.
void requestChunkedStream() {
  webSocket.setExtraHeaders("X-Offbeat-Camera-Stream: chunked-v1");
}

// The server sends {"cameraStream":"chunked-v1"} as a text message once the connection
// negotiated the protocol. Without it, binary messages still mean "one whole JPEG".
bool handleCameraControl(const String& message) {
  if (offbeat::camera::examples::isChunkedConfirmation(message)) {
    chunkedConfirmed = true;
    Serial.println("SERVER_CONFIRMED_CHUNKED_STREAM");
    return true;
  }

  if (offbeat::camera::examples::hasKey(message, "startVideo")) {
    startVideo(message);
    return true;
  }

  if (offbeat::camera::examples::hasKey(message, "stopVideo")) {
    videoStreaming = false;
    agreedChunkCount = 0;
    Serial.println("VIDEO_STOPPED");
    return true;
  }

  return false;
}

// Sends one JPEG as several complete binary messages. The agreement is positional and stays in
// effect until it is replaced, so it is only sent when this frame needs a different chunk count
// than the previous one. `webSocket.loop()` runs between writes so control traffic arriving
// mid-image is answered immediately; the current image is still finished, which keeps the
// server's framing in step.
bool sendChunkedFrame(camera_fb_t* frame) {
  size_t chunkCount = offbeat::camera::examples::chunkCountFor(frame->len, kChunkBytes);
  if (chunkCount == 0) {
    return false;
  }

  if (chunkCount != agreedChunkCount) {
    char agreement[96];
    if (offbeat::camera::examples::buildAgreement(agreement, sizeof(agreement), kChunkBytes, chunkCount) == 0) {
      return false;
    }
    if (!webSocket.sendTXT(agreement)) {
      agreedChunkCount = 0;
      return false;
    }
    agreedChunkCount = chunkCount;
    Serial.print("STREAM_AGREEMENT=");
    Serial.println(agreement);
  }

  for (size_t offset = 0; offset < frame->len; offset += kChunkBytes) {
    size_t remaining = frame->len - offset;
    size_t length = remaining < kChunkBytes ? remaining : kChunkBytes;
    if (!webSocket.sendBIN(frame->buf + offset, length)) {
      // The server still expects the rest of this image, so drop the agreement instead of
      // leaving its framing out of step with ours.
      agreedChunkCount = 0;
      return false;
    }
    webSocket.loop();
  }

  Serial.print("FRAME_COMPLETED_BYTES=");
  Serial.println(static_cast<unsigned>(frame->len));
  return true;
}
// end::camera-chunked-stream-docs[]

uint32_t jsonIntValue(const String& message, const char* key, uint32_t fallback) {
  int keyAt = message.indexOf(String("\"") + key + "\"");
  if (keyAt < 0) {
    return fallback;
  }
  int colon = message.indexOf(':', keyAt);
  if (colon < 0) {
    return fallback;
  }
  int valueAt = colon + 1;
  while (valueAt < static_cast<int>(message.length()) && message[valueAt] == ' ') {
    valueAt++;
  }
  int start = valueAt;
  while (valueAt < static_cast<int>(message.length()) && isDigit(message[valueAt])) {
    valueAt++;
  }
  if (valueAt == start) {
    return fallback;
  }
  return message.substring(start, valueAt).toInt();
}

void startVideo(const String& message) {
  uint32_t fps = jsonIntValue(message, "fps", kDefaultFps);
  fps = fps < kMinFps ? kMinFps : (fps > kMaxFps ? kMaxFps : fps);
  frameIntervalMs = 1000UL / fps;
  lastFrameAt = 0;
  videoStreaming = true;
  Serial.print("VIDEO_STARTED_FPS=");
  Serial.println(static_cast<unsigned>(fps));
}

void sendFrame() {
  camera_fb_t* frame = esp_camera_fb_get();
  if (frame == nullptr) {
    Serial.println("CAMERA_CAPTURE_FAILED");
    return;
  }

  bool chunked = chunkedConfirmed &&
                 offbeat::camera::examples::fitsServerLimits(frame->len, kChunkBytes);
  if (chunked) {
    sendChunkedFrame(frame);
  } else if (!webSocket.sendBIN(frame->buf, frame->len)) {
    Serial.println("WHOLE_FRAME_SEND_FAILED");
  }

  esp_camera_fb_return(frame);
}

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  (void)length;
  switch (type) {
    case WStype_CONNECTED:
      // The WebSockets client reports the request URL here, not the upgrade response headers,
      // so the confirmation of X-Offbeat-Camera-Stream: chunked-v1 arrives as a text message.
      chunkedConfirmed = false;
      agreedChunkCount = 0;
      Serial.println("WS_CONNECTED_WAITING_FOR_CHUNKED_CONFIRMATION");
      break;
    case WStype_DISCONNECTED:
      chunkedConfirmed = false;
      agreedChunkCount = 0;
      videoStreaming = false;
      Serial.println("WS_DISCONNECTED");
      break;
    case WStype_TEXT:
      Serial.print("WS_TEXT=");
      Serial.println(reinterpret_cast<char*>(payload));
      handleCameraControl(String(reinterpret_cast<char*>(payload)));
      break;
    default:
      break;
  }
}

bool initCamera() {
  camera_config_t config = {};
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_VGA;
  config.jpeg_quality = 12;
  config.fb_count = psramFound() ? 2 : 1;

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("CAMERA_INIT_FAILED");
    return false;
  }
  return true;
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("TEST:READY");

  if (!initCamera()) {
    return;
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(OFFBEAT_WIFI_SSID, OFFBEAT_WIFI_PASSWORD);
  Serial.print("WIFI_CONNECTING");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WIFI_CONNECTED");

  requestChunkedStream();
  webSocket.beginSSL(OFFBEAT_WS_HOST, OFFBEAT_WS_PORT, OFFBEAT_WS_PATH);
  webSocket.onEvent(websocketEvent);
  webSocket.setReconnectInterval(5000);
  webSocket.enableHeartbeat(10000, 15000, 2);
}

void loop() {
  webSocket.loop();

  if (!videoStreaming || !webSocket.isConnected()) {
    return;
  }

  unsigned long now = millis();
  if (lastFrameAt != 0 && now - lastFrameAt < frameIntervalMs) {
    return;
  }
  lastFrameAt = now;
  sendFrame();
}
