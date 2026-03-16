#include <SpotifyExampleSupport.h>
#include <SpotifyJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-track-json-docs[]
constexpr char kGetTrackJsonValue[] = "track-id";

void sendSpotifyGetTrackJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.tracks.get", kGetTrackJsonValue, body)) {
    Serial.println("Unable to build spotify.tracks.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.tracks.get");
}

void handleSpotifyGetTrackJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<6144> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.tracks.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.get.response payload");
    return;
  }

  if (kGetTrackJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetTrackJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-track-json-docs[]

// tag::spotify-get-several-tracks-json-docs[]
constexpr char kGetSeveralTracksJsonValue[] = "ids=track-1,track-2";

void sendSpotifyGetSeveralTracksJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.tracks.get.several", kGetSeveralTracksJsonValue, body)) {
    Serial.println("Unable to build spotify.tracks.get.several request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.tracks.get.several");
}

void handleSpotifyGetSeveralTracksJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<6144> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.tracks.get.several.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.get.several.response payload");
    return;
  }

  if (kGetSeveralTracksJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralTracksJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-tracks-json-docs[]

// tag::spotify-get-users-saved-tracks-json-docs[]
constexpr char kGetUsersSavedTracksJsonValue[] = "limit=1";

void sendSpotifyGetUsersSavedTracksJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.tracks.saved.get", kGetUsersSavedTracksJsonValue, body)) {
    Serial.println("Unable to build spotify.tracks.saved.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.tracks.saved.get");
}

void handleSpotifyGetUsersSavedTracksJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<6144> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.tracks.saved.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.saved.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.saved.get.response payload");
    return;
  }

  if (kGetUsersSavedTracksJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersSavedTracksJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-saved-tracks-json-docs[]

// tag::spotify-save-tracks-for-current-user-json-docs[]
constexpr char kSaveTracksForCurrentUserJsonValue[] = "[\"track-id\"]";

void sendSpotifySaveTracksForCurrentUserJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.tracks.saved.save", kSaveTracksForCurrentUserJsonValue, body)) {
    Serial.println("Unable to build spotify.tracks.saved.save request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.tracks.saved.save");
}

void handleSpotifySaveTracksForCurrentUserJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<6144> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.tracks.saved.save.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.saved.save response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.saved.save.response payload");
    return;
  }

  if (kSaveTracksForCurrentUserJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kSaveTracksForCurrentUserJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-save-tracks-for-current-user-json-docs[]

// tag::spotify-remove-users-saved-tracks-json-docs[]
constexpr char kRemoveUsersSavedTracksJsonValue[] = "[\"track-id\"]";

void sendSpotifyRemoveUsersSavedTracksJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.tracks.saved.remove", kRemoveUsersSavedTracksJsonValue, body)) {
    Serial.println("Unable to build spotify.tracks.saved.remove request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.tracks.saved.remove");
}

void handleSpotifyRemoveUsersSavedTracksJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<6144> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.tracks.saved.remove.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.saved.remove response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.saved.remove.response payload");
    return;
  }

  if (kRemoveUsersSavedTracksJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kRemoveUsersSavedTracksJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-remove-users-saved-tracks-json-docs[]

// tag::spotify-check-users-saved-tracks-json-docs[]
constexpr char kCheckUsersSavedTracksJsonValue[] = "ids=track-id";

void sendSpotifyCheckUsersSavedTracksJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.tracks.saved.check", kCheckUsersSavedTracksJsonValue, body)) {
    Serial.println("Unable to build spotify.tracks.saved.check request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.tracks.saved.check");
}

void handleSpotifyCheckUsersSavedTracksJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<6144> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.tracks.saved.check.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.saved.check response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.saved.check.response payload");
    return;
  }

  if (kCheckUsersSavedTracksJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckUsersSavedTracksJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-users-saved-tracks-json-docs[]

// tag::spotify-get-several-tracks-audio-features-json-docs[]
constexpr char kGetSeveralTracksAudioFeaturesJsonValue[] = "ids=track-1,track-2";

void sendSpotifyGetSeveralTracksAudioFeaturesJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.tracks.audio-features.get.several", kGetSeveralTracksAudioFeaturesJsonValue, body)) {
    Serial.println("Unable to build spotify.tracks.audio-features.get.several request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.tracks.audio-features.get.several");
}

void handleSpotifyGetSeveralTracksAudioFeaturesJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<6144> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.tracks.audio-features.get.several.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.audio-features.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.audio-features.get.several.response payload");
    return;
  }

  if (kGetSeveralTracksAudioFeaturesJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralTracksAudioFeaturesJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-tracks-audio-features-json-docs[]

// tag::spotify-get-tracks-audio-features-json-docs[]
constexpr char kGetTracksAudioFeaturesJsonValue[] = "track-id";

void sendSpotifyGetTracksAudioFeaturesJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.tracks.audio-features.get", kGetTracksAudioFeaturesJsonValue, body)) {
    Serial.println("Unable to build spotify.tracks.audio-features.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.tracks.audio-features.get");
}

void handleSpotifyGetTracksAudioFeaturesJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<6144> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.tracks.audio-features.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.audio-features.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.audio-features.get.response payload");
    return;
  }

  if (kGetTracksAudioFeaturesJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetTracksAudioFeaturesJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-tracks-audio-features-json-docs[]

// tag::spotify-get-tracks-audio-analysis-json-docs[]
constexpr char kGetTracksAudioAnalysisJsonValue[] = "track-id";

void sendSpotifyGetTracksAudioAnalysisJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.tracks.audio-analysis.get", kGetTracksAudioAnalysisJsonValue, body)) {
    Serial.println("Unable to build spotify.tracks.audio-analysis.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.tracks.audio-analysis.get");
}

void handleSpotifyGetTracksAudioAnalysisJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<6144> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.tracks.audio-analysis.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.audio-analysis.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.audio-analysis.get.response payload");
    return;
  }

  if (kGetTracksAudioAnalysisJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetTracksAudioAnalysisJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-tracks-audio-analysis-json-docs[]

// tag::spotify-get-recommendations-json-docs[]
constexpr char kGetRecommendationsJsonValue[] = "seed_tracks=track-1";

void sendSpotifyGetRecommendationsJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.tracks.recommendations", kGetRecommendationsJsonValue, body)) {
    Serial.println("Unable to build spotify.tracks.recommendations request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.tracks.recommendations");
}

void handleSpotifyGetRecommendationsJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<6144> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.tracks.recommendations.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.recommendations response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.recommendations.response payload");
    return;
  }

  if (kGetRecommendationsJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetRecommendationsJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-recommendations-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetTrackJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyGetTrackJsonResponse(payload, length);
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
