#include <ArduinoCbor.h>
#include <FitbitCborExampleSupport.h>
#include <FitbitExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::fitbit-get-sleep-cbor-docs[]
void sendFitbitGetSleepCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength =
      offbeat::fitbit::examples::cbor::buildStringRequest("fitbit.get.sleep", "", encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.get.sleep request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.get.sleep");
}

void handleFitbitGetSleepCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.sleep response");
    return;
  }

  cn_cbor* sleep = offbeat::fitbit::examples::cbor::findField(root, "fitbit.get.sleep");
  if (sleep == NULL || sleep->type != CN_CBOR_MAP) {
    Serial.println("No fitbit.get.sleep payload");
    return;
  }

  offbeat::fitbit::examples::cbor::printLine(
      "Minutes asleep: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(sleep, "totalMinutesAsleep")));
  offbeat::fitbit::examples::cbor::printLine(
      "Minutes awake: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(sleep, "stagesWake")));
  offbeat::fitbit::examples::cbor::printLine(
      "Time in bed: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(sleep, "totalTimeInBed")));
  offbeat::fitbit::examples::cbor::printLine(
      "Deep sleep: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(sleep, "stagesDeep")));
  offbeat::fitbit::examples::cbor::printLine(
      "Light sleep: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(sleep, "stageLight")));
  offbeat::fitbit::examples::cbor::printLine(
      "REM sleep: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(sleep, "stagesRem")));
  offbeat::fitbit::examples::cbor::printLine(
      "Sleep records: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(sleep, "totalSleepRecords")));
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-sleep-cbor-docs[]

// tag::fitbit-get-sleep-goal-cbor-docs[]
void sendFitbitGetSleepGoalCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength =
      offbeat::fitbit::examples::cbor::buildStringRequest("fitbit.get.sleep.goal", "", encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.get.sleep.goal request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.get.sleep.goal");
}

void handleFitbitGetSleepGoalCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.sleep.goal response");
    return;
  }

  cn_cbor* sleepGoal = offbeat::fitbit::examples::cbor::findField(root, "fitbit.get.sleep.goal");
  if (sleepGoal == NULL || sleepGoal->type != CN_CBOR_MAP) {
    Serial.println("No fitbit.get.sleep.goal payload");
    return;
  }

  offbeat::fitbit::examples::cbor::printLine(
      "Minimum duration: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(sleepGoal, "goal.minDuration")));
  offbeat::fitbit::examples::cbor::printLine(
      "Consistency flow ID: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(sleepGoal, "consistency.flowId")));
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-sleep-goal-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendFitbitGetSleepCbor(webSocket);
      break;
    case WStype_BIN:
      handleFitbitGetSleepCborResponse(payload, length);
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
