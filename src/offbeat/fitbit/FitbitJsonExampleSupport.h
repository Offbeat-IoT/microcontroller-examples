#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

namespace offbeat::fitbit::examples::json {

enum class ParseStatus {
  kOk,
  kInvalidPayload,
};

inline bool buildStringRequest(const char* command, const char* value, String& output) {
  StaticJsonDocument<512> payload;
  payload[command] = value;
  output = "";
  return serializeJson(payload, output) > 0;
}

template <typename ObjectBuilder>
inline bool buildObjectRequest(const char* command, String& output, ObjectBuilder&& buildObject) {
  StaticJsonDocument<512> payload;
  JsonObject value = payload.createNestedObject(command);
  buildObject(value);
  output = "";
  return serializeJson(payload, output) > 0;
}

template <size_t Capacity>
inline ParseStatus parseRoot(
    const uint8_t* payload,
    size_t length,
    StaticJsonDocument<Capacity>& document,
    JsonObjectConst& root) {
  DeserializationError error = deserializeJson(document, payload, length);
  if (error) {
    return ParseStatus::kInvalidPayload;
  }

  root = document.template as<JsonObjectConst>();
  return root.isNull() ? ParseStatus::kInvalidPayload : ParseStatus::kOk;
}

inline const char* readString(JsonVariantConst value, const char* fallback = "unknown") {
  return value.isNull() ? fallback : value.as<const char*>();
}

inline long readLong(JsonVariantConst value, long fallback = -1) {
  return value.isNull() ? fallback : value.as<long>();
}

inline double readDouble(JsonVariantConst value, double fallback = -1.0) {
  return value.isNull() ? fallback : value.as<double>();
}

inline void printLine(const char* label, const char* value) {
  Serial.print(label);
  Serial.println(value);
}

inline void printLine(const char* label, long value) {
  Serial.print(label);
  Serial.println(value);
}

inline void printLine(const char* label, double value, int digits = 1) {
  Serial.print(label);
  Serial.println(value, digits);
}

inline void printEndpoint(JsonObjectConst root) {
  JsonVariantConst endpointId = root["endpointId"];
  if (!endpointId.isNull()) {
    printLine("Endpoint ID: ", readString(endpointId));
  }
}

}  // namespace offbeat::fitbit::examples::json
