#include <ArduinoJson.h>
#include <SpotifyExampleSupport.h>
#include <SpotifyPlaybackCommandJson.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-play-uris-json-docs[]
// Use one or more track URIs in the array.
constexpr const char* kTrackUris[] = {
    "spotify:track:track1",
    "spotify:track:track2",
};

void sendSpotifyPlayUrisJson(WebSocketsClient& socket) {
  StaticJsonDocument<256> payload;
  JsonArray trackUris = payload.createNestedArray("spotify.play.items");
  for (const char* trackUri : kTrackUris) {
    trackUris.add(trackUri);
  }

  String body;
  if (serializeJson(payload, body) == 0) {
    Serial.println("Unable to build spotify.play.items request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.play.items");
}

void handleSpotifyPlayUrisJsonResponse(uint8_t* payload, size_t length) {
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

  for (const char* trackUri : kTrackUris) {
    Serial.print("Track URI: ");
    Serial.println(trackUri);
    Serial.print("TRACK_URI=");
    Serial.println(trackUri);
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
// end::spotify-play-uris-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyPlayUrisJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyPlayUrisJsonResponse(payload, length);
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
