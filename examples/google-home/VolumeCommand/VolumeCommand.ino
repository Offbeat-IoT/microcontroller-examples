#include <GoogleHomeExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::google-home-volume-command-docs[]
void applyGoogleHomeSetVolume(const char* endpointId, long volume) {
  Serial.print("Set volume on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.println(volume);

  Serial.print("VOLUME=");
  Serial.println(volume);
}

void applyGoogleHomeAdjustVolume(const char* endpointId, long volumeSteps) {
  Serial.print("Adjust volume on ");
  Serial.print(endpointId);
  Serial.print(" by ");
  Serial.println(volumeSteps);

  Serial.print("VOLUME_STEPS=");
  Serial.println(volumeSteps);
}

void handleGoogleHomeVolumeCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::google_home::examples::ParseStatus status =
      offbeat::google_home::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::google_home::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Google Home volume command");
    return;
  }

  const char* endpointId = offbeat::google_home::examples::readEndpointId(root);
  JsonVariantConst volumeValue = root[offbeat::google_home::examples::kVolumeKey];
  JsonVariantConst volumeStepsValue = root[offbeat::google_home::examples::kVolumeStepsKey];

  if (!volumeValue.isNull()) {
    applyGoogleHomeSetVolume(endpointId, offbeat::google_home::examples::readLong(volumeValue));
  } else if (!volumeStepsValue.isNull()) {
    applyGoogleHomeAdjustVolume(endpointId, offbeat::google_home::examples::readLong(volumeStepsValue));
  } else {
    Serial.println("No Google Home volume payload");
    return;
  }

  offbeat::google_home::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::google-home-volume-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Google Home volume commands");
      break;
    case WStype_TEXT:
      handleGoogleHomeVolumeCommand(payload, length);
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
