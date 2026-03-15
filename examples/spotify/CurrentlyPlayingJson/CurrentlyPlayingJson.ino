#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SpotifyPlaybackStateJson.h>
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

// tag::spotify-currently-playing-json-docs[]
void sendSpotifyCurrentlyPlayingJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::buildCurrentlyPlayingJsonRequest(body)) {
    Serial.println("Unable to build spotify.currently-playing request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.currently-playing");
}

void printSpotifyPlaybackState(const offbeat::spotify::SpotifyPlaybackState& playbackState) {
  Serial.print("Playing: ");
  Serial.println(playbackState.isPlaying ? "true" : "false");

  Serial.print("Track name: ");
  Serial.println(playbackState.item.name);

  Serial.print("Artist: ");
  Serial.println(playbackState.item.artist);

  Serial.print("Album: ");
  Serial.println(playbackState.item.album);

  Serial.print("Device name: ");
  Serial.println(playbackState.device.name);

  Serial.print("Volume percent: ");
  Serial.println(playbackState.device.volumePercent);

  Serial.print("PLAYING=");
  Serial.println(playbackState.isPlaying ? "true" : "false");
  Serial.print("TRACK_NAME=");
  Serial.println(playbackState.item.name);
  Serial.print("TRACK_ARTIST=");
  Serial.println(playbackState.item.artist);
  Serial.print("TRACK_ALBUM=");
  Serial.println(playbackState.item.album);
  Serial.print("DEVICE_NAME=");
  Serial.println(playbackState.device.name);
  Serial.print("VOLUME_PERCENT=");
  Serial.println(playbackState.device.volumePercent);
}

void handleSpotifyCurrentlyPlayingJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<2048> response;
  offbeat::spotify::SpotifyPlaybackState playbackState;
  offbeat::spotify::SpotifyPlaybackStateParseStatus status =
      offbeat::spotify::parseCurrentlyPlayingJsonResponse(payload, length, response, playbackState);

  if (status == offbeat::spotify::SpotifyPlaybackStateParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify currently-playing response");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackStateParseStatus::kMissingResponse) {
    Serial.println("No spotify.currently-playing.response payload");
    return;
  }

  printSpotifyPlaybackState(playbackState);
  Serial.println("TEST:PASS");
}
// end::spotify-currently-playing-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyCurrentlyPlayingJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyCurrentlyPlayingJsonResponse(payload, length);
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
