#pragma once

#include <Arduino.h>
#include <ArduinoCbor.h>

namespace offbeat::fitbit::examples::cbor {

enum class ParseStatus {
  kOk,
  kInvalidPayload,
};

inline size_t buildStringRequest(
    const char* command,
    const char* value,
    uint8_t* output,
    size_t capacity) {
  CborBuffer buffer(512);
  CborObject payload(buffer);
  payload.set(command, value);
  return payload.encode(output, capacity);
}

template <typename ObjectBuilder>
inline size_t buildObjectRequest(
    const char* command,
    uint8_t* output,
    size_t capacity,
    ObjectBuilder&& buildObject) {
  CborBuffer buffer(512);
  CborObject payload(buffer);
  CborObject value(buffer);
  buildObject(value);
  payload.set(command, value);
  return payload.encode(output, capacity);
}

inline ParseStatus parseRoot(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    cn_cbor*& root) {
  cn_cbor_errback error;
  root = cn_cbor_decode(payload, length, &buffer.context, &error);
  if (root == NULL || root->type != CN_CBOR_MAP) {
    return ParseStatus::kInvalidPayload;
  }

  return ParseStatus::kOk;
}

inline cn_cbor* findField(cn_cbor* object, const char* key) {
  return object == NULL || object->type != CN_CBOR_MAP ? NULL : cn_cbor_mapget_string(object, key);
}

inline const char* readString(cn_cbor* value, const char* fallback = "unknown") {
  return value != NULL && value->type == CN_CBOR_TEXT && value->v.str != NULL ? value->v.str : fallback;
}

inline long readLong(cn_cbor* value, long fallback = -1) {
  return value != NULL && value->type == CN_CBOR_INT ? static_cast<long>(value->v.sint) : fallback;
}

inline double readDouble(cn_cbor* value, double fallback = -1.0) {
  if (value == NULL) {
    return fallback;
  }
  if (value->type == CN_CBOR_DOUBLE) {
    return value->v.dbl;
  }
  if (value->type == CN_CBOR_FLOAT) {
    return value->v.f;
  }
  if (value->type == CN_CBOR_INT) {
    return static_cast<double>(value->v.sint);
  }
  return fallback;
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

inline void printEndpoint(cn_cbor* root) {
  cn_cbor* endpointId = findField(root, "endpointId");
  if (endpointId != NULL) {
    printLine("Endpoint ID: ", readString(endpointId));
  }
}

}  // namespace offbeat::fitbit::examples::cbor
