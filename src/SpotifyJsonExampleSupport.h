#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

namespace offbeat::spotify::examples::json {

enum class ParseStatus {
  kOk,
  kInvalidPayload,
  kMissingResponse,
};

inline bool buildRequest(const char* command, const char* value, String& output) {
  StaticJsonDocument<512> payload;
  payload[command] = value;
  output = "";
  return serializeJson(payload, output) > 0;
}

template <size_t Capacity>
inline ParseStatus parseResult(
    const uint8_t* payload,
    size_t length,
    StaticJsonDocument<Capacity>& document,
    const char* responseKey,
    JsonObjectConst& root,
    JsonVariantConst& result) {
  DeserializationError error = deserializeJson(document, payload, length);
  if (error) {
    return ParseStatus::kInvalidPayload;
  }

  root = document.template as<JsonObjectConst>();
  JsonObjectConst response = root[responseKey].as<JsonObjectConst>();
  if (response.isNull()) {
    return ParseStatus::kMissingResponse;
  }

  result = response["result"];
  return ParseStatus::kOk;
}

inline bool isNull(JsonVariantConst value) {
  return value.isNull();
}

inline const char* readString(JsonVariantConst value, const char* fallback = "unknown") {
  return value.is<const char*>() ? value.as<const char*>() : fallback;
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

inline void printLine(const char* label, bool value) {
  Serial.print(label);
  Serial.println(value ? "true" : "false");
}

inline void printEndpoint(JsonObjectConst root) {
  JsonVariantConst endpointId = root["endpointId"];
  if (!endpointId.isNull()) {
    printLine("Endpoint ID: ", readString(endpointId));
  }
}

inline void printCommonObjectFields(JsonObjectConst object) {
  if (!object["display_name"].isNull()) {
    printLine("Display name: ", readString(object["display_name"]));
  }
  if (!object["name"].isNull()) {
    printLine("Name: ", readString(object["name"]));
  }
  if (!object["id"].isNull()) {
    printLine("ID: ", readString(object["id"]));
  }
  if (!object["url"].isNull()) {
    printLine("URL: ", readString(object["url"]));
  }
  if (!object["description"].isNull()) {
    printLine("Description: ", readString(object["description"]));
  }
  if (!object["chapter_number"].isNull()) {
    printLine("Chapter number: ", readLong(object["chapter_number"]));
  }
  if (!object["duration_ms"].isNull()) {
    printLine("Duration ms: ", readLong(object["duration_ms"]));
  }
  if (!object["tempo"].isNull()) {
    printLine("Tempo: ", readDouble(object["tempo"]));
  }
  if (!object["message"].isNull()) {
    printLine("Message: ", readString(object["message"]));
  }
  if (!object["status"].isNull()) {
    printLine("Status: ", readLong(object["status"]));
  }
}

inline void printSummary(JsonVariantConst value, int depth = 0);

inline void printArraySummary(JsonArrayConst array, int depth = 0) {
  printLine("Item count: ", static_cast<long>(array.size()));
  if (array.size() == 0 || depth > 2) {
    return;
  }

  JsonVariantConst first = array[0];
  if (first.is<JsonObjectConst>()) {
    printSummary(first, depth + 1);
    return;
  }
  if (first.is<const char*>()) {
    printLine("First item: ", readString(first));
    return;
  }
  if (first.is<bool>()) {
    printLine("First status: ", readBool(first));
    return;
  }
  if (first.is<long>()) {
    printLine("First item: ", readLong(first));
  }
}

inline void printNestedCollection(JsonObjectConst object, const char* key, int depth) {
  JsonVariantConst nested = object[key];
  if (nested.isNull()) {
    return;
  }
  Serial.print("Collection: ");
  Serial.println(key);
  printSummary(nested, depth + 1);
}

inline void printSummary(JsonVariantConst value, int depth) {
  if (depth > 3 || value.isNull()) {
    return;
  }

  if (value.is<const char*>()) {
    printLine("Result: ", readString(value));
    return;
  }
  if (value.is<bool>()) {
    printLine("Result: ", readBool(value));
    return;
  }
  if (value.is<long>()) {
    printLine("Result: ", readLong(value));
    return;
  }
  if (value.is<double>()) {
    printLine("Result: ", readDouble(value));
    return;
  }
  if (value.is<JsonArrayConst>()) {
    printArraySummary(value.as<JsonArrayConst>(), depth);
    return;
  }
  if (!value.is<JsonObjectConst>()) {
    return;
  }

  JsonObjectConst object = value.as<JsonObjectConst>();
  printCommonObjectFields(object);

  if (!object["error"].isNull()) {
    Serial.println("Error:");
    printSummary(object["error"], depth + 1);
  }

  if (!object["items"].isNull()) {
    printArraySummary(object["items"].as<JsonArrayConst>(), depth);
  }

  if (!object["genres"].isNull()) {
    printArraySummary(object["genres"].as<JsonArrayConst>(), depth);
  }

  if (!object["queue"].isNull()) {
    Serial.println("Queue:");
    printArraySummary(object["queue"].as<JsonArrayConst>(), depth);
  }

  if (!object["currently_playing"].isNull()) {
    Serial.println("Currently playing:");
    printSummary(object["currently_playing"], depth + 1);
  }

  printNestedCollection(object, "albums", depth);
  printNestedCollection(object, "artists", depth);
  printNestedCollection(object, "tracks", depth);
  printNestedCollection(object, "playlists", depth);
  printNestedCollection(object, "categories", depth);
  printNestedCollection(object, "chapters", depth);
  printNestedCollection(object, "episodes", depth);
  printNestedCollection(object, "shows", depth);
  printNestedCollection(object, "audio_features", depth);
  printNestedCollection(object, "seeds", depth);
}

}  // namespace offbeat::spotify::examples::json
