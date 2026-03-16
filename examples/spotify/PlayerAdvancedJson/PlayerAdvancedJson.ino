#include <SpotifyExampleSupport.h>
#include <SpotifyJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-transfer-playback-json-docs[]
constexpr char kTransferPlaybackJsonValue[] = "{\"device_ids\":[\"device-id\"],\"play\":true}";

void sendSpotifyTransferPlaybackJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.player.transfer", kTransferPlaybackJsonValue, body)) {
    Serial.println("Unable to build spotify.player.transfer request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.player.transfer");
}

void handleSpotifyTransferPlaybackJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.player.transfer.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.player.transfer response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.player.transfer.response payload");
    return;
  }

  if (kTransferPlaybackJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kTransferPlaybackJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-transfer-playback-json-docs[]

// tag::spotify-seek-to-position-json-docs[]
constexpr char kSeekToPositionJsonValue[] = "position_ms=120000";

void sendSpotifySeekToPositionJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.player.seek", kSeekToPositionJsonValue, body)) {
    Serial.println("Unable to build spotify.player.seek request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.player.seek");
}

void handleSpotifySeekToPositionJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.player.seek.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.player.seek response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.player.seek.response payload");
    return;
  }

  if (kSeekToPositionJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kSeekToPositionJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-seek-to-position-json-docs[]

// tag::spotify-get-recently-played-tracks-json-docs[]
constexpr char kGetRecentlyPlayedTracksJsonValue[] = "limit=5";

void sendSpotifyGetRecentlyPlayedTracksJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.player.recently-played", kGetRecentlyPlayedTracksJsonValue, body)) {
    Serial.println("Unable to build spotify.player.recently-played request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.player.recently-played");
}

void handleSpotifyGetRecentlyPlayedTracksJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.player.recently-played.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.player.recently-played response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.player.recently-played.response payload");
    return;
  }

  if (kGetRecentlyPlayedTracksJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetRecentlyPlayedTracksJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-recently-played-tracks-json-docs[]

// tag::spotify-get-the-users-queue-json-docs[]
constexpr char kGetTheUsersQueueJsonValue[] = "";

void sendSpotifyGetTheUsersQueueJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.player.queue.get", kGetTheUsersQueueJsonValue, body)) {
    Serial.println("Unable to build spotify.player.queue.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.player.queue.get");
}

void handleSpotifyGetTheUsersQueueJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.player.queue.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.player.queue.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.player.queue.get.response payload");
    return;
  }

  if (kGetTheUsersQueueJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetTheUsersQueueJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-the-users-queue-json-docs[]

// tag::spotify-add-item-to-playback-queue-json-docs[]
constexpr char kAddItemToPlaybackQueueJsonValue[] = "uri=spotify:track:track-id";

void sendSpotifyAddItemToPlaybackQueueJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.player.queue.add", kAddItemToPlaybackQueueJsonValue, body)) {
    Serial.println("Unable to build spotify.player.queue.add request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.player.queue.add");
}

void handleSpotifyAddItemToPlaybackQueueJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.player.queue.add.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.player.queue.add response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.player.queue.add.response payload");
    return;
  }

  if (kAddItemToPlaybackQueueJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kAddItemToPlaybackQueueJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-add-item-to-playback-queue-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyTransferPlaybackJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyTransferPlaybackJsonResponse(payload, length);
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
