#include <ArduinoJson.h>
#include <SpotifyExampleSupport.h>
#include <SpotifyPlaybackCommandJson.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-shuffle-off-json-docs[]
constexpr char kDesiredValue[] = "Off";
void sendSpotifyShuffleOffJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::buildPlaybackCommandJsonRequest("spotify.shuffle", kDesiredValue, body)) {
    Serial.println("Unable to build spotify.shuffle request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.shuffle");
}

void handleSpotifyShuffleOffJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<512> response;
  offbeat::spotify::SpotifyPlaybackCommandResult result;
  offbeat::spotify::SpotifyPlaybackCommandParseStatus status =
      offbeat::spotify::parsePlaybackCommandJsonResponse(
          payload, length, response, "spotify.shuffle.response", result);

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
  Serial.println(kDesiredValue);
  Serial.print("SHUFFLE_STATE=");
  Serial.println(kDesiredValue);
  Serial.print("Result: ");
  Serial.println(result.result);
  Serial.print("Endpoint ID: ");
  Serial.println(result.endpointId);
  Serial.print("RESULT=");
  Serial.println(result.result);
  Serial.print("ENDPOINT_ID=");
  Serial.println(result.endpointId);
  Serial.println("TEST:PASS");
}
// end::spotify-shuffle-off-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyShuffleOffJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyShuffleOffJsonResponse(payload, length);
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
