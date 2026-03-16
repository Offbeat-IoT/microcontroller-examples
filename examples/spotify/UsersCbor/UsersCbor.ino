#include <SpotifyCborExampleSupport.h>
#include <SpotifyExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-current-users-profile-cbor-docs[]
constexpr char kGetCurrentUsersProfileCborValue[] = "";

void sendSpotifyGetCurrentUsersProfileCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.users.current.get", kGetCurrentUsersProfileCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.users.current.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.users.current.get");
}

void handleSpotifyGetCurrentUsersProfileCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.users.current.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.current.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.current.get.response payload");
    return;
  }

  if (kGetCurrentUsersProfileCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetCurrentUsersProfileCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-current-users-profile-cbor-docs[]

// tag::spotify-get-users-top-items-cbor-docs[]
constexpr char kGetUsersTopItemsCborValue[] = "tracks?limit=5";

void sendSpotifyGetUsersTopItemsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.users.top-items", kGetUsersTopItemsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.users.top-items request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.users.top-items");
}

void handleSpotifyGetUsersTopItemsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.users.top-items.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.top-items response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.top-items.response payload");
    return;
  }

  if (kGetUsersTopItemsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersTopItemsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-top-items-cbor-docs[]

// tag::spotify-get-users-profile-cbor-docs[]
constexpr char kGetUsersProfileCborValue[] = "user-id";

void sendSpotifyGetUsersProfileCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.users.get", kGetUsersProfileCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.users.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.users.get");
}

void handleSpotifyGetUsersProfileCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.users.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.get.response payload");
    return;
  }

  if (kGetUsersProfileCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersProfileCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-profile-cbor-docs[]

// tag::spotify-follow-playlist-cbor-docs[]
constexpr char kFollowPlaylistCborValue[] = "playlist-id||{\"public\":false}";

void sendSpotifyFollowPlaylistCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.users.playlists.follow", kFollowPlaylistCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.users.playlists.follow request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.users.playlists.follow");
}

void handleSpotifyFollowPlaylistCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.users.playlists.follow.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.playlists.follow response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.playlists.follow.response payload");
    return;
  }

  if (kFollowPlaylistCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kFollowPlaylistCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-follow-playlist-cbor-docs[]

// tag::spotify-unfollow-playlist-cbor-docs[]
constexpr char kUnfollowPlaylistCborValue[] = "playlist-id";

void sendSpotifyUnfollowPlaylistCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.users.playlists.unfollow", kUnfollowPlaylistCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.users.playlists.unfollow request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.users.playlists.unfollow");
}

void handleSpotifyUnfollowPlaylistCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.users.playlists.unfollow.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.playlists.unfollow response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.playlists.unfollow.response payload");
    return;
  }

  if (kUnfollowPlaylistCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kUnfollowPlaylistCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-unfollow-playlist-cbor-docs[]

// tag::spotify-get-followed-artists-cbor-docs[]
constexpr char kGetFollowedArtistsCborValue[] = "type=artist&limit=5";

void sendSpotifyGetFollowedArtistsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.users.followed-artists", kGetFollowedArtistsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.users.followed-artists request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.users.followed-artists");
}

void handleSpotifyGetFollowedArtistsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.users.followed-artists.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.followed-artists response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.followed-artists.response payload");
    return;
  }

  if (kGetFollowedArtistsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetFollowedArtistsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-followed-artists-cbor-docs[]

// tag::spotify-follow-artists-or-users-cbor-docs[]
constexpr char kFollowArtistsOrUsersCborValue[] = "type=artist&ids=artist-id";

void sendSpotifyFollowArtistsOrUsersCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.users.follow", kFollowArtistsOrUsersCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.users.follow request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.users.follow");
}

void handleSpotifyFollowArtistsOrUsersCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.users.follow.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.follow response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.follow.response payload");
    return;
  }

  if (kFollowArtistsOrUsersCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kFollowArtistsOrUsersCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-follow-artists-or-users-cbor-docs[]

// tag::spotify-unfollow-artists-or-users-cbor-docs[]
constexpr char kUnfollowArtistsOrUsersCborValue[] = "type=user&ids=user-id";

void sendSpotifyUnfollowArtistsOrUsersCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.users.unfollow", kUnfollowArtistsOrUsersCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.users.unfollow request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.users.unfollow");
}

void handleSpotifyUnfollowArtistsOrUsersCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.users.unfollow.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.unfollow response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.unfollow.response payload");
    return;
  }

  if (kUnfollowArtistsOrUsersCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kUnfollowArtistsOrUsersCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-unfollow-artists-or-users-cbor-docs[]

// tag::spotify-check-if-user-follows-artists-or-users-cbor-docs[]
constexpr char kCheckIfUserFollowsArtistsOrUsersCborValue[] = "type=artist&ids=artist-id";

void sendSpotifyCheckIfUserFollowsArtistsOrUsersCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.users.follow.check", kCheckIfUserFollowsArtistsOrUsersCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.users.follow.check request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.users.follow.check");
}

void handleSpotifyCheckIfUserFollowsArtistsOrUsersCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.users.follow.check.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.follow.check response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.follow.check.response payload");
    return;
  }

  if (kCheckIfUserFollowsArtistsOrUsersCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckIfUserFollowsArtistsOrUsersCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-if-user-follows-artists-or-users-cbor-docs[]

// tag::spotify-check-if-current-user-follows-playlist-cbor-docs[]
constexpr char kCheckIfCurrentUserFollowsPlaylistCborValue[] = "playlist-id/followers/contains?ids=user-id";

void sendSpotifyCheckIfCurrentUserFollowsPlaylistCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.users.playlists.follow.check", kCheckIfCurrentUserFollowsPlaylistCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.users.playlists.follow.check request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.users.playlists.follow.check");
}

void handleSpotifyCheckIfCurrentUserFollowsPlaylistCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(4096);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.users.playlists.follow.check.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.playlists.follow.check response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.playlists.follow.check.response payload");
    return;
  }

  if (kCheckIfCurrentUserFollowsPlaylistCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckIfCurrentUserFollowsPlaylistCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-if-current-user-follows-playlist-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetCurrentUsersProfileCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyGetCurrentUsersProfileCborResponse(payload, length);
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
