#include <SpotifyExampleSupport.h>
#include <SpotifyJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-album-json-docs[]
constexpr char kGetAlbumJsonValue[] = "album-id";

void sendSpotifyGetAlbumJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.albums.get", kGetAlbumJsonValue, body)) {
    Serial.println("Unable to build spotify.albums.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.albums.get");
}

void handleSpotifyGetAlbumJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.albums.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.albums.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.albums.get.response payload");
    return;
  }

  if (kGetAlbumJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetAlbumJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-album-json-docs[]

// tag::spotify-get-several-albums-json-docs[]
constexpr char kGetSeveralAlbumsJsonValue[] = "ids=album-1,album-2";

void sendSpotifyGetSeveralAlbumsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.albums.get.several", kGetSeveralAlbumsJsonValue, body)) {
    Serial.println("Unable to build spotify.albums.get.several request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.albums.get.several");
}

void handleSpotifyGetSeveralAlbumsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.albums.get.several.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.albums.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.albums.get.several.response payload");
    return;
  }

  if (kGetSeveralAlbumsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralAlbumsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-albums-json-docs[]

// tag::spotify-get-album-tracks-json-docs[]
constexpr char kGetAlbumTracksJsonValue[] = "album-id";

void sendSpotifyGetAlbumTracksJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.albums.tracks", kGetAlbumTracksJsonValue, body)) {
    Serial.println("Unable to build spotify.albums.tracks request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.albums.tracks");
}

void handleSpotifyGetAlbumTracksJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.albums.tracks.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.albums.tracks response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.albums.tracks.response payload");
    return;
  }

  if (kGetAlbumTracksJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetAlbumTracksJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-album-tracks-json-docs[]

// tag::spotify-get-users-saved-albums-json-docs[]
constexpr char kGetUsersSavedAlbumsJsonValue[] = "limit=2";

void sendSpotifyGetUsersSavedAlbumsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.albums.saved.get", kGetUsersSavedAlbumsJsonValue, body)) {
    Serial.println("Unable to build spotify.albums.saved.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.albums.saved.get");
}

void handleSpotifyGetUsersSavedAlbumsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.albums.saved.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.albums.saved.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.albums.saved.get.response payload");
    return;
  }

  if (kGetUsersSavedAlbumsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersSavedAlbumsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-saved-albums-json-docs[]

// tag::spotify-save-albums-for-current-user-json-docs[]
constexpr char kSaveAlbumsForCurrentUserJsonValue[] = "[\"album-id\"]";

void sendSpotifySaveAlbumsForCurrentUserJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.albums.saved.save", kSaveAlbumsForCurrentUserJsonValue, body)) {
    Serial.println("Unable to build spotify.albums.saved.save request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.albums.saved.save");
}

void handleSpotifySaveAlbumsForCurrentUserJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.albums.saved.save.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.albums.saved.save response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.albums.saved.save.response payload");
    return;
  }

  if (kSaveAlbumsForCurrentUserJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kSaveAlbumsForCurrentUserJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-save-albums-for-current-user-json-docs[]

// tag::spotify-remove-users-saved-albums-json-docs[]
constexpr char kRemoveUsersSavedAlbumsJsonValue[] = "[\"album-id\"]";

void sendSpotifyRemoveUsersSavedAlbumsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.albums.saved.remove", kRemoveUsersSavedAlbumsJsonValue, body)) {
    Serial.println("Unable to build spotify.albums.saved.remove request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.albums.saved.remove");
}

void handleSpotifyRemoveUsersSavedAlbumsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.albums.saved.remove.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.albums.saved.remove response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.albums.saved.remove.response payload");
    return;
  }

  if (kRemoveUsersSavedAlbumsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kRemoveUsersSavedAlbumsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-remove-users-saved-albums-json-docs[]

// tag::spotify-check-users-saved-albums-json-docs[]
constexpr char kCheckUsersSavedAlbumsJsonValue[] = "ids=album-id";

void sendSpotifyCheckUsersSavedAlbumsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.albums.saved.check", kCheckUsersSavedAlbumsJsonValue, body)) {
    Serial.println("Unable to build spotify.albums.saved.check request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.albums.saved.check");
}

void handleSpotifyCheckUsersSavedAlbumsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.albums.saved.check.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.albums.saved.check response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.albums.saved.check.response payload");
    return;
  }

  if (kCheckUsersSavedAlbumsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckUsersSavedAlbumsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-users-saved-albums-json-docs[]

// tag::spotify-get-new-releases-json-docs[]
constexpr char kGetNewReleasesJsonValue[] = "country=US";

void sendSpotifyGetNewReleasesJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.albums.new-releases", kGetNewReleasesJsonValue, body)) {
    Serial.println("Unable to build spotify.albums.new-releases request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.albums.new-releases");
}

void handleSpotifyGetNewReleasesJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.albums.new-releases.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.albums.new-releases response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.albums.new-releases.response payload");
    return;
  }

  if (kGetNewReleasesJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetNewReleasesJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-new-releases-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetAlbumJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyGetAlbumJsonResponse(payload, length);
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
