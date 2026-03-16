#include <SpotifyExampleSupport.h>
#include <SpotifyJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-show-json-docs[]
constexpr char kGetShowJsonValue[] = "show-id";

void sendSpotifyGetShowJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.shows.get", kGetShowJsonValue, body)) {
    Serial.println("Unable to build spotify.shows.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.shows.get");
}

void handleSpotifyGetShowJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.shows.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.get.response payload");
    return;
  }

  if (kGetShowJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetShowJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-show-json-docs[]

// tag::spotify-get-several-shows-json-docs[]
constexpr char kGetSeveralShowsJsonValue[] = "ids=show-1,show-2";

void sendSpotifyGetSeveralShowsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.shows.get.several", kGetSeveralShowsJsonValue, body)) {
    Serial.println("Unable to build spotify.shows.get.several request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.shows.get.several");
}

void handleSpotifyGetSeveralShowsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.shows.get.several.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.get.several.response payload");
    return;
  }

  if (kGetSeveralShowsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralShowsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-shows-json-docs[]

// tag::spotify-get-show-episodes-json-docs[]
constexpr char kGetShowEpisodesJsonValue[] = "show-id/episodes?market=US";

void sendSpotifyGetShowEpisodesJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.shows.episodes", kGetShowEpisodesJsonValue, body)) {
    Serial.println("Unable to build spotify.shows.episodes request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.shows.episodes");
}

void handleSpotifyGetShowEpisodesJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.shows.episodes.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.episodes response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.episodes.response payload");
    return;
  }

  if (kGetShowEpisodesJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetShowEpisodesJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-show-episodes-json-docs[]

// tag::spotify-get-users-saved-shows-json-docs[]
constexpr char kGetUsersSavedShowsJsonValue[] = "limit=3";

void sendSpotifyGetUsersSavedShowsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.shows.saved.get", kGetUsersSavedShowsJsonValue, body)) {
    Serial.println("Unable to build spotify.shows.saved.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.shows.saved.get");
}

void handleSpotifyGetUsersSavedShowsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.shows.saved.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.saved.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.saved.get.response payload");
    return;
  }

  if (kGetUsersSavedShowsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersSavedShowsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-saved-shows-json-docs[]

// tag::spotify-save-shows-for-current-user-json-docs[]
constexpr char kSaveShowsForCurrentUserJsonValue[] = "[\"show-id\"]";

void sendSpotifySaveShowsForCurrentUserJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.shows.saved.save", kSaveShowsForCurrentUserJsonValue, body)) {
    Serial.println("Unable to build spotify.shows.saved.save request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.shows.saved.save");
}

void handleSpotifySaveShowsForCurrentUserJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.shows.saved.save.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.saved.save response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.saved.save.response payload");
    return;
  }

  if (kSaveShowsForCurrentUserJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kSaveShowsForCurrentUserJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-save-shows-for-current-user-json-docs[]

// tag::spotify-remove-users-saved-shows-json-docs[]
constexpr char kRemoveUsersSavedShowsJsonValue[] = "[\"show-id\"]";

void sendSpotifyRemoveUsersSavedShowsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.shows.saved.remove", kRemoveUsersSavedShowsJsonValue, body)) {
    Serial.println("Unable to build spotify.shows.saved.remove request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.shows.saved.remove");
}

void handleSpotifyRemoveUsersSavedShowsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.shows.saved.remove.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.saved.remove response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.saved.remove.response payload");
    return;
  }

  if (kRemoveUsersSavedShowsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kRemoveUsersSavedShowsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-remove-users-saved-shows-json-docs[]

// tag::spotify-check-users-saved-shows-json-docs[]
constexpr char kCheckUsersSavedShowsJsonValue[] = "ids=show-id";

void sendSpotifyCheckUsersSavedShowsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.shows.saved.check", kCheckUsersSavedShowsJsonValue, body)) {
    Serial.println("Unable to build spotify.shows.saved.check request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.shows.saved.check");
}

void handleSpotifyCheckUsersSavedShowsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.shows.saved.check.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.shows.saved.check response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.shows.saved.check.response payload");
    return;
  }

  if (kCheckUsersSavedShowsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckUsersSavedShowsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-users-saved-shows-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetShowJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyGetShowJsonResponse(payload, length);
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
