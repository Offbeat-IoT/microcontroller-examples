#include <AlexaExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::alexa-playback-command-docs[]
void applyAlexaPlaybackCommand(const char* endpointId, const char* playerControl) {
  Serial.print("Apply playback command for ");
  Serial.print(endpointId);
  Serial.print(": ");
  Serial.println(playerControl);

  if (strcmp(playerControl, "Play") == 0) {
    Serial.println("Start playback here");
  } else if (strcmp(playerControl, "Pause") == 0) {
    Serial.println("Pause playback here");
  } else if (strcmp(playerControl, "Stop") == 0) {
    Serial.println("Stop playback here");
  } else if (strcmp(playerControl, "Next") == 0) {
    Serial.println("Skip to the next item here");
  } else if (strcmp(playerControl, "Prev") == 0) {
    Serial.println("Go to the previous item here");
  } else {
    Serial.println("Unsupported Alexa playback command");
    return;
  }

  Serial.print("PLAYER_CONTROL=");
  Serial.println(playerControl);
}

void handleAlexaPlaybackCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::alexa::examples::ParseStatus status =
      offbeat::alexa::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::alexa::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Alexa playback command");
    return;
  }

  JsonVariantConst playerControlValue = root[offbeat::alexa::examples::kPlayerControlKey];
  if (playerControlValue.isNull()) {
    Serial.println("No Alexa playback payload");
    return;
  }

  applyAlexaPlaybackCommand(
      offbeat::alexa::examples::readEndpointId(root),
      offbeat::alexa::examples::readString(playerControlValue));
  offbeat::alexa::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::alexa-playback-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Alexa playback commands");
      break;
    case WStype_TEXT:
      handleAlexaPlaybackCommand(payload, length);
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
