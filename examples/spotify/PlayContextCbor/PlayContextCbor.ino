#include <ArduinoCbor.h>
#include <SpotifyExampleSupport.h>
#include <SpotifyPlaybackCommandCbor.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-play-context-cbor-docs[]
// Replace the URI prefix with spotify:album:, spotify:artists:, or spotify:playlists:.
constexpr char kContextUri[] = "spotify:album:the context_uri";

void sendSpotifyPlayContextCbor(WebSocketsClient& socket) {
  uint8_t encoded[160];
  size_t encodedLength = offbeat::spotify::buildPlaybackCommandCborRequest(
      "spotify.play.items", kContextUri, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.play.items request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.play.items");
}

void handleSpotifyPlayContextCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(256);
  offbeat::spotify::SpotifyPlaybackCommandResult result;
  offbeat::spotify::SpotifyPlaybackCommandParseStatus status =
      offbeat::spotify::parsePlaybackCommandCborResponse(
          payload, length, buffer, "spotify.play.items.response", result);

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify play.items response");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kMissingResponse) {
    Serial.println("No spotify.play.items.response payload");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kMissingResult) {
    Serial.println("No result in spotify.play.items.response payload");
    return;
  }

  Serial.print("Context URI: ");
  Serial.println(kContextUri);
  Serial.print("Result: ");
  Serial.println(result.result);
  Serial.print("Endpoint ID: ");
  Serial.println(result.endpointId);
  Serial.print("CONTEXT_URI=");
  Serial.println(kContextUri);
  Serial.print("RESULT=");
  Serial.println(result.result);
  Serial.print("ENDPOINT_ID=");
  Serial.println(result.endpointId);
  Serial.println("TEST:PASS");
}
// end::spotify-play-context-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyPlayContextCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyPlayContextCborResponse(payload, length);
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
