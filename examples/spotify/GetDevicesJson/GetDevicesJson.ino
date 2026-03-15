#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SpotifyGetDevicesJson.h>
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

// tag::spotify-get-devices-json-docs[]
void sendSpotifyGetDevicesJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::spotify::buildGetDevicesJsonRequest(body)) {
    Serial.println("Unable to build spotify.devices request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=spotify.devices");
}

void printSpotifyDevice(const offbeat::spotify::SpotifyDevice& device) {
  Serial.print("Device id: ");
  Serial.println(device.id);

  Serial.print("Device name: ");
  Serial.println(device.name);

  Serial.print("Volume: ");
  Serial.println(device.volume);

  Serial.print("DEVICE_ID=");
  Serial.println(device.id);
  Serial.print("DEVICE_NAME=");
  Serial.println(device.name);
  Serial.print("VOLUME=");
  Serial.println(device.volume);
}

void handleSpotifyGetDevicesJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<2048> response;
  offbeat::spotify::SpotifyGetDevicesParseStatus status =
      offbeat::spotify::visitGetDevicesJsonResponse(payload, length, response, printSpotifyDevice);

  if (status == offbeat::spotify::SpotifyGetDevicesParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify response");
    return;
  }

  if (status == offbeat::spotify::SpotifyGetDevicesParseStatus::kMissingResponse) {
    Serial.println("No spotify.devices.response payload");
    return;
  }

  Serial.println("TEST:PASS");
}
// end::spotify-get-devices-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetDevicesJson(webSocket);
      break;
    case WStype_TEXT:
      handleSpotifyGetDevicesJsonResponse(payload, length);
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
