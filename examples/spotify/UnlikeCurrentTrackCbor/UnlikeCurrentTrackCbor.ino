#include <ArduinoCbor.h>
#include <SpotifyExampleSupport.h>
#include <SpotifyPlaybackCommandCbor.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-unlike-cbor-docs[]
void sendSpotifyUnlikeCurrentTrackCbor(WebSocketsClient& socket) {
  uint8_t encoded[96];
  size_t encodedLength =
      offbeat::spotify::buildPlaybackCommandCborRequest("spotify.unlike", "", encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.unlike request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.unlike");
}

void handleSpotifyUnlikeCurrentTrackCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(256);
  offbeat::spotify::SpotifyPlaybackCommandResult result;
  offbeat::spotify::SpotifyPlaybackCommandParseStatus status =
      offbeat::spotify::parsePlaybackCommandCborResponse(
          payload, length, buffer, "spotify.unlike.response", result);

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify unlike response");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kMissingResponse) {
    Serial.println("No spotify.unlike.response payload");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kMissingResult) {
    Serial.println("No result in spotify.unlike.response payload");
    return;
  }

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
// end::spotify-unlike-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyUnlikeCurrentTrackCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyUnlikeCurrentTrackCborResponse(payload, length);
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
