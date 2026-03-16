#include <SpotifyCborExampleSupport.h>
#include <SpotifyExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-episode-cbor-docs[]
constexpr char kGetEpisodeCborValue[] = "episode-id";

void sendSpotifyGetEpisodeCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.episodes.get", kGetEpisodeCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.episodes.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.episodes.get");
}

void handleSpotifyGetEpisodeCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.episodes.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.episodes.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.episodes.get.response payload");
    return;
  }

  if (kGetEpisodeCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetEpisodeCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-episode-cbor-docs[]

// tag::spotify-get-several-episodes-cbor-docs[]
constexpr char kGetSeveralEpisodesCborValue[] = "ids=episode-1,episode-2";

void sendSpotifyGetSeveralEpisodesCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.episodes.get.several", kGetSeveralEpisodesCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.episodes.get.several request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.episodes.get.several");
}

void handleSpotifyGetSeveralEpisodesCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.episodes.get.several.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.episodes.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.episodes.get.several.response payload");
    return;
  }

  if (kGetSeveralEpisodesCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralEpisodesCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-episodes-cbor-docs[]

// tag::spotify-get-users-saved-episodes-cbor-docs[]
constexpr char kGetUsersSavedEpisodesCborValue[] = "limit=1";

void sendSpotifyGetUsersSavedEpisodesCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.episodes.saved.get", kGetUsersSavedEpisodesCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.episodes.saved.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.episodes.saved.get");
}

void handleSpotifyGetUsersSavedEpisodesCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.episodes.saved.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.episodes.saved.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.episodes.saved.get.response payload");
    return;
  }

  if (kGetUsersSavedEpisodesCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersSavedEpisodesCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-saved-episodes-cbor-docs[]

// tag::spotify-save-episodes-for-current-user-cbor-docs[]
constexpr char kSaveEpisodesForCurrentUserCborValue[] = "[\"episode-id\"]";

void sendSpotifySaveEpisodesForCurrentUserCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.episodes.saved.save", kSaveEpisodesForCurrentUserCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.episodes.saved.save request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.episodes.saved.save");
}

void handleSpotifySaveEpisodesForCurrentUserCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.episodes.saved.save.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.episodes.saved.save response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.episodes.saved.save.response payload");
    return;
  }

  if (kSaveEpisodesForCurrentUserCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kSaveEpisodesForCurrentUserCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-save-episodes-for-current-user-cbor-docs[]

// tag::spotify-remove-users-saved-episodes-cbor-docs[]
constexpr char kRemoveUsersSavedEpisodesCborValue[] = "[\"episode-id\"]";

void sendSpotifyRemoveUsersSavedEpisodesCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.episodes.saved.remove", kRemoveUsersSavedEpisodesCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.episodes.saved.remove request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.episodes.saved.remove");
}

void handleSpotifyRemoveUsersSavedEpisodesCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.episodes.saved.remove.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.episodes.saved.remove response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.episodes.saved.remove.response payload");
    return;
  }

  if (kRemoveUsersSavedEpisodesCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kRemoveUsersSavedEpisodesCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-remove-users-saved-episodes-cbor-docs[]

// tag::spotify-check-users-saved-episodes-cbor-docs[]
constexpr char kCheckUsersSavedEpisodesCborValue[] = "ids=episode-id";

void sendSpotifyCheckUsersSavedEpisodesCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.episodes.saved.check", kCheckUsersSavedEpisodesCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.episodes.saved.check request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.episodes.saved.check");
}

void handleSpotifyCheckUsersSavedEpisodesCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.episodes.saved.check.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.episodes.saved.check response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.episodes.saved.check.response payload");
    return;
  }

  if (kCheckUsersSavedEpisodesCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckUsersSavedEpisodesCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-users-saved-episodes-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetEpisodeCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyGetEpisodeCborResponse(payload, length);
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
