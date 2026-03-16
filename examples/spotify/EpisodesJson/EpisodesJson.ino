#include <SpotifyExampleSupport.h>
#include <SpotifyJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-episode-json-docs[]
constexpr char kGetEpisodeJsonValue[] = "episode-id";

void sendSpotifyGetEpisodeJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.episodes.get", kGetEpisodeJsonValue, body)) {
    Serial.println("Unable to build spotify.episodes.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.episodes.get");
}

void handleSpotifyGetEpisodeJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.episodes.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.episodes.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.episodes.get.response payload");
    return;
  }

  if (kGetEpisodeJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetEpisodeJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-episode-json-docs[]

// tag::spotify-get-several-episodes-json-docs[]
constexpr char kGetSeveralEpisodesJsonValue[] = "ids=episode-1,episode-2";

void sendSpotifyGetSeveralEpisodesJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.episodes.get.several", kGetSeveralEpisodesJsonValue, body)) {
    Serial.println("Unable to build spotify.episodes.get.several request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.episodes.get.several");
}

void handleSpotifyGetSeveralEpisodesJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.episodes.get.several.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.episodes.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.episodes.get.several.response payload");
    return;
  }

  if (kGetSeveralEpisodesJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralEpisodesJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-episodes-json-docs[]

// tag::spotify-get-users-saved-episodes-json-docs[]
constexpr char kGetUsersSavedEpisodesJsonValue[] = "limit=1";

void sendSpotifyGetUsersSavedEpisodesJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.episodes.saved.get", kGetUsersSavedEpisodesJsonValue, body)) {
    Serial.println("Unable to build spotify.episodes.saved.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.episodes.saved.get");
}

void handleSpotifyGetUsersSavedEpisodesJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.episodes.saved.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.episodes.saved.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.episodes.saved.get.response payload");
    return;
  }

  if (kGetUsersSavedEpisodesJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersSavedEpisodesJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-saved-episodes-json-docs[]

// tag::spotify-save-episodes-for-current-user-json-docs[]
constexpr char kSaveEpisodesForCurrentUserJsonValue[] = "[\"episode-id\"]";

void sendSpotifySaveEpisodesForCurrentUserJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.episodes.saved.save", kSaveEpisodesForCurrentUserJsonValue, body)) {
    Serial.println("Unable to build spotify.episodes.saved.save request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.episodes.saved.save");
}

void handleSpotifySaveEpisodesForCurrentUserJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.episodes.saved.save.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.episodes.saved.save response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.episodes.saved.save.response payload");
    return;
  }

  if (kSaveEpisodesForCurrentUserJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kSaveEpisodesForCurrentUserJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-save-episodes-for-current-user-json-docs[]

// tag::spotify-remove-users-saved-episodes-json-docs[]
constexpr char kRemoveUsersSavedEpisodesJsonValue[] = "[\"episode-id\"]";

void sendSpotifyRemoveUsersSavedEpisodesJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.episodes.saved.remove", kRemoveUsersSavedEpisodesJsonValue, body)) {
    Serial.println("Unable to build spotify.episodes.saved.remove request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.episodes.saved.remove");
}

void handleSpotifyRemoveUsersSavedEpisodesJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.episodes.saved.remove.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.episodes.saved.remove response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.episodes.saved.remove.response payload");
    return;
  }

  if (kRemoveUsersSavedEpisodesJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kRemoveUsersSavedEpisodesJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-remove-users-saved-episodes-json-docs[]

// tag::spotify-check-users-saved-episodes-json-docs[]
constexpr char kCheckUsersSavedEpisodesJsonValue[] = "ids=episode-id";

void sendSpotifyCheckUsersSavedEpisodesJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.episodes.saved.check", kCheckUsersSavedEpisodesJsonValue, body)) {
    Serial.println("Unable to build spotify.episodes.saved.check request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.episodes.saved.check");
}

void handleSpotifyCheckUsersSavedEpisodesJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.episodes.saved.check.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.episodes.saved.check response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.episodes.saved.check.response payload");
    return;
  }

  if (kCheckUsersSavedEpisodesJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckUsersSavedEpisodesJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-users-saved-episodes-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetEpisodeJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyGetEpisodeJsonResponse(payload, length);
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
