#include <GoogleHomeExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::google-home-color-command-docs[]
void applyGoogleHomeColorCommand(const char* endpointId, double hue, double saturation, double brightness) {
  Serial.print("Set color on ");
  Serial.println(endpointId);
  offbeat::google_home::examples::printLine("Hue: ", hue, 2);
  offbeat::google_home::examples::printLine("Saturation: ", saturation, 2);
  offbeat::google_home::examples::printLine("Brightness: ", brightness, 2);

  Serial.print("HUE=");
  Serial.println(hue, 2);
  Serial.print("SATURATION=");
  Serial.println(saturation, 2);
  Serial.print("BRIGHTNESS=");
  Serial.println(brightness, 2);
}

void handleGoogleHomeColorCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::google_home::examples::ParseStatus status =
      offbeat::google_home::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::google_home::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Google Home color command");
    return;
  }

  JsonVariantConst hueValue = root[offbeat::google_home::examples::kHueKey];
  JsonVariantConst saturationValue = root[offbeat::google_home::examples::kSaturationKey];
  JsonVariantConst brightnessValue = root[offbeat::google_home::examples::kBrightnessKey];
  if (hueValue.isNull() || saturationValue.isNull() || brightnessValue.isNull()) {
    Serial.println("Incomplete Google Home color payload");
    return;
  }

  applyGoogleHomeColorCommand(
      offbeat::google_home::examples::readEndpointId(root),
      offbeat::google_home::examples::readDouble(hueValue),
      offbeat::google_home::examples::readDouble(saturationValue),
      offbeat::google_home::examples::readDouble(brightnessValue));
  offbeat::google_home::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::google-home-color-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Google Home color commands");
      break;
    case WStype_TEXT:
      handleGoogleHomeColorCommand(payload, length);
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("TEST:READY");
  if (!offbeat::google_home::examples::connectWifi(OFFBEAT_WIFI_SSID, OFFBEAT_WIFI_PASSWORD)) {
    return;
  }

  webSocket.begin(OFFBEAT_WS_HOST, OFFBEAT_WS_PORT, OFFBEAT_WS_PATH);
  webSocket.onEvent(websocketEvent);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();
}
