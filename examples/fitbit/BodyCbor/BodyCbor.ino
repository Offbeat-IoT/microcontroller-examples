#include <ArduinoCbor.h>
#include <FitbitCborExampleSupport.h>
#include <FitbitExampleSupport.h>
#include <WebSocketsClient.h>

#include "offbeat_test_config.h"

WebSocketsClient webSocket;

// tag::fitbit-get-body-cbor-docs[]
void sendFitbitGetBodyCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength =
      offbeat::fitbit::examples::cbor::buildStringRequest("fitbit.get.body", "", encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.get.body request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.get.body");
}

void handleFitbitGetBodyCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.body response");
    return;
  }

  offbeat::fitbit::examples::cbor::printLine(
      "Body fat: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(root, "fat")));
  offbeat::fitbit::examples::cbor::printLine(
      "Weight: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(root, "weight")));
  offbeat::fitbit::examples::cbor::printLine(
      "BMI: ",
      offbeat::fitbit::examples::cbor::readDouble(offbeat::fitbit::examples::cbor::findField(root, "bmi")),
      2);
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-body-cbor-docs[]

// tag::fitbit-get-weight-cbor-docs[]
constexpr char kGetWeightCborValue[] = "14-07-2024";

void sendFitbitGetWeightCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength = offbeat::fitbit::examples::cbor::buildStringRequest(
      "fitbit.get.weight", kGetWeightCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.get.weight request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.get.weight");
}

void handleFitbitGetWeightCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.weight response");
    return;
  }

  Serial.print("Requested date: ");
  Serial.println(kGetWeightCborValue);
  offbeat::fitbit::examples::cbor::printLine(
      "Weight: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(root, "weight")));
  offbeat::fitbit::examples::cbor::printLine(
      "BMI: ",
      offbeat::fitbit::examples::cbor::readDouble(offbeat::fitbit::examples::cbor::findField(root, "bmi")),
      2);
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-weight-cbor-docs[]

// tag::fitbit-get-current-weight-cbor-docs[]
void sendFitbitGetCurrentWeightCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength = offbeat::fitbit::examples::cbor::buildStringRequest(
      "fitbit.get.current.weight", "", encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.get.current.weight request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.get.current.weight");
}

void handleFitbitGetCurrentWeightCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.current.weight response");
    return;
  }

  offbeat::fitbit::examples::cbor::printLine(
      "Current weight: ",
      offbeat::fitbit::examples::cbor::readLong(offbeat::fitbit::examples::cbor::findField(root, "weight")));
  offbeat::fitbit::examples::cbor::printLine(
      "Weight unit: ",
      offbeat::fitbit::examples::cbor::readString(offbeat::fitbit::examples::cbor::findField(root, "weightUnit")));
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-current-weight-cbor-docs[]

// tag::fitbit-get-weight-goal-cbor-docs[]
void sendFitbitGetWeightGoalCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength = offbeat::fitbit::examples::cbor::buildStringRequest(
      "fitbit.get.weight.goal", "", encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.get.weight.goal request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.get.weight.goal");
}

void handleFitbitGetWeightGoalCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.get.weight.goal response");
    return;
  }

  cn_cbor* weightGoal = offbeat::fitbit::examples::cbor::findField(root, "weightGoal");
  if (weightGoal == NULL || weightGoal->type != CN_CBOR_MAP) {
    Serial.println("No weightGoal payload");
    return;
  }

  offbeat::fitbit::examples::cbor::printLine(
      "Goal type: ",
      offbeat::fitbit::examples::cbor::readString(offbeat::fitbit::examples::cbor::findField(weightGoal, "goalType")));
  offbeat::fitbit::examples::cbor::printLine(
      "Start date: ",
      offbeat::fitbit::examples::cbor::readString(offbeat::fitbit::examples::cbor::findField(weightGoal, "startDate")));
  offbeat::fitbit::examples::cbor::printLine(
      "Start weight: ",
      offbeat::fitbit::examples::cbor::readDouble(offbeat::fitbit::examples::cbor::findField(weightGoal, "startWeight")),
      2);
  offbeat::fitbit::examples::cbor::printLine(
      "Target weight: ",
      offbeat::fitbit::examples::cbor::readDouble(offbeat::fitbit::examples::cbor::findField(weightGoal, "weight")),
      2);
  offbeat::fitbit::examples::cbor::printLine(
      "Weight threshold: ",
      offbeat::fitbit::examples::cbor::readDouble(offbeat::fitbit::examples::cbor::findField(weightGoal, "weightThreshold")),
      2);
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-get-weight-goal-cbor-docs[]

// tag::fitbit-create-weight-cbor-docs[]
constexpr char kCreateWeightCborValue[] = "100";

void sendFitbitCreateWeightCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength = offbeat::fitbit::examples::cbor::buildStringRequest(
      "fitbit.create.weight", kCreateWeightCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.create.weight request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.create.weight");
}

void handleFitbitCreateWeightCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.create.weight response");
    return;
  }

  cn_cbor* response = offbeat::fitbit::examples::cbor::findField(root, "fitbit.create.weight");
  if (response == NULL || response->type != CN_CBOR_MAP) {
    Serial.println("No fitbit.create.weight payload");
    return;
  }

  Serial.print("Requested weight: ");
  Serial.println(kCreateWeightCborValue);
  offbeat::fitbit::examples::cbor::printLine(
      "Result: ",
      offbeat::fitbit::examples::cbor::readString(offbeat::fitbit::examples::cbor::findField(response, "result")));
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-create-weight-cbor-docs[]

// tag::fitbit-create-fat-cbor-docs[]
constexpr char kCreateFatCborValue[] = "21";

void sendFitbitCreateFatCbor(WebSocketsClient& socket) {
  uint8_t encoded[128];
  size_t encodedLength = offbeat::fitbit::examples::cbor::buildStringRequest(
      "fitbit.create.fat", kCreateFatCborValue, encoded, sizeof(encoded));
  if (encodedLength == 0) {
    Serial.println("Unable to build fitbit.create.fat request");
    return;
  }

  socket.sendBIN(encoded, encodedLength);
  Serial.println("REQUEST_SENT=fitbit.create.fat");
}

void handleFitbitCreateFatCborResponse(uint8_t* payload, size_t length) {
  CborBuffer buffer(1024);
  cn_cbor* root = NULL;
  offbeat::fitbit::examples::cbor::ParseStatus status =
      offbeat::fitbit::examples::cbor::parseRoot(payload, length, buffer, root);

  if (status == offbeat::fitbit::examples::cbor::ParseStatus::kInvalidPayload) {
    Serial.println("Unable to parse fitbit.create.fat response");
    return;
  }

  cn_cbor* response = offbeat::fitbit::examples::cbor::findField(root, "fitbit.create.fat");
  if (response == NULL || response->type != CN_CBOR_MAP) {
    Serial.println("No fitbit.create.fat payload");
    return;
  }

  Serial.print("Requested fat value: ");
  Serial.println(kCreateFatCborValue);
  offbeat::fitbit::examples::cbor::printLine(
      "Result: ",
      offbeat::fitbit::examples::cbor::readString(offbeat::fitbit::examples::cbor::findField(response, "result")));
  offbeat::fitbit::examples::cbor::printEndpoint(root);
  Serial.println("TEST:PASS");
}
// end::fitbit-create-fat-cbor-docs[]

void websocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WS_CONNECTED");
      sendFitbitGetBodyCbor(webSocket);
      break;
    case WStype_BIN:
      handleFitbitGetBodyCborResponse(payload, length);
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
