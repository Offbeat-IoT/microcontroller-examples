#include <SpotifyCborExampleSupport.h>
#include <SpotifyExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-artist-cbor-docs[]
constexpr char kGetArtistCborValue[] = "artist-id";

void sendSpotifyGetArtistCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.artists.get", kGetArtistCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.artists.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.artists.get");
}

void handleSpotifyGetArtistCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.artists.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.artists.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.artists.get.response payload");
    return;
  }

  if (kGetArtistCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetArtistCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-artist-cbor-docs[]

// tag::spotify-get-several-artists-cbor-docs[]
constexpr char kGetSeveralArtistsCborValue[] = "ids=artist-1,artist-2";

void sendSpotifyGetSeveralArtistsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.artists.get.several", kGetSeveralArtistsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.artists.get.several request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.artists.get.several");
}

void handleSpotifyGetSeveralArtistsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.artists.get.several.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.artists.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.artists.get.several.response payload");
    return;
  }

  if (kGetSeveralArtistsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralArtistsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-artists-cbor-docs[]

// tag::spotify-get-artists-albums-cbor-docs[]
constexpr char kGetArtistsAlbumsCborValue[] = "artist-id";

void sendSpotifyGetArtistsAlbumsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.artists.albums", kGetArtistsAlbumsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.artists.albums request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.artists.albums");
}

void handleSpotifyGetArtistsAlbumsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.artists.albums.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.artists.albums response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.artists.albums.response payload");
    return;
  }

  if (kGetArtistsAlbumsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetArtistsAlbumsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-artists-albums-cbor-docs[]

// tag::spotify-get-artists-top-tracks-cbor-docs[]
constexpr char kGetArtistsTopTracksCborValue[] = "artist-id/top-tracks?market=US";

void sendSpotifyGetArtistsTopTracksCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.artists.top-tracks", kGetArtistsTopTracksCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.artists.top-tracks request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.artists.top-tracks");
}

void handleSpotifyGetArtistsTopTracksCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.artists.top-tracks.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.artists.top-tracks response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.artists.top-tracks.response payload");
    return;
  }

  if (kGetArtistsTopTracksCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetArtistsTopTracksCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-artists-top-tracks-cbor-docs[]

// tag::spotify-get-artists-related-artists-cbor-docs[]
constexpr char kGetArtistsRelatedArtistsCborValue[] = "artist-id";

void sendSpotifyGetArtistsRelatedArtistsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.artists.related", kGetArtistsRelatedArtistsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.artists.related request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.artists.related");
}

void handleSpotifyGetArtistsRelatedArtistsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.artists.related.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.artists.related response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.artists.related.response payload");
    return;
  }

  if (kGetArtistsRelatedArtistsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetArtistsRelatedArtistsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-artists-related-artists-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetArtistCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyGetArtistCborResponse(payload, length);
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
