#include <ArduinoJson.h>
#include <SpotifyExampleSupport.h>
#include <SpotifyPlaybackCommandJson.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::spotify-play-items-on-device-json-docs[]
constexpr char kDeviceId[] = "the id";
constexpr char kTrackUri[] = "spotify:track:playing on device";

void sendSpotifyPlayItemsOnDeviceJson(WebSocketsClient& socket) {
  StaticJsonDocument<256> payload;
  payload["spotify.play.items"] = kTrackUri;
  payload["spotify.play.on"] = kDeviceId;

  String body;
  if (serializeJson(payload, body) == 0) {
    Serial.println("Unable to build spotify.play.items request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.play.items");
  Serial.println("REQUEST_SENT=spotify.play.on");
}

void handleSpotifyPlayItemsOnDeviceJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<512> response;
  offbeat::spotify::SpotifyPlaybackCommandResult result;
  offbeat::spotify::SpotifyPlaybackCommandParseStatus status =
      offbeat::spotify::parsePlaybackCommandJsonResponse(
          payload, length, response, "spotify.play.on.response", result);

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify play.on response");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kMissingResponse) {
    Serial.println("No spotify.play.on.response payload");
    return;
  }

  if (status == offbeat::spotify::SpotifyPlaybackCommandParseStatus::kMissingResult) {
    Serial.println("No result in spotify.play.on.response payload");
    return;
  }

  Serial.print("Device ID: ");
  Serial.println(kDeviceId);
  Serial.print("Track URI: ");
  Serial.println(kTrackUri);
  Serial.print("Result: ");
  Serial.println(result.result);
  Serial.print("Endpoint ID: ");
  Serial.println(result.endpointId);
  Serial.print("DEVICE_ID=");
  Serial.println(kDeviceId);
  Serial.print("TRACK_URI=");
  Serial.println(kTrackUri);
  Serial.print("RESULT=");
  Serial.println(result.result);
  Serial.print("ENDPOINT_ID=");
  Serial.println(result.endpointId);
  Serial.println("TEST:PASS");
}
// end::spotify-play-items-on-device-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyPlayItemsOnDeviceJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyPlayItemsOnDeviceJsonResponse(payload, length);
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
