#include <SpotifyExampleSupport.h>
#include <SpotifyJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-get-an-audiobook-json-docs[]
constexpr char kGetAnAudiobookJsonValue[] = "audiobook-id";

void sendSpotifyGetAnAudiobookJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.audiobooks.get", kGetAnAudiobookJsonValue, body)) {
    Serial.println("Unable to build spotify.audiobooks.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.audiobooks.get");
}

void handleSpotifyGetAnAudiobookJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.audiobooks.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.get.response payload");
    return;
  }

  if (kGetAnAudiobookJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetAnAudiobookJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-an-audiobook-json-docs[]

// tag::spotify-get-several-audiobooks-json-docs[]
constexpr char kGetSeveralAudiobooksJsonValue[] = "ids=book-1,book-2";

void sendSpotifyGetSeveralAudiobooksJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.audiobooks.get.several", kGetSeveralAudiobooksJsonValue, body)) {
    Serial.println("Unable to build spotify.audiobooks.get.several request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.audiobooks.get.several");
}

void handleSpotifyGetSeveralAudiobooksJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.audiobooks.get.several.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.get.several response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.get.several.response payload");
    return;
  }

  if (kGetSeveralAudiobooksJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetSeveralAudiobooksJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-several-audiobooks-json-docs[]

// tag::spotify-get-audiobook-chapters-json-docs[]
constexpr char kGetAudiobookChaptersJsonValue[] = "audiobook-id";

void sendSpotifyGetAudiobookChaptersJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.audiobooks.chapters", kGetAudiobookChaptersJsonValue, body)) {
    Serial.println("Unable to build spotify.audiobooks.chapters request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.audiobooks.chapters");
}

void handleSpotifyGetAudiobookChaptersJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.audiobooks.chapters.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.chapters response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.chapters.response payload");
    return;
  }

  if (kGetAudiobookChaptersJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetAudiobookChaptersJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-audiobook-chapters-json-docs[]

// tag::spotify-get-users-saved-audiobooks-json-docs[]
constexpr char kGetUsersSavedAudiobooksJsonValue[] = "limit=5";

void sendSpotifyGetUsersSavedAudiobooksJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.audiobooks.saved.get", kGetUsersSavedAudiobooksJsonValue, body)) {
    Serial.println("Unable to build spotify.audiobooks.saved.get request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.audiobooks.saved.get");
}

void handleSpotifyGetUsersSavedAudiobooksJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.audiobooks.saved.get.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.saved.get response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.saved.get.response payload");
    return;
  }

  if (kGetUsersSavedAudiobooksJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kGetUsersSavedAudiobooksJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-get-users-saved-audiobooks-json-docs[]

// tag::spotify-save-audiobooks-for-current-user-json-docs[]
constexpr char kSaveAudiobooksForCurrentUserJsonValue[] = "[\"audiobook-id\"]";

void sendSpotifySaveAudiobooksForCurrentUserJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.audiobooks.saved.save", kSaveAudiobooksForCurrentUserJsonValue, body)) {
    Serial.println("Unable to build spotify.audiobooks.saved.save request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.audiobooks.saved.save");
}

void handleSpotifySaveAudiobooksForCurrentUserJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.audiobooks.saved.save.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.saved.save response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.saved.save.response payload");
    return;
  }

  if (kSaveAudiobooksForCurrentUserJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kSaveAudiobooksForCurrentUserJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-save-audiobooks-for-current-user-json-docs[]

// tag::spotify-remove-users-saved-audiobooks-json-docs[]
constexpr char kRemoveUsersSavedAudiobooksJsonValue[] = "[\"audiobook-id\"]";

void sendSpotifyRemoveUsersSavedAudiobooksJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.audiobooks.saved.remove", kRemoveUsersSavedAudiobooksJsonValue, body)) {
    Serial.println("Unable to build spotify.audiobooks.saved.remove request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.audiobooks.saved.remove");
}

void handleSpotifyRemoveUsersSavedAudiobooksJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.audiobooks.saved.remove.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.saved.remove response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.saved.remove.response payload");
    return;
  }

  if (kRemoveUsersSavedAudiobooksJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kRemoveUsersSavedAudiobooksJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-remove-users-saved-audiobooks-json-docs[]

// tag::spotify-check-users-saved-audiobooks-json-docs[]
constexpr char kCheckUsersSavedAudiobooksJsonValue[] = "ids=audiobook-id";

void sendSpotifyCheckUsersSavedAudiobooksJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::examples::json::buildRequest("spotify.audiobooks.saved.check", kCheckUsersSavedAudiobooksJsonValue, body)) {
    Serial.println("Unable to build spotify.audiobooks.saved.check request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.audiobooks.saved.check");
}

void handleSpotifyCheckUsersSavedAudiobooksJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<4096> document;
  JsonObjectConst root;
  JsonVariantConst result;
  offbeat::spotify::examples::json::ParseStatus status =
      offbeat::spotify::examples::json::parseResult(
          payload, length, document, "spotify.audiobooks.saved.check.response", root, result);

  if (status == offbeat::spotify::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify.audiobooks.saved.check response");
    return;
  }

  if (status == offbeat::spotify::examples::json::ParseStatus::kMissingResponse) {
    Serial.println("No spotify.audiobooks.saved.check.response payload");
    return;
  }

  if (kCheckUsersSavedAudiobooksJsonValue[0] != '\0') {
    Serial.print("Request value: ");
    Serial.println(kCheckUsersSavedAudiobooksJsonValue);
  }
  offbeat::spotify::examples::json::printSummary(result);
  offbeat::spotify::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::spotify-check-users-saved-audiobooks-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetAnAudiobookJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyGetAnAudiobookJsonResponse(payload, length);
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
