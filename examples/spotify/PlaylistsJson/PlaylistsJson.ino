#include <SpotifyExampleSupport.h>
#include <SpotifyJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-playlist-json-docs[]
constexpr char kGetPlaylistJsonValue[] = "playlist-id";

void sendSpotifyGetPlaylistJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.get", kGetPlaylistJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.get");
}

void handleSpotifyGetPlaylistJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.get.response payload");
    return;
  }

  if (kGetPlaylistJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetPlaylistJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-playlist-json-docs[]

// tag::spotify-change-playlist-details-json-docs[]
constexpr char kChangePlaylistDetailsJsonValue[] = "playlist-id||{\"name\":\"Road Trip\"}";

void sendSpotifyChangePlaylistDetailsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.change-details", kChangePlaylistDetailsJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.change-details request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.change-details");
}

void handleSpotifyChangePlaylistDetailsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.change-details.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.change-details response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.change-details.response payload");
    return;
  }

  if (kChangePlaylistDetailsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kChangePlaylistDetailsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-change-playlist-details-json-docs[]

// tag::spotify-get-playlist-items-json-docs[]
constexpr char kGetPlaylistItemsJsonValue[] = "playlist-id/tracks?limit=10";

void sendSpotifyGetPlaylistItemsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.items.get", kGetPlaylistItemsJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.items.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.items.get");
}

void handleSpotifyGetPlaylistItemsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.items.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.items.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.items.get.response payload");
    return;
  }

  if (kGetPlaylistItemsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetPlaylistItemsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-playlist-items-json-docs[]

// tag::spotify-update-playlist-items-json-docs[]
constexpr char kUpdatePlaylistItemsJsonValue[] = "playlist-id||{\"uris\":[\"spotify:track:1\"]}";

void sendSpotifyUpdatePlaylistItemsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.items.update", kUpdatePlaylistItemsJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.items.update request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.items.update");
}

void handleSpotifyUpdatePlaylistItemsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.items.update.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.items.update response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.items.update.response payload");
    return;
  }

  if (kUpdatePlaylistItemsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kUpdatePlaylistItemsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-update-playlist-items-json-docs[]

// tag::spotify-add-items-to-playlist-json-docs[]
constexpr char kAddItemsToPlaylistJsonValue[] = "playlist-id||{\"uris\":[\"spotify:track:1\"]}";

void sendSpotifyAddItemsToPlaylistJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.items.add", kAddItemsToPlaylistJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.items.add request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.items.add");
}

void handleSpotifyAddItemsToPlaylistJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.items.add.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.items.add response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.items.add.response payload");
    return;
  }

  if (kAddItemsToPlaylistJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kAddItemsToPlaylistJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-add-items-to-playlist-json-docs[]

// tag::spotify-remove-playlist-items-json-docs[]
constexpr char kRemovePlaylistItemsJsonValue[] = "playlist-id||{\"tracks\":[{\"uri\":\"spotify:track:1\"}]}";

void sendSpotifyRemovePlaylistItemsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.items.remove", kRemovePlaylistItemsJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.items.remove request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.items.remove");
}

void handleSpotifyRemovePlaylistItemsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.items.remove.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.items.remove response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.items.remove.response payload");
    return;
  }

  if (kRemovePlaylistItemsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kRemovePlaylistItemsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-remove-playlist-items-json-docs[]

// tag::spotify-get-current-users-playlists-json-docs[]
constexpr char kGetCurrentUsersPlaylistsJsonValue[] = "limit=5";

void sendSpotifyGetCurrentUsersPlaylistsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.current-user.get", kGetCurrentUsersPlaylistsJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.current-user.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.current-user.get");
}

void handleSpotifyGetCurrentUsersPlaylistsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.current-user.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.current-user.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.current-user.get.response payload");
    return;
  }

  if (kGetCurrentUsersPlaylistsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetCurrentUsersPlaylistsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-current-users-playlists-json-docs[]

// tag::spotify-get-users-playlists-json-docs[]
constexpr char kGetUsersPlaylistsJsonValue[] = "user-id/playlists?limit=5";

void sendSpotifyGetUsersPlaylistsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.user.get", kGetUsersPlaylistsJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.user.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.user.get");
}

void handleSpotifyGetUsersPlaylistsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.user.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.user.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.user.get.response payload");
    return;
  }

  if (kGetUsersPlaylistsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersPlaylistsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-playlists-json-docs[]

// tag::spotify-create-playlist-json-docs[]
constexpr char kCreatePlaylistJsonValue[] = "user-id||{\"name\":\"Chill\"}";

void sendSpotifyCreatePlaylistJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.create", kCreatePlaylistJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.create request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.create");
}

void handleSpotifyCreatePlaylistJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.create.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.create response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.create.response payload");
    return;
  }

  if (kCreatePlaylistJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCreatePlaylistJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-create-playlist-json-docs[]

// tag::spotify-get-featured-playlists-json-docs[]
constexpr char kGetFeaturedPlaylistsJsonValue[] = "country=US";

void sendSpotifyGetFeaturedPlaylistsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.featured.get", kGetFeaturedPlaylistsJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.featured.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.featured.get");
}

void handleSpotifyGetFeaturedPlaylistsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.featured.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.featured.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.featured.get.response payload");
    return;
  }

  if (kGetFeaturedPlaylistsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetFeaturedPlaylistsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-featured-playlists-json-docs[]

// tag::spotify-get-categories-playlists-json-docs[]
constexpr char kGetCategoriesPlaylistsJsonValue[] = "category-id/playlists?limit=10";

void sendSpotifyGetCategoriesPlaylistsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.category.get", kGetCategoriesPlaylistsJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.category.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.category.get");
}

void handleSpotifyGetCategoriesPlaylistsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.category.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.category.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.category.get.response payload");
    return;
  }

  if (kGetCategoriesPlaylistsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetCategoriesPlaylistsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-categories-playlists-json-docs[]

// tag::spotify-get-playlist-cover-image-json-docs[]
constexpr char kGetPlaylistCoverImageJsonValue[] = "playlist-id";

void sendSpotifyGetPlaylistCoverImageJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.cover.get", kGetPlaylistCoverImageJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.cover.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.cover.get");
}

void handleSpotifyGetPlaylistCoverImageJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.cover.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.cover.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.cover.get.response payload");
    return;
  }

  if (kGetPlaylistCoverImageJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetPlaylistCoverImageJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-playlist-cover-image-json-docs[]

// tag::spotify-add-custom-playlist-cover-image-json-docs[]
constexpr char kAddCustomPlaylistCoverImageJsonValue[] = "playlist-id||BASE64DATA";

void sendSpotifyAddCustomPlaylistCoverImageJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.playlists.cover.add", kAddCustomPlaylistCoverImageJsonValue, body)) {
    Serial.println("Unable to build spotify.playlists.cover.add request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.playlists.cover.add");
}

void handleSpotifyAddCustomPlaylistCoverImageJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<8192> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.playlists.cover.add.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.cover.add response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.cover.add.response payload");
    return;
  }

  if (kAddCustomPlaylistCoverImageJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kAddCustomPlaylistCoverImageJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-add-custom-playlist-cover-image-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetPlaylistJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyGetPlaylistJsonResponse(payload, length);
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
