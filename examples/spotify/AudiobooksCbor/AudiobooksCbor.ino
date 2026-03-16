#include <SpotifyCborExampleSupport.h>
#include <SpotifyExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-an-audiobook-cbor-docs[]
constexpr char kGetAnAudiobookCborValue[] = "audiobook-id";

void sendSpotifyGetAnAudiobookCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.audiobooks.get", kGetAnAudiobookCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.audiobooks.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.audiobooks.get");
}

void handleSpotifyGetAnAudiobookCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.audiobooks.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.get.response payload");
    return;
  }

  if (kGetAnAudiobookCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetAnAudiobookCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-an-audiobook-cbor-docs[]

// tag::spotify-get-several-audiobooks-cbor-docs[]
constexpr char kGetSeveralAudiobooksCborValue[] = "ids=book-1,book-2";

void sendSpotifyGetSeveralAudiobooksCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.audiobooks.get.several", kGetSeveralAudiobooksCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.audiobooks.get.several request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.audiobooks.get.several");
}

void handleSpotifyGetSeveralAudiobooksCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.audiobooks.get.several.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.get.several.response payload");
    return;
  }

  if (kGetSeveralAudiobooksCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralAudiobooksCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-audiobooks-cbor-docs[]

// tag::spotify-get-audiobook-chapters-cbor-docs[]
constexpr char kGetAudiobookChaptersCborValue[] = "audiobook-id";

void sendSpotifyGetAudiobookChaptersCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.audiobooks.chapters", kGetAudiobookChaptersCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.audiobooks.chapters request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.audiobooks.chapters");
}

void handleSpotifyGetAudiobookChaptersCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.audiobooks.chapters.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.chapters response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.chapters.response payload");
    return;
  }

  if (kGetAudiobookChaptersCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetAudiobookChaptersCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-audiobook-chapters-cbor-docs[]

// tag::spotify-get-users-saved-audiobooks-cbor-docs[]
constexpr char kGetUsersSavedAudiobooksCborValue[] = "limit=5";

void sendSpotifyGetUsersSavedAudiobooksCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.audiobooks.saved.get", kGetUsersSavedAudiobooksCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.audiobooks.saved.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.audiobooks.saved.get");
}

void handleSpotifyGetUsersSavedAudiobooksCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.audiobooks.saved.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.saved.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.saved.get.response payload");
    return;
  }

  if (kGetUsersSavedAudiobooksCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersSavedAudiobooksCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-saved-audiobooks-cbor-docs[]

// tag::spotify-save-audiobooks-for-current-user-cbor-docs[]
constexpr char kSaveAudiobooksForCurrentUserCborValue[] = "[\"audiobook-id\"]";

void sendSpotifySaveAudiobooksForCurrentUserCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.audiobooks.saved.save", kSaveAudiobooksForCurrentUserCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.audiobooks.saved.save request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.audiobooks.saved.save");
}

void handleSpotifySaveAudiobooksForCurrentUserCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.audiobooks.saved.save.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.saved.save response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.saved.save.response payload");
    return;
  }

  if (kSaveAudiobooksForCurrentUserCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kSaveAudiobooksForCurrentUserCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-save-audiobooks-for-current-user-cbor-docs[]

// tag::spotify-remove-users-saved-audiobooks-cbor-docs[]
constexpr char kRemoveUsersSavedAudiobooksCborValue[] = "[\"audiobook-id\"]";

void sendSpotifyRemoveUsersSavedAudiobooksCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.audiobooks.saved.remove", kRemoveUsersSavedAudiobooksCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.audiobooks.saved.remove request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.audiobooks.saved.remove");
}

void handleSpotifyRemoveUsersSavedAudiobooksCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.audiobooks.saved.remove.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.saved.remove response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.saved.remove.response payload");
    return;
  }

  if (kRemoveUsersSavedAudiobooksCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kRemoveUsersSavedAudiobooksCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-remove-users-saved-audiobooks-cbor-docs[]

// tag::spotify-check-users-saved-audiobooks-cbor-docs[]
constexpr char kCheckUsersSavedAudiobooksCborValue[] = "ids=audiobook-id";

void sendSpotifyCheckUsersSavedAudiobooksCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.audiobooks.saved.check", kCheckUsersSavedAudiobooksCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.audiobooks.saved.check request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.audiobooks.saved.check");
}

void handleSpotifyCheckUsersSavedAudiobooksCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.audiobooks.saved.check.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.saved.check response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.saved.check.response payload");
    return;
  }

  if (kCheckUsersSavedAudiobooksCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckUsersSavedAudiobooksCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-users-saved-audiobooks-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetAnAudiobookCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyGetAnAudiobookCborResponse(payload, length);
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("TEST:READY");
  if (!offbeat::spotify::examples::connectWifi(OFFBEAT_WIFI_SSID, OFFBEAT_WIFI_PASSWORD)) {
    return;
  }

  webSocket.begin(OFFBEAT_WS_HOST, OFFBEAT_WS_PORT, OFFBEAT_WS_PATH);
  webSocket.onEvent(websocketEvent);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();
}
