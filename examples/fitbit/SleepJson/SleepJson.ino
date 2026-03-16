#include <FitbitExampleSupport.h>
#include <FitbitJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::fitbit-get-sleep-json-docs[]
void sendFitbitGetSleepJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.get.sleep", "", body)) {
    Serial.println("Unable to build fitbit.get.sleep request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.get.sleep");
}

void handleFitbitGetSleepJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.sleep response");
    return;
  }

  JsonObjectConst sleep = root["fitbit.get.sleep"].as<JsonObjectConst>();
  if (sleep.isNull()) {
    Serial.println("No fitbit.get.sleep payload");
    return;
  }

  offbeat::fitbit::examples::json::printLine(
      "Minutes asleep: ",
      offbeat::fitbit::examples::json::readLong(sleep["totalMinutesAsleep"]));
  offbeat::fitbit::examples::json::printLine(
      "Minutes awake: ",
      offbeat::fitbit::examples::json::readLong(sleep["stagesWake"]));
  offbeat::fitbit::examples::json::printLine(
      "Time in bed: ",
      offbeat::fitbit::examples::json::readLong(sleep["totalTimeInBed"]));
  offbeat::fitbit::examples::json::printLine(
      "Deep sleep: ",
      offbeat::fitbit::examples::json::readLong(sleep["stagesDeep"]));
  offbeat::fitbit::examples::json::printLine(
      "Light sleep: ",
      offbeat::fitbit::examples::json::readLong(sleep["stageLight"]));
  offbeat::fitbit::examples::json::printLine(
      "REM sleep: ",
      offbeat::fitbit::examples::json::readLong(sleep["stagesRem"]));
  offbeat::fitbit::examples::json::printLine(
      "Sleep records: ",
      offbeat::fitbit::examples::json::readLong(sleep["totalSleepRecords"]));
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-sleep-json-docs[]

// tag::fitbit-get-sleep-goal-json-docs[]
void sendFitbitGetSleepGoalJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.get.sleep.goal", "", body)) {
    Serial.println("Unable to build fitbit.get.sleep.goal request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.get.sleep.goal");
}

void handleFitbitGetSleepGoalJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.sleep.goal response");
    return;
  }

  JsonObjectConst sleepGoal = root["fitbit.get.sleep.goal"].as<JsonObjectConst>();
  if (sleepGoal.isNull()) {
    Serial.println("No fitbit.get.sleep.goal payload");
    return;
  }

  offbeat::fitbit::examples::json::printLine(
      "Minimum duration: ",
      offbeat::fitbit::examples::json::readLong(sleepGoal["goal.minDuration"]));
  offbeat::fitbit::examples::json::printLine(
      "Consistency flow ID: ",
      offbeat::fitbit::examples::json::readLong(sleepGoal["consistency.flowId"]));
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-sleep-goal-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendFitbitGetSleepJson(webSocket);
      break;
    case WStype_TEXT:
      handleFitbitGetSleepJsonResponse(payload, length);
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
