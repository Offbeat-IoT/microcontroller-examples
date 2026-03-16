#include <ArduinoJson.h>
#include <SpotifyExampleSupport.h>
#include <SpotifyPlaybackCommandJson.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-play-context-json-docs[]
// Replace the URI prefix with spotify:album:, spotify:artists:, or spotify:playlists:.
constexpr char kContextUri[] = "spotify:album:the context_uri";

void sendSpotifyPlayContextJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::buildPlaybackCommandJsonRequest("spotify.play.items", kContextUri, body)) {
    Serial.println("Unable to build spotify.play.items request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.play.items");
}

void handleSpotifyPlayContextJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<512> response;
  offbeat::spotify::SpotifyPlaybackCommandResult result;
  offbeat::spotify::SpotifyPlaybackCommandParseStatus status =
      offbeat::spotify::parsePlaybackCommandJsonResponse(
          payload, length, response, "spotify.play.items.response", result);

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
// end::spotify-play-context-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyPlayContextJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyPlayContextJsonResponse(payload, length);
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
