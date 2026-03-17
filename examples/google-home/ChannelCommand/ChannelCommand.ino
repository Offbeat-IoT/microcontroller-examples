#include <GoogleHomeExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::google-home-channel-command-docs[]
void applyGoogleHomeSetChannel(const char* endpointId, long channelNumber) {
  Serial.print("Set channel on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.println(channelNumber);

  Serial.print("SET_CHANNEL=");
  Serial.println(channelNumber);
}

void applyGoogleHomeSkipChannel(const char* endpointId, long channelOffset) {
  Serial.print("Skip channel on ");
  Serial.print(endpointId);
  Serial.print(" by ");
  Serial.println(channelOffset);

  Serial.print("SKIP_CHANNEL=");
  Serial.println(channelOffset);
}

void handleGoogleHomeChannelCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::google_home::examples::ParseStatus status =
      offbeat::google_home::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::google_home::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Google Home channel command");
    return;
  }

  const char* endpointId = offbeat::google_home::examples::readEndpointId(root);
  JsonVariantConst setChannelValue = root[offbeat::google_home::examples::kSetChannelKey];
  JsonVariantConst skipChannelValue = root[offbeat::google_home::examples::kSkipChannelKey];

  if (!setChannelValue.isNull()) {
    applyGoogleHomeSetChannel(endpointId, offbeat::google_home::examples::readLong(setChannelValue));
  } else if (!skipChannelValue.isNull()) {
    applyGoogleHomeSkipChannel(endpointId, offbeat::google_home::examples::readLong(skipChannelValue));
  } else {
    Serial.println("No Google Home channel payload");
    return;
  }

  offbeat::google_home::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::google-home-channel-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Google Home channel commands");
      break;
    case WStype_TEXT:
      handleGoogleHomeChannelCommand(payload, length);
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
