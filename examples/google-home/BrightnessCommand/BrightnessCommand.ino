#include <GoogleHomeExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::google-home-brightness-command-docs[]
void applyGoogleHomeBrightnessPercent(const char* endpointId, long brightnessPercent) {
  Serial.print("Set brightness percent on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.println(brightnessPercent);

  Serial.print("BRIGHTNESS_PERCENT=");
  Serial.println(brightnessPercent);
}

void applyGoogleHomeBrightnessWeight(const char* endpointId, long brightnessWeight) {
  Serial.print("Adjust brightness weight on ");
  Serial.print(endpointId);
  Serial.print(" by ");
  Serial.println(brightnessWeight);

  Serial.print("BRIGHTNESS_WEIGHT=");
  Serial.println(brightnessWeight);
}

void applyGoogleHomeBrightnessAbsolute(const char* endpointId, long brightnessValue) {
  Serial.print("Set absolute brightness on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.println(brightnessValue);

  Serial.print("BRIGHTNESS=");
  Serial.println(brightnessValue);
}

void handleGoogleHomeBrightnessCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::google_home::examples::ParseStatus status =
      offbeat::google_home::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::google_home::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Google Home brightness command");
    return;
  }

  const char* endpointId = offbeat::google_home::examples::readEndpointId(root);
  JsonVariantConst percentValue = root[offbeat::google_home::examples::kAdjustBrightnessPercentKey];
  JsonVariantConst weightValue = root[offbeat::google_home::examples::kAdjustBrightnessWeightKey];
  JsonVariantConst brightnessValue = root[offbeat::google_home::examples::kBrightnessKey];

  if (!percentValue.isNull()) {
    applyGoogleHomeBrightnessPercent(endpointId, offbeat::google_home::examples::readLong(percentValue));
  } else if (!weightValue.isNull()) {
    applyGoogleHomeBrightnessWeight(endpointId, offbeat::google_home::examples::readLong(weightValue));
  } else if (!brightnessValue.isNull()) {
    applyGoogleHomeBrightnessAbsolute(endpointId, offbeat::google_home::examples::readLong(brightnessValue));
  } else {
    Serial.println("No Google Home brightness payload");
    return;
  }

  offbeat::google_home::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::google-home-brightness-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Google Home brightness commands");
      break;
    case WStype_TEXT:
      handleGoogleHomeBrightnessCommand(payload, length);
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
