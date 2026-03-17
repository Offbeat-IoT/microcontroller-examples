#include <AlexaExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::alexa-speaker-command-docs[]
void applyAlexaSpeakerVolume(const char* endpointId, long volumePercent) {
  Serial.print("Set speaker volume on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.println(volumePercent);

  Serial.print("VOLUME=");
  Serial.println(volumePercent);
}

void applyAlexaSpeakerVolumeSteps(const char* endpointId, long volumeSteps) {
  Serial.print("Adjust speaker volume steps on ");
  Serial.print(endpointId);
  Serial.print(" by ");
  Serial.println(volumeSteps);

  Serial.print("VOLUME_STEPS=");
  Serial.println(volumeSteps);
}

void applyAlexaSpeakerMute(const char* endpointId, bool muted) {
  Serial.print("Set mute on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.println(muted ? "true" : "false");

  Serial.print("MUTE=");
  Serial.println(muted ? "true" : "false");
}

void handleAlexaSpeakerCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::alexa::examples::ParseStatus status =
      offbeat::alexa::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::alexa::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Alexa speaker command");
    return;
  }

  const char* endpointId = offbeat::alexa::examples::readEndpointId(root);
  JsonVariantConst volumeValue = root[offbeat::alexa::examples::kVolumeKey];
  JsonVariantConst volumeStepsValue = root[offbeat::alexa::examples::kVolumeStepsKey];
  JsonVariantConst muteValue = root[offbeat::alexa::examples::kMuteKey];

  if (!volumeValue.isNull()) {
    applyAlexaSpeakerVolume(endpointId, offbeat::alexa::examples::readLong(volumeValue));
  } else if (!volumeStepsValue.isNull()) {
    applyAlexaSpeakerVolumeSteps(endpointId, offbeat::alexa::examples::readLong(volumeStepsValue));
  } else if (!muteValue.isNull()) {
    applyAlexaSpeakerMute(endpointId, offbeat::alexa::examples::readBool(muteValue));
  } else {
    Serial.println("No Alexa speaker payload");
    return;
  }

  offbeat::alexa::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::alexa-speaker-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Alexa speaker commands");
      break;
    case WStype_TEXT:
      handleAlexaSpeakerCommand(payload, length);
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
