#include <FitbitExampleSupport.h>
#include <FitbitJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::fitbit-activities-json-docs[]
void sendFitbitActivitiesJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.activities", "", body)) {
    Serial.println("Unable to build fitbit.activities request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.activities");
}

void handleFitbitActivitiesJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.activities response");
    return;
  }

  offbeat::fitbit::examples::json::printLine(
      "Calories out: ",
      offbeat::fitbit::examples::json::readLong(root["caloriesOut"]));
  offbeat::fitbit::examples::json::printLine(
      "Activity calories: ",
      offbeat::fitbit::examples::json::readLong(root["activityCalories"]));
  offbeat::fitbit::examples::json::printLine(
      "Steps: ",
      offbeat::fitbit::examples::json::readLong(root["steps"]));
  offbeat::fitbit::examples::json::printLine(
      "Very active minutes: ",
      offbeat::fitbit::examples::json::readLong(root["veryActiveMinutes"]));
  offbeat::fitbit::examples::json::printLine(
      "Calories BMR: ",
      offbeat::fitbit::examples::json::readLong(root["caloriesBMR"]));
  offbeat::fitbit::examples::json::printLine(
      "Sedentary minutes: ",
      offbeat::fitbit::examples::json::readLong(root["sedentaryMinutes"]));
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-activities-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendFitbitActivitiesJson(webSocket);
      break;
    case WStype_TEXT:
      handleFitbitActivitiesJsonResponse(payload, length);
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
