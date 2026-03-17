#include <AlexaExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::alexa-brightness-command-docs[]
void applyAlexaBrightnessPercent(const char* endpointId, long brightnessPercent) {
  Serial.print("Set brightness percent on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.println(brightnessPercent);

  Serial.print("BRIGHTNESS_PERCENT=");
  Serial.println(brightnessPercent);
}

void applyAlexaBrightnessWeight(const char* endpointId, long brightnessWeight) {
  Serial.print("Adjust brightness weight on ");
  Serial.print(endpointId);
  Serial.print(" by ");
  Serial.println(brightnessWeight);

  Serial.print("BRIGHTNESS_WEIGHT=");
  Serial.println(brightnessWeight);
}

void handleAlexaBrightnessCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::alexa::examples::ParseStatus status =
      offbeat::alexa::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::alexa::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Alexa brightness command");
    return;
  }

  const char* endpointId = offbeat::alexa::examples::readEndpointId(root);
  JsonVariantConst brightnessPercent = root[offbeat::alexa::examples::kAdjustBrightnessPercentKey];
  JsonVariantConst brightnessWeight = root[offbeat::alexa::examples::kAdjustBrightnessWeightKey];

  if (!brightnessPercent.isNull()) {
    applyAlexaBrightnessPercent(endpointId, offbeat::alexa::examples::readLong(brightnessPercent));
  } else if (!brightnessWeight.isNull()) {
    applyAlexaBrightnessWeight(endpointId, offbeat::alexa::examples::readLong(brightnessWeight));
  } else {
    Serial.println("No Alexa brightness payload");
    return;
  }

  offbeat::alexa::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::alexa-brightness-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Alexa brightness commands");
      break;
    case WStype_TEXT:
      handleAlexaBrightnessCommand(payload, length);
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
