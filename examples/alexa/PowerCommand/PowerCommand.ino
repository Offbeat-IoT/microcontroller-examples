#include <AlexaExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::alexa-power-command-docs[]
void applyAlexaPowerState(const char* endpointId, const char* powerState) {
  Serial.print("Apply Alexa power command for ");
  Serial.print(endpointId);
  Serial.print(": ");
  Serial.println(powerState);

  if (strcmp(powerState, "TurnOn") == 0) {
    Serial.println("Turn your relay or transistor on here");
  } else if (strcmp(powerState, "TurnOff") == 0) {
    Serial.println("Turn your relay or transistor off here");
  } else {
    Serial.println("Unsupported Alexa power command");
    return;
  }

  Serial.print("POWERSTATE=");
  Serial.println(powerState);
}

void handleAlexaPowerCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::alexa::examples::ParseStatus status =
      offbeat::alexa::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::alexa::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Alexa power command");
    return;
  }

  JsonVariantConst powerStateValue = root[offbeat::alexa::examples::kPowerStateKey];
  if (powerStateValue.isNull()) {
    Serial.println("No Alexa powerstate payload");
    return;
  }

  applyAlexaPowerState(
      offbeat::alexa::examples::readEndpointId(root),
      offbeat::alexa::examples::readString(powerStateValue));
  offbeat::alexa::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::alexa-power-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Alexa power commands");
      break;
    case WStype_TEXT:
      handleAlexaPowerCommand(payload, length);
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
