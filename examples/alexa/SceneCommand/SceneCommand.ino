#include <AlexaExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::alexa-scene-command-docs[]
void applyAlexaSceneState(const char* endpointId, const char* sceneState) {
  Serial.print("Apply scene command for ");
  Serial.print(endpointId);
  Serial.print(": ");
  Serial.println(sceneState);

  if (strcmp(sceneState, "TurnOn") == 0) {
    Serial.println("Activate the scene here");
  } else if (strcmp(sceneState, "TurnOff") == 0) {
    Serial.println("Deactivate the scene here");
  } else {
    Serial.println("Unsupported Alexa scene command");
    return;
  }

  Serial.print("SCENESTATE=");
  Serial.println(sceneState);
}

void handleAlexaSceneCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::alexa::examples::ParseStatus status =
      offbeat::alexa::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::alexa::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Alexa scene command");
    return;
  }

  JsonVariantConst sceneStateValue = root[offbeat::alexa::examples::kSceneStateKey];
  if (sceneStateValue.isNull()) {
    Serial.println("No Alexa scene payload");
    return;
  }

  applyAlexaSceneState(
      offbeat::alexa::examples::readEndpointId(root),
      offbeat::alexa::examples::readString(sceneStateValue));
  offbeat::alexa::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::alexa-scene-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Alexa scene commands");
      break;
    case WStype_TEXT:
      handleAlexaSceneCommand(payload, length);
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
