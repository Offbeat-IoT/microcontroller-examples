#include <SpotifyCborExampleSupport.h>
#include <SpotifyExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-playlist-cbor-docs[]
constexpr char kGetPlaylistCborValue[] = "playlist-id";

void sendSpotifyGetPlaylistCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.get", kGetPlaylistCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.get");
}

void handleSpotifyGetPlaylistCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.get.response payload");
    return;
  }

  if (kGetPlaylistCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetPlaylistCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-playlist-cbor-docs[]

// tag::spotify-change-playlist-details-cbor-docs[]
constexpr char kChangePlaylistDetailsCborValue[] = "playlist-id||{\"name\":\"Road Trip\"}";

void sendSpotifyChangePlaylistDetailsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.change-details", kChangePlaylistDetailsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.change-details request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.change-details");
}

void handleSpotifyChangePlaylistDetailsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.change-details.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.change-details response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.change-details.response payload");
    return;
  }

  if (kChangePlaylistDetailsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kChangePlaylistDetailsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-change-playlist-details-cbor-docs[]

// tag::spotify-get-playlist-items-cbor-docs[]
constexpr char kGetPlaylistItemsCborValue[] = "playlist-id/tracks?limit=10";

void sendSpotifyGetPlaylistItemsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.items.get", kGetPlaylistItemsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.items.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.items.get");
}

void handleSpotifyGetPlaylistItemsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.items.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.items.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.items.get.response payload");
    return;
  }

  if (kGetPlaylistItemsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetPlaylistItemsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-playlist-items-cbor-docs[]

// tag::spotify-update-playlist-items-cbor-docs[]
constexpr char kUpdatePlaylistItemsCborValue[] = "playlist-id||{\"uris\":[\"spotify:track:1\"]}";

void sendSpotifyUpdatePlaylistItemsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.items.update", kUpdatePlaylistItemsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.items.update request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.items.update");
}

void handleSpotifyUpdatePlaylistItemsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.items.update.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.items.update response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.items.update.response payload");
    return;
  }

  if (kUpdatePlaylistItemsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kUpdatePlaylistItemsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-update-playlist-items-cbor-docs[]

// tag::spotify-add-items-to-playlist-cbor-docs[]
constexpr char kAddItemsToPlaylistCborValue[] = "playlist-id||{\"uris\":[\"spotify:track:1\"]}";

void sendSpotifyAddItemsToPlaylistCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.items.add", kAddItemsToPlaylistCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.items.add request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.items.add");
}

void handleSpotifyAddItemsToPlaylistCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.items.add.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.items.add response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.items.add.response payload");
    return;
  }

  if (kAddItemsToPlaylistCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kAddItemsToPlaylistCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-add-items-to-playlist-cbor-docs[]

// tag::spotify-remove-playlist-items-cbor-docs[]
constexpr char kRemovePlaylistItemsCborValue[] = "playlist-id||{\"tracks\":[{\"uri\":\"spotify:track:1\"}]}";

void sendSpotifyRemovePlaylistItemsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.items.remove", kRemovePlaylistItemsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.items.remove request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.items.remove");
}

void handleSpotifyRemovePlaylistItemsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.items.remove.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.items.remove response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.items.remove.response payload");
    return;
  }

  if (kRemovePlaylistItemsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kRemovePlaylistItemsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-remove-playlist-items-cbor-docs[]

// tag::spotify-get-current-users-playlists-cbor-docs[]
constexpr char kGetCurrentUsersPlaylistsCborValue[] = "limit=5";

void sendSpotifyGetCurrentUsersPlaylistsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.current-user.get", kGetCurrentUsersPlaylistsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.current-user.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.current-user.get");
}

void handleSpotifyGetCurrentUsersPlaylistsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.current-user.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.current-user.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.current-user.get.response payload");
    return;
  }

  if (kGetCurrentUsersPlaylistsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetCurrentUsersPlaylistsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-current-users-playlists-cbor-docs[]

// tag::spotify-get-users-playlists-cbor-docs[]
constexpr char kGetUsersPlaylistsCborValue[] = "user-id/playlists?limit=5";

void sendSpotifyGetUsersPlaylistsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.user.get", kGetUsersPlaylistsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.user.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.user.get");
}

void handleSpotifyGetUsersPlaylistsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.user.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.user.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.user.get.response payload");
    return;
  }

  if (kGetUsersPlaylistsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersPlaylistsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-playlists-cbor-docs[]

// tag::spotify-create-playlist-cbor-docs[]
constexpr char kCreatePlaylistCborValue[] = "user-id||{\"name\":\"Chill\"}";

void sendSpotifyCreatePlaylistCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.create", kCreatePlaylistCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.create request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.create");
}

void handleSpotifyCreatePlaylistCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.create.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.create response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.create.response payload");
    return;
  }

  if (kCreatePlaylistCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCreatePlaylistCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-create-playlist-cbor-docs[]

// tag::spotify-get-featured-playlists-cbor-docs[]
constexpr char kGetFeaturedPlaylistsCborValue[] = "country=US";

void sendSpotifyGetFeaturedPlaylistsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.featured.get", kGetFeaturedPlaylistsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.featured.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.featured.get");
}

void handleSpotifyGetFeaturedPlaylistsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.featured.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.featured.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.featured.get.response payload");
    return;
  }

  if (kGetFeaturedPlaylistsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetFeaturedPlaylistsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-featured-playlists-cbor-docs[]

// tag::spotify-get-categories-playlists-cbor-docs[]
constexpr char kGetCategoriesPlaylistsCborValue[] = "category-id/playlists?limit=10";

void sendSpotifyGetCategoriesPlaylistsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.category.get", kGetCategoriesPlaylistsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.category.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.category.get");
}

void handleSpotifyGetCategoriesPlaylistsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.category.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.category.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.category.get.response payload");
    return;
  }

  if (kGetCategoriesPlaylistsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetCategoriesPlaylistsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-categories-playlists-cbor-docs[]

// tag::spotify-get-playlist-cover-image-cbor-docs[]
constexpr char kGetPlaylistCoverImageCborValue[] = "playlist-id";

void sendSpotifyGetPlaylistCoverImageCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.cover.get", kGetPlaylistCoverImageCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.cover.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.cover.get");
}

void handleSpotifyGetPlaylistCoverImageCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.cover.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.cover.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.cover.get.response payload");
    return;
  }

  if (kGetPlaylistCoverImageCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetPlaylistCoverImageCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-playlist-cover-image-cbor-docs[]

// tag::spotify-add-custom-playlist-cover-image-cbor-docs[]
constexpr char kAddCustomPlaylistCoverImageCborValue[] = "playlist-id||BASE64DATA";

void sendSpotifyAddCustomPlaylistCoverImageCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.playlists.cover.add", kAddCustomPlaylistCoverImageCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.playlists.cover.add request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.playlists.cover.add");
}

void handleSpotifyAddCustomPlaylistCoverImageCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(8192);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.playlists.cover.add.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.playlists.cover.add response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.playlists.cover.add.response payload");
    return;
  }

  if (kAddCustomPlaylistCoverImageCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kAddCustomPlaylistCoverImageCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-add-custom-playlist-cover-image-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetPlaylistCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyGetPlaylistCborResponse(payload, length);
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
