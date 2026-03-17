#include <GoogleHomeExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::google-home-media-command-docs[]
void applyGoogleHomePlayerControl(const char* endpointId, const char* playerControl) {
  Serial.print("Apply media command for ");
  Serial.print(endpointId);
  Serial.print(": ");
  Serial.println(playerControl);

  Serial.print("PLAYER_CONTROL=");
  Serial.println(playerControl);
}

void applyGoogleHomeSeekAbsolute(const char* endpointId, long absolutePositionMs) {
  Serial.print("Seek absolute on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.println(absolutePositionMs);

  Serial.print("SEEK_ABSOLUTE_MS=");
  Serial.println(absolutePositionMs);
}

void applyGoogleHomeSeekRelative(const char* endpointId, long relativePositionMs) {
  Serial.print("Seek relative on ");
  Serial.print(endpointId);
  Serial.print(" by ");
  Serial.println(relativePositionMs);

  Serial.print("SEEK_RELATIVE_MS=");
  Serial.println(relativePositionMs);
}

void handleGoogleHomeMediaCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::google_home::examples::ParseStatus status =
      offbeat::google_home::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::google_home::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Google Home media command");
    return;
  }

  const char* endpointId = offbeat::google_home::examples::readEndpointId(root);
  JsonVariantConst playerControlValue = root[offbeat::google_home::examples::kPlayerControlKey];
  JsonVariantConst seekAbsoluteValue = root[offbeat::google_home::examples::kSeekAbsoluteKey];
  JsonVariantConst seekRelativeValue = root[offbeat::google_home::examples::kSeekRelativeKey];

  if (!playerControlValue.isNull()) {
    applyGoogleHomePlayerControl(endpointId, offbeat::google_home::examples::readString(playerControlValue));
  } else if (!seekAbsoluteValue.isNull()) {
    applyGoogleHomeSeekAbsolute(endpointId, offbeat::google_home::examples::readLong(seekAbsoluteValue));
  } else if (!seekRelativeValue.isNull()) {
    applyGoogleHomeSeekRelative(endpointId, offbeat::google_home::examples::readLong(seekRelativeValue));
  } else {
    Serial.println("No Google Home media payload");
    return;
  }

  offbeat::google_home::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::google-home-media-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Google Home media commands");
      break;
    case WStype_TEXT:
      handleGoogleHomeMediaCommand(payload, length);
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
