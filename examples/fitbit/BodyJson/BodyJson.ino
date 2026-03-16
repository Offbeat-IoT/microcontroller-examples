#include <FitbitExampleSupport.h>
#include <FitbitJsonExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::fitbit-get-body-json-docs[]
void sendFitbitGetBodyJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.get.body", "", body)) {
    Serial.println("Unable to build fitbit.get.body request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.get.body");
}

void handleFitbitGetBodyJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.body response");
    return;
  }

  offbeat::fitbit::examples::json::printLine(
      "Body fat: ",
      offbeat::fitbit::examples::json::readLong(root["fat"]));
  offbeat::fitbit::examples::json::printLine(
      "Weight: ",
      offbeat::fitbit::examples::json::readLong(root["weight"]));
  offbeat::fitbit::examples::json::printLine(
      "BMI: ",
      offbeat::fitbit::examples::json::readDouble(root["bmi"]),
      2);
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-body-json-docs[]

// tag::fitbit-get-weight-json-docs[]
constexpr char kGetWeightJsonValue[] = "14-07-2024";

void sendFitbitGetWeightJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.get.weight", kGetWeightJsonValue, body)) {
    Serial.println("Unable to build fitbit.get.weight request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.get.weight");
}

void handleFitbitGetWeightJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.weight response");
    return;
  }

  Serial.print("Requested date: ");
  Serial.println(kGetWeightJsonValue);
  offbeat::fitbit::examples::json::printLine(
      "Weight: ",
      offbeat::fitbit::examples::json::readLong(root["weight"]));
  offbeat::fitbit::examples::json::printLine(
      "BMI: ",
      offbeat::fitbit::examples::json::readDouble(root["bmi"]),
      2);
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-weight-json-docs[]

// tag::fitbit-get-current-weight-json-docs[]
void sendFitbitGetCurrentWeightJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.get.current.weight", "", body)) {
    Serial.println("Unable to build fitbit.get.current.weight request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.get.current.weight");
}

void handleFitbitGetCurrentWeightJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.current.weight response");
    return;
  }

  offbeat::fitbit::examples::json::printLine(
      "Current weight: ",
      offbeat::fitbit::examples::json::readLong(root["weight"]));
  offbeat::fitbit::examples::json::printLine(
      "Weight unit: ",
      offbeat::fitbit::examples::json::readString(root["weightUnit"]));
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-current-weight-json-docs[]

// tag::fitbit-get-weight-goal-json-docs[]
void sendFitbitGetWeightGoalJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.get.weight.goal", "", body)) {
    Serial.println("Unable to build fitbit.get.weight.goal request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.get.weight.goal");
}

void handleFitbitGetWeightGoalJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.weight.goal response");
    return;
  }

  JsonObjectConst weightGoal = root["weightGoal"].as<JsonObjectConst>();
  if (weightGoal.isNull()) {
    Serial.println("No weightGoal payload");
    return;
  }

  offbeat::fitbit::examples::json::printLine(
      "Goal type: ",
      offbeat::fitbit::examples::json::readString(weightGoal["goalType"]));
  offbeat::fitbit::examples::json::printLine(
      "Start date: ",
      offbeat::fitbit::examples::json::readString(weightGoal["startDate"]));
  offbeat::fitbit::examples::json::printLine(
      "Start weight: ",
      offbeat::fitbit::examples::json::readDouble(weightGoal["startWeight"]),
      2);
  offbeat::fitbit::examples::json::printLine(
      "Target weight: ",
      offbeat::fitbit::examples::json::readDouble(weightGoal["weight"]),
      2);
  offbeat::fitbit::examples::json::printLine(
      "Weight threshold: ",
      offbeat::fitbit::examples::json::readDouble(weightGoal["weightThreshold"]),
      2);
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-weight-goal-json-docs[]

// tag::fitbit-create-weight-json-docs[]
constexpr char kCreateWeightJsonValue[] = "100";

void sendFitbitCreateWeightJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.create.weight", kCreateWeightJsonValue, body)) {
    Serial.println("Unable to build fitbit.create.weight request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.create.weight");
}

void handleFitbitCreateWeightJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.create.weight response");
    return;
  }

  JsonObjectConst response = root["fitbit.create.weight"].as<JsonObjectConst>();
  if (response.isNull()) {
    Serial.println("No fitbit.create.weight payload");
    return;
  }

  Serial.print("Requested weight: ");
  Serial.println(kCreateWeightJsonValue);
  offbeat::fitbit::examples::json::printLine(
      "Result: ",
      offbeat::fitbit::examples::json::readString(response["result"]));
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-create-weight-json-docs[]

// tag::fitbit-create-fat-json-docs[]
constexpr char kCreateFatJsonValue[] = "21";

void sendFitbitCreateFatJson(WebSocketsClient& socket) {
  String body;
  if (!offbeat::fitbit::examples::json::buildStringRequest("fitbit.create.fat", kCreateFatJsonValue, body)) {
    Serial.println("Unable to build fitbit.create.fat request");
    return;
  }

  socket.sendTXT(body);
  Serial.println("REQUEST_SENT=fitbit.create.fat");
}

void handleFitbitCreateFatJsonResponse(uint8_t* payload, size_t length) {
  StaticJsonDocument<1024> document;
  JsonObjectConst root;
  offbeat::fitbit::examples::json::ParseStatus status =
      offbeat::fitbit::examples::json::parseRoot(payload, length, document, root);

  if (status == offbeat::fitbit::examples::json::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.create.fat response");
    return;
  }

  JsonObjectConst response = root["fitbit.create.fat"].as<JsonObjectConst>();
  if (response.isNull()) {
    Serial.println("No fitbit.create.fat payload");
    return;
  }

  Serial.print("Requested fat value: ");
  Serial.println(kCreateFatJsonValue);
  offbeat::fitbit::examples::json::printLine(
      "Result: ",
      offbeat::fitbit::examples::json::readString(response["result"]));
  offbeat::fitbit::examples::json::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-create-fat-json-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendFitbitGetBodyJson(webSocket);
      break;
    case WStype_TEXT:
      handleFitbitGetBodyJsonResponse(payload, length);
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
