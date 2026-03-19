#include <GoogleHomeExampleSupport.h>
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

long clampDegrees(long degrees) {
  if (degrees < 0) {
    return 0;
  }
  if (degrees > 180) {
    return 180;
  }
  return degrees;
}

long percentToDegrees(long percent) {
  return (clampPercent(percent) * 180L + 50L) / 100L;
}

long degreesToPercent(long degrees) {
  return (clampDegrees(degrees) * 100L + 90L) / 180L;
}

}  // namespace

// tag::google-home-blind-tilt-command-docs[]
void applyGoogleHomeBlindTiltPercent(const char* endpointId, long tiltPercent) {
  long clampedTiltPercent = clampPercent(tiltPercent);
  long tiltDegrees = percentToDegrees(clampedTiltPercent);

  Serial.print("Set Google Home blind tilt on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.print(clampedTiltPercent);
  Serial.println("%");

  Serial.print("TILT_PERCENT=");
  Serial.println(clampedTiltPercent);
  Serial.print("TILT_DEGREES=");
  Serial.println(tiltDegrees);
}

void applyGoogleHomeBlindTiltDegrees(const char* endpointId, long tiltDegrees) {
  long clampedTiltDegrees = clampDegrees(tiltDegrees);
  long tiltPercent = degreesToPercent(clampedTiltDegrees);

  Serial.print("Set Google Home blind tilt on ");
  Serial.print(endpointId);
  Serial.print(" to ");
  Serial.print(clampedTiltDegrees);
  Serial.println(" degrees");

  Serial.print("TILT_DEGREES=");
  Serial.println(clampedTiltDegrees);
  Serial.print("TILT_PERCENT=");
  Serial.println(tiltPercent);
}

void handleGoogleHomeBlindTiltCommand(uint8_t* payload, size_t length) {
  StaticJsonDocument<256> document;
  JsonObjectConst root;
  offbeat::google_home::examples::ParseStatus status =
      offbeat::google_home::examples::parseRoot(payload, length, document, root);

  if (status == offbeat::google_home::examples::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse Google Home blind tilt command");
    return;
  }

  const char* endpointId = offbeat::google_home::examples::readEndpointId(root);
  JsonVariantConst rotationPercent = root[offbeat::google_home::examples::kRotationPercentKey];
  JsonVariantConst rotationDegrees = root[offbeat::google_home::examples::kRotationDegreesKey];

  if (!rotationPercent.isNull()) {
    applyGoogleHomeBlindTiltPercent(
        endpointId, offbeat::google_home::examples::readLong(rotationPercent));
  } else if (!rotationDegrees.isNull()) {
    applyGoogleHomeBlindTiltDegrees(
        endpointId, offbeat::google_home::examples::readLong(rotationDegrees));
  } else {
    Serial.println("No Google Home blind tilt payload");
    return;
  }

  offbeat::google_home::examples::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::google-home-blind-tilt-command-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      Serial.println("Waiting for Google Home blind tilt commands");
      break;
    case WStype_TEXT:
      handleGoogleHomeBlindTiltCommand(payload, length);
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
