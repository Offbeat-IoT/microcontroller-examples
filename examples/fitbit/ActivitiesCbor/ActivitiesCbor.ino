#include <ArduinoCbor.h>
#include <FitbitCborExampleSupport.h>
#include <FitbitExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::fitbit-activities-cbor-docs[]
void sendFitbitActivitiesCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength =
      offbeat::fitbit::examples::cbor::buildStringRequest("fitbit.activities", "", encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.activities request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.activities");
}

void handleFitbitActivitiesCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.activities response");
    return;
  }

  offbeat::fitbit::examples::cbor::printLine(
      "Calories out: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(root, "caloriesOut")));
  offbeat::fitbit::examples::cbor::printLine(
      "Activity calories: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(root, "activityCalories")));
  offbeat::fitbit::examples::cbor::printLine(
      "Steps: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(root, "steps")));
  offbeat::fitbit::examples::cbor::printLine(
      "Very active minutes: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(root, "veryActiveMinutes")));
  offbeat::fitbit::examples::cbor::printLine(
      "Calories BMR: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(root, "caloriesBMR")));
  offbeat::fitbit::examples::cbor::printLine(
      "Sedentary minutes: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(root, "sedentaryMinutes")));
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-activities-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendFitbitActivitiesCbor(webSocket);
      break;
    case WStype_BIN:
      handleFitbitActivitiesCborResponse(payload, length);
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("TEST:READY");
  if (!offbeat::fitbit::examples::connectWifi(OFFBEAT_WIFI_SSID, OFFBEAT_WIFI_PASSWORD)) {
    return;
  }

  webSocket.begin(OFFBEAT_WS_HOST, OFFBEAT_WS_PORT, OFFBEAT_WS_PATH);
  webSocket.onEvent(websocketEvent);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();
}
