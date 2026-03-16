#include <ArduinoJson.h>
#include <SpotifyPlaybackCommandJson.h>
#include <WebSocketsClient.h>

#include "../SpotifyExampleSupport.h"
#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-shuffle-on-json-docs[]
constexpr char kDesiredShuffleState[] = "on";

void sendSpotifyShuffleOnJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::buildShuffleJsonRequest(kDesiredShuffleState, body)) {
    Serial.println("Unable to build spotify.shuffle request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.shuffle");
}

void handleSpotifyShuffleOnJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<512> response;
  offbeat::spotify::SpotifyPlaybackCommandResult actionResult;
  offbeat::spotify::SpotifyPlaybackCommandParseStatus status =
      offbeat::spotify::parseShuffleJsonResponse(payload, length, response, actionResult);

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify shuffle response");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kMissingResponse) {
    Serial.println("No spotify.shuffle.response payload");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kMissingResult) {
    Serial.println("No result in spotify.shuffle.response payload");
    return;
  }

  Serial.print("Desired shuffle state: ");
  Serial.println(kDesiredShuffleState);
  Serial.print("Result: ");
  Serial.println(actionResult.result);
  Serial.print("Endpoint ID: ");
  Serial.println(actionResult.endpointId);
  Serial.print("SHUFFLE_STATE=");
  Serial.println(kDesiredShuffleState);
  Serial.print("RESULT=");
  Serial.println(actionResult.result);
  Serial.print("ENDPOINT_ID=");
  Serial.println(actionResult.endpointId);
  Serial.println("TEST:PASS");
}
// end::spotify-shuffle-on-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyShuffleOnJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyShuffleOnJsonResponse(payload, length);
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
