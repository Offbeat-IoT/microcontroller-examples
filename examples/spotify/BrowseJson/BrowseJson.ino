#include <SpotifyExampleSupport.h>
#include <SpotifyJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-several-browse-categories-json-docs[]
constexpr char kGetSeveralBrowseCategoriesJsonValue[] = "country=US";

void sendSpotifyGetSeveralBrowseCategoriesJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.categories.get", kGetSeveralBrowseCategoriesJsonValue, body)) {
    Serial.println("Unable to build spotify.categories.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.categories.get");
}

void handleSpotifyGetSeveralBrowseCategoriesJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.categories.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.categories.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.categories.get.response payload");
    return;
  }

  if (kGetSeveralBrowseCategoriesJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralBrowseCategoriesJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-browse-categories-json-docs[]

// tag::spotify-get-single-browse-category-json-docs[]
constexpr char kGetSingleBrowseCategoryJsonValue[] = "category-id";

void sendSpotifyGetSingleBrowseCategoryJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.categories.get.single", kGetSingleBrowseCategoryJsonValue, body)) {
    Serial.println("Unable to build spotify.categories.get.single request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.categories.get.single");
}

void handleSpotifyGetSingleBrowseCategoryJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.categories.get.single.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.categories.get.single response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.categories.get.single.response payload");
    return;
  }

  if (kGetSingleBrowseCategoryJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSingleBrowseCategoryJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-single-browse-category-json-docs[]

// tag::spotify-get-available-genre-seeds-json-docs[]
constexpr char kGetAvailableGenreSeedsJsonValue[] = "";

void sendSpotifyGetAvailableGenreSeedsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.genres.seeds.get", kGetAvailableGenreSeedsJsonValue, body)) {
    Serial.println("Unable to build spotify.genres.seeds.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.genres.seeds.get");
}

void handleSpotifyGetAvailableGenreSeedsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.genres.seeds.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.genres.seeds.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.genres.seeds.get.response payload");
    return;
  }

  if (kGetAvailableGenreSeedsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetAvailableGenreSeedsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-available-genre-seeds-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetSeveralBrowseCategoriesJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyGetSeveralBrowseCategoriesJsonResponse(payload, length);
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
