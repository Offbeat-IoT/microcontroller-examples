#include <SpotifyCborExampleSupport.h>
#include <SpotifyExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-show-cbor-docs[]
constexpr char kGetShowCborValue[] = "show-id";

void sendSpotifyGetShowCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.shows.get", kGetShowCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.shows.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.shows.get");
}

void handleSpotifyGetShowCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.shows.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.get.response payload");
    return;
  }

  if (kGetShowCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetShowCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-show-cbor-docs[]

// tag::spotify-get-several-shows-cbor-docs[]
constexpr char kGetSeveralShowsCborValue[] = "ids=show-1,show-2";

void sendSpotifyGetSeveralShowsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.shows.get.several", kGetSeveralShowsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.shows.get.several request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.shows.get.several");
}

void handleSpotifyGetSeveralShowsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.shows.get.several.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.get.several.response payload");
    return;
  }

  if (kGetSeveralShowsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralShowsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-shows-cbor-docs[]

// tag::spotify-get-show-episodes-cbor-docs[]
constexpr char kGetShowEpisodesCborValue[] = "show-id/episodes?market=US";

void sendSpotifyGetShowEpisodesCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.shows.episodes", kGetShowEpisodesCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.shows.episodes request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.shows.episodes");
}

void handleSpotifyGetShowEpisodesCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.shows.episodes.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.episodes response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.episodes.response payload");
    return;
  }

  if (kGetShowEpisodesCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetShowEpisodesCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-show-episodes-cbor-docs[]

// tag::spotify-get-users-saved-shows-cbor-docs[]
constexpr char kGetUsersSavedShowsCborValue[] = "limit=3";

void sendSpotifyGetUsersSavedShowsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.shows.saved.get", kGetUsersSavedShowsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.shows.saved.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.shows.saved.get");
}

void handleSpotifyGetUsersSavedShowsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.shows.saved.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.saved.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.saved.get.response payload");
    return;
  }

  if (kGetUsersSavedShowsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersSavedShowsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-saved-shows-cbor-docs[]

// tag::spotify-save-shows-for-current-user-cbor-docs[]
constexpr char kSaveShowsForCurrentUserCborValue[] = "[\"show-id\"]";

void sendSpotifySaveShowsForCurrentUserCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.shows.saved.save", kSaveShowsForCurrentUserCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.shows.saved.save request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.shows.saved.save");
}

void handleSpotifySaveShowsForCurrentUserCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.shows.saved.save.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.saved.save response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.saved.save.response payload");
    return;
  }

  if (kSaveShowsForCurrentUserCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kSaveShowsForCurrentUserCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-save-shows-for-current-user-cbor-docs[]

// tag::spotify-remove-users-saved-shows-cbor-docs[]
constexpr char kRemoveUsersSavedShowsCborValue[] = "[\"show-id\"]";

void sendSpotifyRemoveUsersSavedShowsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.shows.saved.remove", kRemoveUsersSavedShowsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.shows.saved.remove request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.shows.saved.remove");
}

void handleSpotifyRemoveUsersSavedShowsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.shows.saved.remove.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.saved.remove response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.saved.remove.response payload");
    return;
  }

  if (kRemoveUsersSavedShowsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kRemoveUsersSavedShowsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-remove-users-saved-shows-cbor-docs[]

// tag::spotify-check-users-saved-shows-cbor-docs[]
constexpr char kCheckUsersSavedShowsCborValue[] = "ids=show-id";

void sendSpotifyCheckUsersSavedShowsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.shows.saved.check", kCheckUsersSavedShowsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.shows.saved.check request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.shows.saved.check");
}

void handleSpotifyCheckUsersSavedShowsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.shows.saved.check.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.saved.check response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.saved.check.response payload");
    return;
  }

  if (kCheckUsersSavedShowsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckUsersSavedShowsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-users-saved-shows-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetShowCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyGetShowCborResponse(payload, length);
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
