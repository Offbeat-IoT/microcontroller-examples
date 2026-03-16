#include <ArduinoCbor.h>
#include <SpotifyPlaybackCommandCbor.h>
#include <WebSocketsClient.h>

#include "../SpotifyExampleSupport.h"
#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-shuffle-on-cbor-docs[]
constexpr char kDesiredShuffleState[] = "on";

void sendSpotifyShuffleOnCbor(WebSocketsClient& socket) {
  uint8_t encoded[96];
  size_t encodedLength = offbeat::spotify::buildShuffleCborRequest(
      kDesiredShuffleState, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.shuffle request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.shuffle");
}

void handleSpotifyShuffleOnCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(256);
  offbeat::spotify::SpotifyPlaybackCommandResult actionResult;
  offbeat::spotify::SpotifyPlaybackCommandParseStatus status =
      offbeat::spotify::parseShuffleCborResponse(payload, length, buffer, actionResult);

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
// end::spotify-shuffle-on-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyShuffleOnCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyShuffleOnCborResponse(payload, length);
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
