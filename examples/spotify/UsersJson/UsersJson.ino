#include <SpotifyExampleSupport.h>
#include <SpotifyJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-current-users-profile-json-docs[]
constexpr char kGetCurrentUsersProfileJsonValue[] = "";

void sendSpotifyGetCurrentUsersProfileJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.users.current.get", kGetCurrentUsersProfileJsonValue, body)) {
    Serial.println("Unable to build spotify.users.current.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.users.current.get");
}

void handleSpotifyGetCurrentUsersProfileJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.users.current.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.current.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.current.get.response payload");
    return;
  }

  if (kGetCurrentUsersProfileJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetCurrentUsersProfileJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-current-users-profile-json-docs[]

// tag::spotify-get-users-top-items-json-docs[]
constexpr char kGetUsersTopItemsJsonValue[] = "tracks?limit=5";

void sendSpotifyGetUsersTopItemsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.users.top-items", kGetUsersTopItemsJsonValue, body)) {
    Serial.println("Unable to build spotify.users.top-items request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.users.top-items");
}

void handleSpotifyGetUsersTopItemsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.users.top-items.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.top-items response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.top-items.response payload");
    return;
  }

  if (kGetUsersTopItemsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersTopItemsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-top-items-json-docs[]

// tag::spotify-get-users-profile-json-docs[]
constexpr char kGetUsersProfileJsonValue[] = "user-id";

void sendSpotifyGetUsersProfileJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.users.get", kGetUsersProfileJsonValue, body)) {
    Serial.println("Unable to build spotify.users.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.users.get");
}

void handleSpotifyGetUsersProfileJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.users.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.get.response payload");
    return;
  }

  if (kGetUsersProfileJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersProfileJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-profile-json-docs[]

// tag::spotify-follow-playlist-json-docs[]
constexpr char kFollowPlaylistJsonValue[] = "playlist-id||{\"public\":false}";

void sendSpotifyFollowPlaylistJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.users.playlists.follow", kFollowPlaylistJsonValue, body)) {
    Serial.println("Unable to build spotify.users.playlists.follow request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.users.playlists.follow");
}

void handleSpotifyFollowPlaylistJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.users.playlists.follow.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.playlists.follow response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.playlists.follow.response payload");
    return;
  }

  if (kFollowPlaylistJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kFollowPlaylistJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-follow-playlist-json-docs[]

// tag::spotify-unfollow-playlist-json-docs[]
constexpr char kUnfollowPlaylistJsonValue[] = "playlist-id";

void sendSpotifyUnfollowPlaylistJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.users.playlists.unfollow", kUnfollowPlaylistJsonValue, body)) {
    Serial.println("Unable to build spotify.users.playlists.unfollow request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.users.playlists.unfollow");
}

void handleSpotifyUnfollowPlaylistJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.users.playlists.unfollow.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.playlists.unfollow response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.playlists.unfollow.response payload");
    return;
  }

  if (kUnfollowPlaylistJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kUnfollowPlaylistJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-unfollow-playlist-json-docs[]

// tag::spotify-get-followed-artists-json-docs[]
constexpr char kGetFollowedArtistsJsonValue[] = "type=artist&limit=5";

void sendSpotifyGetFollowedArtistsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.users.followed-artists", kGetFollowedArtistsJsonValue, body)) {
    Serial.println("Unable to build spotify.users.followed-artists request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.users.followed-artists");
}

void handleSpotifyGetFollowedArtistsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.users.followed-artists.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.followed-artists response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.followed-artists.response payload");
    return;
  }

  if (kGetFollowedArtistsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetFollowedArtistsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-followed-artists-json-docs[]

// tag::spotify-follow-artists-or-users-json-docs[]
constexpr char kFollowArtistsOrUsersJsonValue[] = "type=artist&ids=artist-id";

void sendSpotifyFollowArtistsOrUsersJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.users.follow", kFollowArtistsOrUsersJsonValue, body)) {
    Serial.println("Unable to build spotify.users.follow request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.users.follow");
}

void handleSpotifyFollowArtistsOrUsersJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.users.follow.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.follow response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.follow.response payload");
    return;
  }

  if (kFollowArtistsOrUsersJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kFollowArtistsOrUsersJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-follow-artists-or-users-json-docs[]

// tag::spotify-unfollow-artists-or-users-json-docs[]
constexpr char kUnfollowArtistsOrUsersJsonValue[] = "type=user&ids=user-id";

void sendSpotifyUnfollowArtistsOrUsersJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.users.unfollow", kUnfollowArtistsOrUsersJsonValue, body)) {
    Serial.println("Unable to build spotify.users.unfollow request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.users.unfollow");
}

void handleSpotifyUnfollowArtistsOrUsersJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.users.unfollow.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.unfollow response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.unfollow.response payload");
    return;
  }

  if (kUnfollowArtistsOrUsersJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kUnfollowArtistsOrUsersJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-unfollow-artists-or-users-json-docs[]

// tag::spotify-check-if-user-follows-artists-or-users-json-docs[]
constexpr char kCheckIfUserFollowsArtistsOrUsersJsonValue[] = "type=artist&ids=artist-id";

void sendSpotifyCheckIfUserFollowsArtistsOrUsersJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.users.follow.check", kCheckIfUserFollowsArtistsOrUsersJsonValue, body)) {
    Serial.println("Unable to build spotify.users.follow.check request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.users.follow.check");
}

void handleSpotifyCheckIfUserFollowsArtistsOrUsersJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.users.follow.check.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.follow.check response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.follow.check.response payload");
    return;
  }

  if (kCheckIfUserFollowsArtistsOrUsersJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckIfUserFollowsArtistsOrUsersJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-if-user-follows-artists-or-users-json-docs[]

// tag::spotify-check-if-current-user-follows-playlist-json-docs[]
constexpr char kCheckIfCurrentUserFollowsPlaylistJsonValue[] = "playlist-id/followers/contains?ids=user-id";

void sendSpotifyCheckIfCurrentUserFollowsPlaylistJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.users.playlists.follow.check", kCheckIfCurrentUserFollowsPlaylistJsonValue, body)) {
    Serial.println("Unable to build spotify.users.playlists.follow.check request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.users.playlists.follow.check");
}

void handleSpotifyCheckIfCurrentUserFollowsPlaylistJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.users.playlists.follow.check.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.users.playlists.follow.check response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.users.playlists.follow.check.response payload");
    return;
  }

  if (kCheckIfCurrentUserFollowsPlaylistJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckIfCurrentUserFollowsPlaylistJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-if-current-user-follows-playlist-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetCurrentUsersProfileJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyGetCurrentUsersProfileJsonResponse(payload, length);
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
