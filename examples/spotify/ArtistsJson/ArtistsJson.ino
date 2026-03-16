#include <SpotifyExampleSupport.h>
#include <SpotifyJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-artist-json-docs[]
constexpr char kGetArtistJsonValue[] = "artist-id";

void sendSpotifyGetArtistJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.artists.get", kGetArtistJsonValue, body)) {
    Serial.println("Unable to build spotify.artists.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.artists.get");
}

void handleSpotifyGetArtistJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.artists.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.artists.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.artists.get.response payload");
    return;
  }

  if (kGetArtistJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetArtistJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-artist-json-docs[]

// tag::spotify-get-several-artists-json-docs[]
constexpr char kGetSeveralArtistsJsonValue[] = "ids=artist-1,artist-2";

void sendSpotifyGetSeveralArtistsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.artists.get.several", kGetSeveralArtistsJsonValue, body)) {
    Serial.println("Unable to build spotify.artists.get.several request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.artists.get.several");
}

void handleSpotifyGetSeveralArtistsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.artists.get.several.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.artists.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.artists.get.several.response payload");
    return;
  }

  if (kGetSeveralArtistsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralArtistsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-artists-json-docs[]

// tag::spotify-get-artists-albums-json-docs[]
constexpr char kGetArtistsAlbumsJsonValue[] = "artist-id";

void sendSpotifyGetArtistsAlbumsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.artists.albums", kGetArtistsAlbumsJsonValue, body)) {
    Serial.println("Unable to build spotify.artists.albums request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.artists.albums");
}

void handleSpotifyGetArtistsAlbumsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.artists.albums.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.artists.albums response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.artists.albums.response payload");
    return;
  }

  if (kGetArtistsAlbumsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetArtistsAlbumsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-artists-albums-json-docs[]

// tag::spotify-get-artists-top-tracks-json-docs[]
constexpr char kGetArtistsTopTracksJsonValue[] = "artist-id/top-tracks?market=US";

void sendSpotifyGetArtistsTopTracksJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.artists.top-tracks", kGetArtistsTopTracksJsonValue, body)) {
    Serial.println("Unable to build spotify.artists.top-tracks request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.artists.top-tracks");
}

void handleSpotifyGetArtistsTopTracksJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.artists.top-tracks.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.artists.top-tracks response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.artists.top-tracks.response payload");
    return;
  }

  if (kGetArtistsTopTracksJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetArtistsTopTracksJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-artists-top-tracks-json-docs[]

// tag::spotify-get-artists-related-artists-json-docs[]
constexpr char kGetArtistsRelatedArtistsJsonValue[] = "artist-id";

void sendSpotifyGetArtistsRelatedArtistsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.artists.related", kGetArtistsRelatedArtistsJsonValue, body)) {
    Serial.println("Unable to build spotify.artists.related request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.artists.related");
}

void handleSpotifyGetArtistsRelatedArtistsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.artists.related.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.artists.related response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.artists.related.response payload");
    return;
  }

  if (kGetArtistsRelatedArtistsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetArtistsRelatedArtistsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-artists-related-artists-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetArtistJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyGetArtistJsonResponse(payload, length);
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
