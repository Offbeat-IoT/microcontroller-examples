#include <ArduinoCbor.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <offbeat/spotify/SpotifyGetDevicesCbor.h>

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

// tag::spotify-get-devices-cbor-docs[]
void sendSpotifyGetDevicesCbor(WebSocketsClient& socket) {
  uint8_t encoded[64];
  size_t encodedLength = offbeat::spotify::buildGetDevicesCborRequest(encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build spotify.devices request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
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

void handleSpotifyGetDevicesCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  offbeat::spotify::SpotifyGetDevicesParseStatus status =
      offbeat::spotify::visitGetDevicesCborResponse(payload, length, buffer, printSpotifyDevice);

  if (status == offbeat::spotify::SpotifyGetDevicesParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse spotify CBOR response");
    return;
  }

  if (status == offbeat::spotify::SpotifyGetDevicesParseStatus::kMissingResponse) {
    Serial.println("No spotify.devices.response payload");
    return;
  }

  Serial.println("TEST:PASS");
}
// end::spotify-get-devices-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendSpotifyGetDevicesCbor(webSocket);
      break;
    case WStype_BIN:
      handleSpotifyGetDevicesCborResponse(payload, length);
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
