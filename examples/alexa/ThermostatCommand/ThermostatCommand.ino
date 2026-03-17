#include <AlexaExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::alexa-thermostat-command-docs[]
void applyAlexaThermostatMode(const char* endpointId, const char* thermostatMode) {
  Serial.print("Set thermostat mode on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.println(thermostatMode);

  Serial.print("THERMOSTAT_MODE=");
  Serial.println(thermostatMode);
}

void handleAlexaThermostatCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::alexa::examples::ParseStatus status =
      offbeat::alexa::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::alexa::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Alexa thermostat command");
    return;
  }

  JsonVariantConst thermostatModeValue = root[offbeat::alexa::examples::kThermostatModeKey];
  if (thermostatModeValue.isNull()) {
    Serial.println("No Alexa thermostat payload");
    return;
  }

  applyAlexaThermostatMode(
      offbeat::alexa::examples::readEndpointId(root),
      offbeat::alexa::examples::readString(thermostatModeValue));
  offbeat::alexa::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::alexa-thermostat-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Alexa thermostat commands");
      break;
    case WStype_TEXT:
      handleAlexaThermostatCommand(payload, length);
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
