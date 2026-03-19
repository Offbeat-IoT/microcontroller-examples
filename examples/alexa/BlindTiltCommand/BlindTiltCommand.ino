#include <AlexaExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

namespace {

long clampPercent(long percent) {
  if (percent < 0) {
    return 0;
  }
  if (percent > 100) {
    return 100;
  }
  return percent;
}

long percentToDegrees(long percent) {
  return (clampPercent(percent) * 180L + 50L) / 100L;
}

}  // namespace

// tag::alexa-blind-tilt-command-docs[]
void applyAlexaBlindTiltPercent(const char* endpointId, long tiltPercent) {
  long clampedTiltPercent = clampPercent(tiltPercent);
  long tiltDegrees = percentToDegrees(clampedTiltPercent);

  Serial.print("Set blind tilt on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.print(clampedTiltPercent);
  Serial.println("%");

  Serial.print("TILT_PERCENT=");
  Serial.println(clampedTiltPercent);
  Serial.print("TILT_DEGREES=");
  Serial.println(tiltDegrees);
}

void adjustAlexaBlindTiltPercent(const char* endpointId, long tiltPercentDelta) {
  Serial.print("Adjust blind tilt on ");
  Serial.print(endpointId);
  Serial.print(" by ");
  Serial.print(tiltPercentDelta);
  Serial.println("%");

  Serial.print("TILT_DELTA_PERCENT=");
  Serial.println(tiltPercentDelta);
  Serial.println("Update your tracked tilt state before driving the motor.");
}

void handleAlexaBlindTiltCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::alexa::examples::ParseStatus status =
      offbeat::alexa::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::alexa::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Alexa blind tilt command");
    return;
  }

  const char* endpointId = offbeat::alexa::examples::readEndpointId(root);
  JsonVariantConst rangeValue = root[offbeat::alexa::examples::kRangeValueKey];
  JsonVariantConst rangeValueDelta = root[offbeat::alexa::examples::kRangeValueDeltaKey];

  if (!rangeValue.isNull()) {
    applyAlexaBlindTiltPercent(
        endpointId, offbeat::alexa::examples::readLong(rangeValue));
  } else if (!rangeValueDelta.isNull()) {
    adjustAlexaBlindTiltPercent(
        endpointId, offbeat::alexa::examples::readLong(rangeValueDelta));
  } else {
    Serial.println("No Alexa blind tilt payload");
    return;
  }

  offbeat::alexa::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::alexa-blind-tilt-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Alexa blind tilt commands");
      break;
    case WStype_TEXT:
      handleAlexaBlindTiltCommand(payload, length);
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
