#include <SpotifyCborExampleSupport.h>
#include <SpotifyExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-transfer-playback-cbor-docs[]
constexpr char kTransferPlaybackCborValue[] = "{\"device_ids\":[\"device-id\"],\"play\":true}";

void sendSpotifyTransferPlaybackCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.player.transfer", kTransferPlaybackCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.player.transfer request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.player.transfer");
}

void handleSpotifyTransferPlaybackCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.player.transfer.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.player.transfer response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.player.transfer.response payload");
    return;
  }

  if (kTransferPlaybackCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kTransferPlaybackCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-transfer-playback-cbor-docs[]

// tag::spotify-seek-to-position-cbor-docs[]
constexpr char kSeekToPositionCborValue[] = "position_ms=120000";

void sendSpotifySeekToPositionCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.player.seek", kSeekToPositionCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.player.seek request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.player.seek");
}

void handleSpotifySeekToPositionCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.player.seek.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.player.seek response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.player.seek.response payload");
    return;
  }

  if (kSeekToPositionCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kSeekToPositionCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-seek-to-position-cbor-docs[]

// tag::spotify-get-recently-played-tracks-cbor-docs[]
constexpr char kGetRecentlyPlayedTracksCborValue[] = "limit=5";

void sendSpotifyGetRecentlyPlayedTracksCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.player.recently-played", kGetRecentlyPlayedTracksCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.player.recently-played request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.player.recently-played");
}

void handleSpotifyGetRecentlyPlayedTracksCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.player.recently-played.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.player.recently-played response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.player.recently-played.response payload");
    return;
  }

  if (kGetRecentlyPlayedTracksCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetRecentlyPlayedTracksCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-recently-played-tracks-cbor-docs[]

// tag::spotify-get-the-users-queue-cbor-docs[]
constexpr char kGetTheUsersQueueCborValue[] = "";

void sendSpotifyGetTheUsersQueueCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.player.queue.get", kGetTheUsersQueueCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.player.queue.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.player.queue.get");
}

void handleSpotifyGetTheUsersQueueCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.player.queue.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.player.queue.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.player.queue.get.response payload");
    return;
  }

  if (kGetTheUsersQueueCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetTheUsersQueueCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-the-users-queue-cbor-docs[]

// tag::spotify-add-item-to-playback-queue-cbor-docs[]
constexpr char kAddItemToPlaybackQueueCborValue[] = "uri=spotify:track:track-id";

void sendSpotifyAddItemToPlaybackQueueCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.player.queue.add", kAddItemToPlaybackQueueCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.player.queue.add request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.player.queue.add");
}

void handleSpotifyAddItemToPlaybackQueueCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.player.queue.add.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.player.queue.add response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.player.queue.add.response payload");
    return;
  }

  if (kAddItemToPlaybackQueueCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kAddItemToPlaybackQueueCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-add-item-to-playback-queue-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyTransferPlaybackCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyTransferPlaybackCborResponse(payload, length);
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
