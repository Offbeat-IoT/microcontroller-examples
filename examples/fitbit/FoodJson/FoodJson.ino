#include <FitbitExampleSupport.h>
#include <FitbitJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::fitbit-create-food-log-json-docs[]
constexpr char kCreateFoodAmount[] = "5";
constexpr long kCreateFoodId = 5678;
constexpr long kCreateFoodMealTypeId = 1;
constexpr char kCreateFoodUnitId[] = "ml";

void sendFitbitCreateFoodLogJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildObjectRequest(
          "fitbit.create.food.log",
          body,
          [](JsonObject value) {
            value["amount"] = kCreateFoodAmount;
            value["foodId"] = kCreateFoodId;
            value["mealTypeId"] = kCreateFoodMealTypeId;
            value["unitId"] = kCreateFoodUnitId;
          })) {
    Serial.println("Unable to build fitbit.create.food.log request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.create.food.log");
}

void handleFitbitCreateFoodLogJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.create.food.log response");
    return;
  }

  JsonObjectConst response = root["fitbit.create.food.log"].as<JsonObjectConst>();
  if (response.isNull()) {
    Serial.println("No fitbit.create.food.log payload");
    return;
  }

  offbeat::fitbit::examples::json::printLine("Food ID: ", kCreateFoodId);
  offbeat::fitbit::examples::json::printLine("Meal type ID: ", kCreateFoodMealTypeId);
  offbeat::fitbit::examples::json::printLine("Amount: ", kCreateFoodAmount);
  offbeat::fitbit::examples::json::printLine("Unit ID: ", kCreateFoodUnitId);
  offbeat::fitbit::examples::json::printLine(
      "Result: ",
      offbeat::fitbit::examples::json::readString(response["result"]));
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-create-food-log-json-docs[]

// tag::fitbit-get-food-log-json-docs[]
void sendFitbitGetFoodLogJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.food", "", body)) {
    Serial.println("Unable to build fitbit.food request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.food");
}

void handleFitbitGetFoodLogJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.food response");
    return;
  }

  JsonObjectConst foodLog = root["fitbit.food.log"].as<JsonObjectConst>();
  if (foodLog.isNull()) {
    Serial.println("No fitbit.food.log payload");
    return;
  }

  offbeat::fitbit::examples::json::printLine(
      "Calories: ",
      offbeat::fitbit::examples::json::readLong(foodLog["calories"]));
  offbeat::fitbit::examples::json::printLine(
      "Carbs: ",
      offbeat::fitbit::examples::json::readLong(foodLog["carbs"]));
  offbeat::fitbit::examples::json::printLine(
      "Fat: ",
      offbeat::fitbit::examples::json::readDouble(foodLog["fat"]),
      1);
  offbeat::fitbit::examples::json::printLine(
      "Fiber: ",
      offbeat::fitbit::examples::json::readLong(foodLog["fiber"]));
  offbeat::fitbit::examples::json::printLine(
      "Protein: ",
      offbeat::fitbit::examples::json::readLong(foodLog["protein"]));
  offbeat::fitbit::examples::json::printLine(
      "Sodium: ",
      offbeat::fitbit::examples::json::readLong(foodLog["sodium"]));
  offbeat::fitbit::examples::json::printLine(
      "Water: ",
      offbeat::fitbit::examples::json::readLong(foodLog["water"]));
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-food-log-json-docs[]

// tag::fitbit-get-food-goal-json-docs[]
void sendFitbitGetFoodGoalJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.get.food.goal", "", body)) {
    Serial.println("Unable to build fitbit.get.food.goal request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.get.food.goal");
}

void handleFitbitGetFoodGoalJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.food.goal response");
    return;
  }

  JsonObjectConst foodGoal = root["fitbit.food.goal"].as<JsonObjectConst>();
  if (foodGoal.isNull()) {
    Serial.println("No fitbit.food.goal payload");
    return;
  }

  offbeat::fitbit::examples::json::printLine(
      "Daily calorie goal: ",
      offbeat::fitbit::examples::json::readLong(foodGoal["calories"]));
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-food-goal-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendFitbitCreateFoodLogJson(webSocket);
      break;
    case WStype_TEXT:
      handleFitbitCreateFoodLogJsonResponse(payload, length);
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
