#include <ArduinoCbor.h>
#include <FitbitCborExampleSupport.h>
#include <FitbitExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::fitbit-get-water-cbor-docs[]
void sendFitbitGetWaterCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength =
      offbeat::fitbit::examples::cbor::buildStringRequest("fitbit.get.water", "", encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.get.water request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.get.water");
}

void handleFitbitGetWaterCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.water response");
    return;
  }

  cn_cbor* water = offbeat::fitbit::examples::cbor::findField(root, "fitbit.get.water");
  if (water == NULL || water->type != CN_CBOR_MAP) {
    Serial.println("No fitbit.get.water payload");
    return;
  }

  offbeat::fitbit::examples::cbor::printLine(
      "Water intake: ",
      offbeat::fitbit::examples::cbor::readDouble(offbeat::fitbit::examples::cbor::findField(water, "water")),
      1);
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-water-cbor-docs[]

// tag::fitbit-create-water-log-cbor-docs[]
constexpr char kCreateWaterAmountCbor[] = "124";
constexpr char kCreateWaterUnitCbor[] = "ml";

void sendFitbitCreateWaterLogCbor(WebSocketsClient& socket) {
  uint8_t encoded[192];
  size_t encodedLength = offbeat::fitbit::examples::cbor::buildObjectRequest(
      "fitbit.create.water.log",
      encoded,
      sizeof(encoded),
      [](CborObject& value) {
        value.set("amount", kCreateWaterAmountCbor);
        value.set("unit", kCreateWaterUnitCbor);
      });
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.create.water.log request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.create.water.log");
}

void handleFitbitCreateWaterLogCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.create.water.log response");
    return;
  }

  cn_cbor* response = offbeat::fitbit::examples::cbor::findField(root, "fitbit.create.water.log");
  if (response == NULL || response->type != CN_CBOR_MAP) {
    Serial.println("No fitbit.create.water.log payload");
    return;
  }

  offbeat::fitbit::examples::cbor::printLine("Amount: ", kCreateWaterAmountCbor);
  offbeat::fitbit::examples::cbor::printLine("Unit: ", kCreateWaterUnitCbor);
  offbeat::fitbit::examples::cbor::printLine(
      "Result: ",
      offbeat::fitbit::examples::cbor::readString(offbeat::fitbit::examples::cbor::findField(response, "result")));
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-create-water-log-cbor-docs[]

// tag::fitbit-get-water-goal-cbor-docs[]
void sendFitbitGetWaterGoalCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength =
      offbeat::fitbit::examples::cbor::buildStringRequest("fitbit.get.water.goal", "", encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.get.water.goal request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.get.water.goal");
}

void handleFitbitGetWaterGoalCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.water.goal response");
    return;
  }

  cn_cbor* waterGoal = offbeat::fitbit::examples::cbor::findField(root, "fitbit.get.water.goal");
  if (waterGoal == NULL || waterGoal->type != CN_CBOR_MAP) {
    Serial.println("No fitbit.get.water.goal payload");
    return;
  }

  offbeat::fitbit::examples::cbor::printLine(
      "Goal: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(waterGoal, "goal")));
  offbeat::fitbit::examples::cbor::printLine(
      "Start date: ",
      offbeat::fitbit::examples::cbor::readString(offbeat::fitbit::examples::cbor::findField(waterGoal, "startDate")));
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-water-goal-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendFitbitGetWaterCbor(webSocket);
      break;
    case WStype_BIN:
      handleFitbitGetWaterCborResponse(payload, length);
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
