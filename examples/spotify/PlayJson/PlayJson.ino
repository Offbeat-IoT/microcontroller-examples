#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SpotifyPlaybackCommandJson.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

bool connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(OFFBEAT_WIFI_SSID, OFFBEAT_WIFI_PASSWORD);
  Serial.println("WIFI_CONNECTING");

  unsigned long nextStatusLogAt = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    unsigned long now = millis();
    if (now >= nextStatusLogAt) {
      Serial.print("WIFI_STATUS=");
      Serial.println(static_cast<int>(WiFi.status()));
      nextStatusLogAt = now + 5000;
    }
  }

  Serial.println("WIFI_CONNECTED");
  return true;
}

// tag::spotify-play-json-docs[]
void sendSpotifyPlayJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::buildPlayJsonRequest(body)) {
    Serial.println("Unable to build spotify.play request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.play");
}

void printSpotifyPlaybackCommandResult(const offbeat::spotify::SpotifyPlaybackCommandResult& result) {
  Serial.print("Result: ");
  Serial.println(result.result);

  Serial.print("Endpoint ID: ");
  Serial.println(result.endpointId);

  Serial.print("RESULT=");
  Serial.println(result.result);
  Serial.print("ENDPOINT_ID=");
  Serial.println(result.endpointId);
}

void handleSpotifyPlayJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<512> response;
  offbeat::spotify::SpotifyPlaybackCommandResult result;
  offbeat::spotify::SpotifyPlaybackCommandParseStatus status =
      offbeat::spotify::parsePlayJsonResponse(payload, length, response, result);

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify play response");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kMissingResponse) {
    Serial.println("No spotify.play.response payload");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kMissingResult) {
    Serial.println("No result in spotify.play.response payload");
    return;
  }

  printSpotifyPlaybackCommandResult(result);
  Serial.println("TEST:PASS");
}
// end::spotify-play-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyPlayJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyPlayJsonResponse(payload, length);
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("TEST:READY");
  if (!connectWifi()) {
    return;
  }

  webSocket.begin(OFFBEAT_WS_HOST, OFFBEAT_WS_PORT, OFFBEAT_WS_PATH);
  webSocket.onEvent(websocketEvent);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();
}
