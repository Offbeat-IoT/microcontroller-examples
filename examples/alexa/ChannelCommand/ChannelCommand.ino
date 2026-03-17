#include <AlexaExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::alexa-channel-command-docs[]
void applyAlexaSetChannel(const char* endpointId, long channelNumber) {
  Serial.print("Set channel on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.println(channelNumber);

  Serial.print("SET_CHANNEL=");
  Serial.println(channelNumber);
}

void applyAlexaSkipChannel(const char* endpointId, long channelOffset) {
  Serial.print("Skip channel on ");
  Serial.print(endpointId);
  Serial.print(" by ");
  Serial.println(channelOffset);

  Serial.print("SKIP_CHANNEL=");
  Serial.println(channelOffset);
}

void handleAlexaChannelCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::alexa::examples::ParseStatus status =
      offbeat::alexa::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::alexa::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Alexa channel command");
    return;
  }

  const char* endpointId = offbeat::alexa::examples::readEndpointId(root);
  JsonVariantConst setChannelValue = root[offbeat::alexa::examples::kSetChannelKey];
  JsonVariantConst skipChannelValue = root[offbeat::alexa::examples::kSkipChannelKey];

  if (!setChannelValue.isNull()) {
    applyAlexaSetChannel(endpointId, offbeat::alexa::examples::readLong(setChannelValue));
  } else if (!skipChannelValue.isNull()) {
    applyAlexaSkipChannel(endpointId, offbeat::alexa::examples::readLong(skipChannelValue));
  } else {
    Serial.println("No Alexa channel payload");
    return;
  }

  offbeat::alexa::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::alexa-channel-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Alexa channel commands");
      break;
    case WStype_TEXT:
      handleAlexaChannelCommand(payload, length);
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
