#include <GoogleHomeExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::google-home-power-command-docs[]
void applyGoogleHomePowerState(const char* endpointId, const char* powerState) {
  Serial.print("Apply Google Home power command for ");
  Serial.print(endpointId);
  Serial.print(": ");
  Serial.println(powerState);

  if (strcmp(powerState, "TurnOn") == 0) {
    Serial.println("Turn your output on here");
  } else if (strcmp(powerState, "TurnOff") == 0) {
    Serial.println("Turn your output off here");
  } else {
    Serial.println("Unsupported Google Home power command");
    return;
  }

  Serial.print("POWERSTATE=");
  Serial.println(powerState);
}

void handleGoogleHomePowerCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::google_home::examples::ParseStatus status =
      offbeat::google_home::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::google_home::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Google Home power command");
    return;
  }

  JsonVariantConst powerStateValue = root[offbeat::google_home::examples::kPowerStateKey];
  if (powerStateValue.isNull()) {
    Serial.println("No Google Home powerstate payload");
    return;
  }

  applyGoogleHomePowerState(
      offbeat::google_home::examples::readEndpointId(root),
      offbeat::google_home::examples::readString(powerStateValue));
  offbeat::google_home::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::google-home-power-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Google Home power commands");
      break;
    case WStype_TEXT:
      handleGoogleHomePowerCommand(payload, length);
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
