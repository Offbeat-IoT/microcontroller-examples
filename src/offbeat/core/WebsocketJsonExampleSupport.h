#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

namespace offbeat::core::examples {

enum class ParseStatus {
  kOk,
  kInvalidPayload,
};

inline bool connectWifi(const char* ssid, const char* password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("WIFI_CONNECTING");

  unsigned long nextStatusLogAt = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    unsigned long now = millis();
    if (now >= nextStatusLogAt) {
      Serial.print("WIFI_STATUS=");
      Serial.println(static_cast<int>(WiFi.status()));
      nextStatusLogAt = now + 5000;
    }
  }

  Serial.println("WIFI_CONNECTED");
  return true;
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

  root = document.as<JsonObjectConst>();
  if (root.isNull()) {
    return ParseStatus::kInvalidPayload;
  }

  return ParseStatus::kOk;
}

inline const char* readEndpointId(JsonObjectConst root) {
  return root["endpointId"] | "unknown";
}

inline long readLong(JsonVariantConst value, long fallback = -1) {
  return value.is<long>() ? value.as<long>() : fallback;
}

inline double readDouble(JsonVariantConst value, double fallback = -1.0) {
  return value.is<double>() ? value.as<double>() : fallback;
}

inline bool readBool(JsonVariantConst value, bool fallback = false) {
  return value.is<bool>() ? value.as<bool>() : fallback;
}

inline const char* readString(JsonVariantConst value, const char* fallback = "unknown") {
  return value.is<const char*>() ? value.as<const char*>() : fallback;
}

inline void printLine(const char* label, const char* value) {
  Serial.print(label);
  Serial.println(value);
}

inline void printLine(const char* label, long value) {
  Serial.print(label);
  Serial.println(value);
}

inline void printLine(const char* label, double value, int digits = 2) {
  Serial.print(label);
  Serial.println(value, digits);
}

inline void printLine(const char* label, bool value) {
  Serial.print(label);
  Serial.println(value ? "true" : "false");
}

inline void printEndpoint(JsonObjectConst root) {
  const char* endpointId = readEndpointId(root);
  printLine("Endpoint ID: ", endpointId);
  printLine("ENDPOINT_ID=", endpointId);
}

}  // namespace offbeat::core::examples
