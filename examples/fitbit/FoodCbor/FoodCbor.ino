#include <ArduinoCbor.h>
#include <FitbitCborExampleSupport.h>
#include <FitbitExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::fitbit-create-food-log-cbor-docs[]
constexpr char kCreateFoodAmountCbor[] = "5";
constexpr long kCreateFoodIdCbor = 5678;
constexpr long kCreateFoodMealTypeIdCbor = 1;
constexpr char kCreateFoodUnitIdCbor[] = "ml";

void sendFitbitCreateFoodLogCbor(WebSocketsClient& socket) {
  uint8_t encoded[192];
  size_t encodedLength = offbeat::fitbit::examples::cbor::buildObjectRequest(
      "fitbit.create.food.log",
      encoded,
      sizeof(encoded),
      [](CborObject& value) {
        value.set("amount", kCreateFoodAmountCbor);
        value.set("foodId", static_cast<long>(kCreateFoodIdCbor));
        value.set("mealTypeId", static_cast<long>(kCreateFoodMealTypeIdCbor));
        value.set("unitId", kCreateFoodUnitIdCbor);
      });
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.create.food.log request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.create.food.log");
}

void handleFitbitCreateFoodLogCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.create.food.log response");
    return;
  }

  cn_cbor* response = offbeat::fitbit::examples::cbor::findField(root, "fitbit.create.food.log");
  if (response == NULL || response->type != CN_CBOR_MAP) {
    Serial.println("No fitbit.create.food.log payload");
    return;
  }

  offbeat::fitbit::examples::cbor::printLine("Food ID: ", kCreateFoodIdCbor);
  offbeat::fitbit::examples::cbor::printLine("Meal type ID: ", kCreateFoodMealTypeIdCbor);
  offbeat::fitbit::examples::cbor::printLine("Amount: ", kCreateFoodAmountCbor);
  offbeat::fitbit::examples::cbor::printLine("Unit ID: ", kCreateFoodUnitIdCbor);
  offbeat::fitbit::examples::cbor::printLine(
      "Result: ",
      offbeat::fitbit::examples::cbor::readString(offbeat::fitbit::examples::cbor::findField(response, "result")));
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-create-food-log-cbor-docs[]

// tag::fitbit-get-food-log-cbor-docs[]
void sendFitbitGetFoodLogCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength =
      offbeat::fitbit::examples::cbor::buildStringRequest("fitbit.food", "", encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.food request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.food");
}

void handleFitbitGetFoodLogCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.food response");
    return;
  }

  cn_cbor* foodLog = offbeat::fitbit::examples::cbor::findField(root, "fitbit.food.log");
  if (foodLog == NULL || foodLog->type != CN_CBOR_MAP) {
    Serial.println("No fitbit.food.log payload");
    return;
  }

  offbeat::fitbit::examples::cbor::printLine(
      "Calories: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(foodLog, "calories")));
  offbeat::fitbit::examples::cbor::printLine(
      "Carbs: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(foodLog, "carbs")));
  offbeat::fitbit::examples::cbor::printLine(
      "Fat: ",
      offbeat::fitbit::examples::cbor::readDouble(offbeat::fitbit::examples::cbor::findField(foodLog, "fat")),
      1);
  offbeat::fitbit::examples::cbor::printLine(
      "Fiber: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(foodLog, "fiber")));
  offbeat::fitbit::examples::cbor::printLine(
      "Protein: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(foodLog, "protein")));
  offbeat::fitbit::examples::cbor::printLine(
      "Sodium: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(foodLog, "sodium")));
  offbeat::fitbit::examples::cbor::printLine(
      "Water: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(foodLog, "water")));
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-food-log-cbor-docs[]

// tag::fitbit-get-food-goal-cbor-docs[]
void sendFitbitGetFoodGoalCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength =
      offbeat::fitbit::examples::cbor::buildStringRequest("fitbit.get.food.goal", "", encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.get.food.goal request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.get.food.goal");
}

void handleFitbitGetFoodGoalCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.food.goal response");
    return;
  }

  cn_cbor* foodGoal = offbeat::fitbit::examples::cbor::findField(root, "fitbit.food.goal");
  if (foodGoal == NULL || foodGoal->type != CN_CBOR_MAP) {
    Serial.println("No fitbit.food.goal payload");
    return;
  }

  offbeat::fitbit::examples::cbor::printLine(
      "Daily calorie goal: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(foodGoal, "calories")));
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-food-goal-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendFitbitCreateFoodLogCbor(webSocket);
      break;
    case WStype_BIN:
      handleFitbitCreateFoodLogCborResponse(payload, length);
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
