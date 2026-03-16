#include <SpotifyCborExampleSupport.h>
#include <SpotifyExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-track-cbor-docs[]
constexpr char kGetTrackCborValue[] = "track-id";

void sendSpotifyGetTrackCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.tracks.get", kGetTrackCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.tracks.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.tracks.get");
}

void handleSpotifyGetTrackCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(6144);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.tracks.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.get.response payload");
    return;
  }

  if (kGetTrackCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetTrackCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-track-cbor-docs[]

// tag::spotify-get-several-tracks-cbor-docs[]
constexpr char kGetSeveralTracksCborValue[] = "ids=track-1,track-2";

void sendSpotifyGetSeveralTracksCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.tracks.get.several", kGetSeveralTracksCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.tracks.get.several request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.tracks.get.several");
}

void handleSpotifyGetSeveralTracksCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(6144);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.tracks.get.several.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.get.several.response payload");
    return;
  }

  if (kGetSeveralTracksCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralTracksCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-tracks-cbor-docs[]

// tag::spotify-get-users-saved-tracks-cbor-docs[]
constexpr char kGetUsersSavedTracksCborValue[] = "limit=1";

void sendSpotifyGetUsersSavedTracksCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.tracks.saved.get", kGetUsersSavedTracksCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.tracks.saved.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.tracks.saved.get");
}

void handleSpotifyGetUsersSavedTracksCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(6144);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.tracks.saved.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.saved.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.saved.get.response payload");
    return;
  }

  if (kGetUsersSavedTracksCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersSavedTracksCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-saved-tracks-cbor-docs[]

// tag::spotify-save-tracks-for-current-user-cbor-docs[]
constexpr char kSaveTracksForCurrentUserCborValue[] = "[\"track-id\"]";

void sendSpotifySaveTracksForCurrentUserCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.tracks.saved.save", kSaveTracksForCurrentUserCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.tracks.saved.save request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.tracks.saved.save");
}

void handleSpotifySaveTracksForCurrentUserCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(6144);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.tracks.saved.save.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.saved.save response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.saved.save.response payload");
    return;
  }

  if (kSaveTracksForCurrentUserCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kSaveTracksForCurrentUserCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-save-tracks-for-current-user-cbor-docs[]

// tag::spotify-remove-users-saved-tracks-cbor-docs[]
constexpr char kRemoveUsersSavedTracksCborValue[] = "[\"track-id\"]";

void sendSpotifyRemoveUsersSavedTracksCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.tracks.saved.remove", kRemoveUsersSavedTracksCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.tracks.saved.remove request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.tracks.saved.remove");
}

void handleSpotifyRemoveUsersSavedTracksCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(6144);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.tracks.saved.remove.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.saved.remove response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.saved.remove.response payload");
    return;
  }

  if (kRemoveUsersSavedTracksCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kRemoveUsersSavedTracksCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-remove-users-saved-tracks-cbor-docs[]

// tag::spotify-check-users-saved-tracks-cbor-docs[]
constexpr char kCheckUsersSavedTracksCborValue[] = "ids=track-id";

void sendSpotifyCheckUsersSavedTracksCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.tracks.saved.check", kCheckUsersSavedTracksCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.tracks.saved.check request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.tracks.saved.check");
}

void handleSpotifyCheckUsersSavedTracksCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(6144);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.tracks.saved.check.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.saved.check response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.saved.check.response payload");
    return;
  }

  if (kCheckUsersSavedTracksCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckUsersSavedTracksCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-users-saved-tracks-cbor-docs[]

// tag::spotify-get-several-tracks-audio-features-cbor-docs[]
constexpr char kGetSeveralTracksAudioFeaturesCborValue[] = "ids=track-1,track-2";

void sendSpotifyGetSeveralTracksAudioFeaturesCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.tracks.audio-features.get.several", kGetSeveralTracksAudioFeaturesCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.tracks.audio-features.get.several request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.tracks.audio-features.get.several");
}

void handleSpotifyGetSeveralTracksAudioFeaturesCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(6144);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.tracks.audio-features.get.several.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.audio-features.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.audio-features.get.several.response payload");
    return;
  }

  if (kGetSeveralTracksAudioFeaturesCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralTracksAudioFeaturesCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-tracks-audio-features-cbor-docs[]

// tag::spotify-get-tracks-audio-features-cbor-docs[]
constexpr char kGetTracksAudioFeaturesCborValue[] = "track-id";

void sendSpotifyGetTracksAudioFeaturesCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.tracks.audio-features.get", kGetTracksAudioFeaturesCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.tracks.audio-features.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.tracks.audio-features.get");
}

void handleSpotifyGetTracksAudioFeaturesCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(6144);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.tracks.audio-features.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.audio-features.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.audio-features.get.response payload");
    return;
  }

  if (kGetTracksAudioFeaturesCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetTracksAudioFeaturesCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-tracks-audio-features-cbor-docs[]

// tag::spotify-get-tracks-audio-analysis-cbor-docs[]
constexpr char kGetTracksAudioAnalysisCborValue[] = "track-id";

void sendSpotifyGetTracksAudioAnalysisCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.tracks.audio-analysis.get", kGetTracksAudioAnalysisCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.tracks.audio-analysis.get request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.tracks.audio-analysis.get");
}

void handleSpotifyGetTracksAudioAnalysisCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(6144);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.tracks.audio-analysis.get.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.audio-analysis.get response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.audio-analysis.get.response payload");
    return;
  }

  if (kGetTracksAudioAnalysisCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetTracksAudioAnalysisCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-tracks-audio-analysis-cbor-docs[]

// tag::spotify-get-recommendations-cbor-docs[]
constexpr char kGetRecommendationsCborValue[] = "seed_tracks=track-1";

void sendSpotifyGetRecommendationsCbor(WebSocketsClient& socket) {
  uint8_t encoded[768];
  size_t encodedLength = offbeat::spotify::examples::cbor::buildRequest("spotify.tracks.recommendations", kGetRecommendationsCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.tracks.recommendations request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.tracks.recommendations");
}

void handleSpotifyGetRecommendationsCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(6144);
  cn_cbor* root = NULL;
  cn_cbor* result = NULL;
  offbeat::spotify::examples::cbor::ParseStatus status =
      offbeat::spotify::examples::cbor::parseResult(
          payload, length, buffer, "spotify.tracks.recommendations.response", root, result);

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.tracks.recommendations response");
    return;
  }

  if (status == offbeat::spotify::examples::cbor::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.tracks.recommendations.response payload");
    return;
  }

  if (kGetRecommendationsCborValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetRecommendationsCborValue);
  }
  offbeat::spotify::examples::cbor::printSummary(result);
  offbeat::spotify::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-recommendations-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetTrackCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyGetTrackCborResponse(payload, length);
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
