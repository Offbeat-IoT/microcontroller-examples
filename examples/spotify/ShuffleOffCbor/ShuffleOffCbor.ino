#include <ArduinoCbor.h>
#include <SpotifyExampleSupport.h>
#include <SpotifyPlaybackCommandCbor.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-shuffle-off-cbor-docs[]
constexpr char kDesiredValue[] = "Off";
void sendSpotifyShuffleOffCbor(WebSocketsClient& socket) {
  uint8_t encoded[96];
  size_t encodedLength =
      offbeat::spotify::buildPlaybackCommandCborRequest("spotify.shuffle", kDesiredValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.shuffle request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.shuffle");
}

void handleSpotifyShuffleOffCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(256);
  offbeat::spotify::SpotifyPlaybackCommandResult result;
  offbeat::spotify::SpotifyPlaybackCommandParseStatus status =
      offbeat::spotify::parsePlaybackCommandCborResponse(
          payload, length, buffer, "spotify.shuffle.response", result);

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
// end::spotify-shuffle-off-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyShuffleOffCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyShuffleOffCborResponse(payload, length);
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
