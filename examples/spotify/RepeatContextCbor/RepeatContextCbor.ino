#include <ArduinoCbor.h>
#include <SpotifyExampleSupport.h>
#include <SpotifyPlaybackCommandCbor.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-repeat-context-cbor-docs[]
constexpr char kDesiredRepeatState[] = "context";

void sendSpotifyRepeatContextCbor(WebSocketsClient& socket) {
  uint8_t encoded[96];
  size_t encodedLength = offbeat::spotify::buildRepeatCborRequest(
      kDesiredRepeatState, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.repeat request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.repeat");
}

void handleSpotifyRepeatContextCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(256);
  offbeat::spotify::SpotifyPlaybackCommandResult actionResult;
  offbeat::spotify::SpotifyPlaybackCommandParseStatus status =
      offbeat::spotify::parseRepeatCborResponse(payload, length, buffer, actionResult);

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify repeat response");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kMissingResponse) {
    Serial.println("No spotify.repeat.response payload");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kMissingResult) {
    Serial.println("No result in spotify.repeat.response payload");
    return;
  }

  Serial.print("Desired repeat state: ");
  Serial.println(kDesiredRepeatState);
  Serial.print("Result: ");
  Serial.println(actionResult.result);
  Serial.print("Endpoint ID: ");
  Serial.println(actionResult.endpointId);
  Serial.print("REPEAT_STATE=");
  Serial.println(kDesiredRepeatState);
  Serial.print("RESULT=");
  Serial.println(actionResult.result);
  Serial.print("ENDPOINT_ID=");
  Serial.println(actionResult.endpointId);
  Serial.println("TEST:PASS");
}
// end::spotify-repeat-context-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyRepeatContextCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyRepeatContextCborResponse(payload, length);
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
