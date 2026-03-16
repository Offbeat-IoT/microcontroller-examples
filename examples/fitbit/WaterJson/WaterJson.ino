#include <FitbitExampleSupport.h>
#include <FitbitJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::fitbit-get-water-json-docs[]
void sendFitbitGetWaterJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.get.water", "", body)) {
    Serial.println("Unable to build fitbit.get.water request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.get.water");
}

void handleFitbitGetWaterJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.water response");
    return;
  }

  JsonObjectConst water = root["fitbit.get.water"].as<JsonObjectConst>();
  if (water.isNull()) {
    Serial.println("No fitbit.get.water payload");
    return;
  }

  offbeat::fitbit::examples::json::printLine(
      "Water intake: ",
      offbeat::fitbit::examples::json::readDouble(water["water"]),
      1);
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-water-json-docs[]

// tag::fitbit-create-water-log-json-docs[]
constexpr char kCreateWaterAmount[] = "124";
constexpr char kCreateWaterUnit[] = "ml";

void sendFitbitCreateWaterLogJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildObjectRequest(
          "fitbit.create.water.log",
          body,
          [](JsonObject value) {
            value["amount"] = kCreateWaterAmount;
            value["unit"] = kCreateWaterUnit;
          })) {
    Serial.println("Unable to build fitbit.create.water.log request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.create.water.log");
}

void handleFitbitCreateWaterLogJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.create.water.log response");
    return;
  }

  JsonObjectConst response = root["fitbit.create.water.log"].as<JsonObjectConst>();
  if (response.isNull()) {
    Serial.println("No fitbit.create.water.log payload");
    return;
  }

  offbeat::fitbit::examples::json::printLine("Amount: ", kCreateWaterAmount);
  offbeat::fitbit::examples::json::printLine("Unit: ", kCreateWaterUnit);
  offbeat::fitbit::examples::json::printLine(
      "Result: ",
      offbeat::fitbit::examples::json::readString(response["result"]));
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-create-water-log-json-docs[]

// tag::fitbit-get-water-goal-json-docs[]
void sendFitbitGetWaterGoalJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.get.water.goal", "", body)) {
    Serial.println("Unable to build fitbit.get.water.goal request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.get.water.goal");
}

void handleFitbitGetWaterGoalJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.water.goal response");
    return;
  }

  JsonObjectConst waterGoal = root["fitbit.get.water.goal"].as<JsonObjectConst>();
  if (waterGoal.isNull()) {
    Serial.println("No fitbit.get.water.goal payload");
    return;
  }

  offbeat::fitbit::examples::json::printLine(
      "Goal: ",
      offbeat::fitbit::examples::json::readLong(waterGoal["goal"]));
  offbeat::fitbit::examples::json::printLine(
      "Start date: ",
      offbeat::fitbit::examples::json::readString(waterGoal["startDate"]));
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-water-goal-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendFitbitGetWaterJson(webSocket);
      break;
    case WStype_TEXT:
      handleFitbitGetWaterJsonResponse(payload, length);
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
