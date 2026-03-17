#include <AlexaExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::alexa-color-command-docs[]
void applyAlexaColorCommand(const char* endpointId, double hue, double saturation, double brightness) {
  Serial.print("Set color on ");
  Serial.println(endpointId);
  offbeat::alexa::examples::printLine("Hue: ", hue, 4);
  offbeat::alexa::examples::printLine("Saturation: ", saturation, 4);
  offbeat::alexa::examples::printLine("Brightness: ", brightness, 4);

  Serial.print("HUE=");
  Serial.println(hue, 4);
  Serial.print("SATURATION=");
  Serial.println(saturation, 4);
  Serial.print("BRIGHTNESS=");
  Serial.println(brightness, 4);
}

void handleAlexaColorCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::alexa::examples::ParseStatus status =
      offbeat::alexa::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::alexa::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Alexa color command");
    return;
  }

  JsonVariantConst hueValue = root[offbeat::alexa::examples::kHueKey];
  JsonVariantConst saturationValue = root[offbeat::alexa::examples::kSaturationKey];
  JsonVariantConst brightnessValue = root[offbeat::alexa::examples::kBrightnessKey];
  if (hueValue.isNull() || saturationValue.isNull() || brightnessValue.isNull()) {
    Serial.println("Incomplete Alexa color payload");
    return;
  }

  applyAlexaColorCommand(
      offbeat::alexa::examples::readEndpointId(root),
      offbeat::alexa::examples::readDouble(hueValue),
      offbeat::alexa::examples::readDouble(saturationValue),
      offbeat::alexa::examples::readDouble(brightnessValue));
  offbeat::alexa::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::alexa-color-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Alexa color commands");
      break;
    case WStype_TEXT:
      handleAlexaColorCommand(payload, length);
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("TEST:READY");
  if (!offbeat::alexa::examples::connectWifi(OFFBEAT_WIFI_SSID, OFFBEAT_WIFI_PASSWORD)) {
    return;
  }

  webSocket.begin(OFFBEAT_WS_HOST, OFFBEAT_WS_PORT, OFFBEAT_WS_PATH);
  webSocket.onEvent(websocketEvent);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();
}
