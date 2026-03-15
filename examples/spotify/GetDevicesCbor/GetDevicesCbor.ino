#include <ArduinoCbor.h>
#include <ESP8266WiFi.h>
#include <OffbeatMicrocontrollerExamples.h>
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

// tag::spotify-get-devices-cbor-docs[]
void sendSpotifyGetDevicesCbor(WebSocketsClient& socket) {
  CborBuffer buffer(64);
  CborObject payload(buffer);
  payload.set(offbeat::spotify::kDevicesCommand, "");

  uint8_t encoded[64];
  size_t encodedLength = payload.encode(encoded, sizeof(encoded));

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=spotify.devices");
}

void handleSpotifyGetDevicesCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor_errback err;
  cn_cbor* root = cn_cbor_decode(payload, length, &buffer.context, &err);
  if (root == NULL) {
    Serial.println("Unable to parse spotify CBOR response");
    return;
  }

  cn_cbor* devices = cn_cbor_mapget_string(root, offbeat::spotify::kDevicesResponse);
  if (devices == NULL || devices->type != CN_CBOR_MAP) {
    Serial.println("No spotify.devices.response payload");
    return;
  }

  for (cn_cbor* deviceEntry = devices->first_child;
       deviceEntry != NULL && deviceEntry->next != NULL;
       deviceEntry = deviceEntry->next->next) {
    const char* deviceId = deviceEntry->v.str;
    CborObject device(buffer, deviceEntry->next);
    const char* name = device.get("name").asString();
    long volume = device.get("volume").asInteger();

    Serial.print("Device id: ");
    Serial.println(deviceId != NULL ? deviceId : "unknown");

    Serial.print("Device name: ");
    Serial.println(name != NULL ? name : "unknown");

    Serial.print("Volume: ");
    Serial.println(volume);

    Serial.print("DEVICE_ID=");
    Serial.println(deviceId != NULL ? deviceId : "unknown");
    Serial.print("DEVICE_NAME=");
    Serial.println(name != NULL ? name : "unknown");
    Serial.print("VOLUME=");
    Serial.println(volume);
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
