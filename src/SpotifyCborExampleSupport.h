#pragma once

#include <Arduino.h>
#include <ArduinoCbor.h>

namespace offbeat::spotify::examples::cbor {

enum class ParseStatus {
  kOk,
  kInvalidPayload,
  kMissingResponse,
};

inline size_t buildRequest(const char* command, const char* value, uint8_t* output, size_t capacity) {
  CborBuffer buffer(512);
  CborObject payload(buffer);
  payload.set(command, value);
  return payload.encode(output, capacity);
}

inline ParseStatus parseResult(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    const char* responseKey,
    cn_cbor*& root,
    cn_cbor*& result) {
  cn_cbor_errback error;
  root = cn_cbor_decode(payload, length, &buffer.context, &error);
  if (root == NULL) {
    return ParseStatus::kInvalidPayload;
  }

  cn_cbor* response = cn_cbor_mapget_string(root, responseKey);
  if (response == NULL || response->type != CN_CBOR_MAP) {
    return ParseStatus::kMissingResponse;
  }

  result = cn_cbor_mapget_string(response, "result");
  return ParseStatus::kOk;
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

inline bool readBool(cn_cbor* value, bool fallback = false) {
  if (value == NULL) {
    return fallback;
  }
  if (value->type == CN_CBOR_TRUE) {
    return true;
  }
  if (value->type == CN_CBOR_FALSE) {
    return false;
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

inline void printLine(const char* label, bool value) {
  Serial.print(label);
  Serial.println(value ? "true" : "false");
}

inline void printEndpoint(cn_cbor* root) {
  cn_cbor* endpointId = cn_cbor_mapget_string(root, "endpointId");
  if (endpointId != NULL) {
    printLine("Endpoint ID: ", readString(endpointId));
  }
}

inline size_t countArray(cn_cbor* array) {
  if (array == NULL || array->type != CN_CBOR_ARRAY) {
    return 0;
  }

  size_t count = 0;
  for (cn_cbor* entry = array->first_child; entry != NULL; entry = entry->next) {
    ++count;
  }
  return count;
}

inline cn_cbor* firstArrayItem(cn_cbor* array) {
  return array != NULL && array->type == CN_CBOR_ARRAY ? array->first_child : NULL;
}

inline void printSummary(cn_cbor* value, int depth = 0);

inline void printArraySummary(cn_cbor* array, int depth = 0) {
  printLine("Item count: ", static_cast<long>(countArray(array)));
  if (depth > 2) {
    return;
  }

  cn_cbor* first = firstArrayItem(array);
  if (first == NULL) {
    return;
  }

  if (first->type == CN_CBOR_TEXT) {
    printLine("First item: ", readString(first));
    return;
  }
  if (first->type == CN_CBOR_TRUE || first->type == CN_CBOR_FALSE) {
    printLine("First status: ", readBool(first));
    return;
  }
  if (first->type == CN_CBOR_INT) {
    printLine("First item: ", readLong(first));
    return;
  }
  printSummary(first, depth + 1);
}

inline void printCommonObjectFields(cn_cbor* object) {
  cn_cbor* displayName = cn_cbor_mapget_string(object, "display_name");
  cn_cbor* name = cn_cbor_mapget_string(object, "name");
  cn_cbor* id = cn_cbor_mapget_string(object, "id");
  cn_cbor* url = cn_cbor_mapget_string(object, "url");
  cn_cbor* description = cn_cbor_mapget_string(object, "description");
  cn_cbor* chapterNumber = cn_cbor_mapget_string(object, "chapter_number");
  cn_cbor* durationMs = cn_cbor_mapget_string(object, "duration_ms");
  cn_cbor* tempo = cn_cbor_mapget_string(object, "tempo");
  cn_cbor* message = cn_cbor_mapget_string(object, "message");
  cn_cbor* status = cn_cbor_mapget_string(object, "status");

  if (displayName != NULL) {
    printLine("Display name: ", readString(displayName));
  }
  if (name != NULL) {
    printLine("Name: ", readString(name));
  }
  if (id != NULL) {
    printLine("ID: ", readString(id));
  }
  if (url != NULL) {
    printLine("URL: ", readString(url));
  }
  if (description != NULL) {
    printLine("Description: ", readString(description));
  }
  if (chapterNumber != NULL) {
    printLine("Chapter number: ", readLong(chapterNumber));
  }
  if (durationMs != NULL) {
    printLine("Duration ms: ", readLong(durationMs));
  }
  if (tempo != NULL) {
    printLine("Tempo: ", readDouble(tempo));
  }
  if (message != NULL) {
    printLine("Message: ", readString(message));
  }
  if (status != NULL) {
    printLine("Status: ", readLong(status));
  }
}

inline void printNestedCollection(cn_cbor* object, const char* key, int depth) {
  cn_cbor* nested = cn_cbor_mapget_string(object, key);
  if (nested == NULL) {
    return;
  }

  Serial.print("Collection: ");
  Serial.println(key);
  printSummary(nested, depth + 1);
}

inline void printSummary(cn_cbor* value, int depth) {
  if (value == NULL || depth > 3) {
    return;
  }

  switch (value->type) {
    case CN_CBOR_TEXT:
      printLine("Result: ", readString(value));
      return;
    case CN_CBOR_TRUE:
    case CN_CBOR_FALSE:
      printLine("Result: ", readBool(value));
      return;
    case CN_CBOR_INT:
      printLine("Result: ", readLong(value));
      return;
    case CN_CBOR_DOUBLE:
    case CN_CBOR_FLOAT:
      printLine("Result: ", readDouble(value));
      return;
    case CN_CBOR_ARRAY:
      printArraySummary(value, depth);
      return;
    case CN_CBOR_MAP:
      break;
    default:
      return;
  }

  printCommonObjectFields(value);

  cn_cbor* error = cn_cbor_mapget_string(value, "error");
  if (error != NULL) {
    Serial.println("Error:");
    printSummary(error, depth + 1);
  }

  cn_cbor* items = cn_cbor_mapget_string(value, "items");
  if (items != NULL) {
    printArraySummary(items, depth);
  }

  cn_cbor* genres = cn_cbor_mapget_string(value, "genres");
  if (genres != NULL) {
    printArraySummary(genres, depth);
  }

  cn_cbor* queue = cn_cbor_mapget_string(value, "queue");
  if (queue != NULL) {
    Serial.println("Queue:");
    printArraySummary(queue, depth);
  }

  cn_cbor* currentlyPlaying = cn_cbor_mapget_string(value, "currently_playing");
  if (currentlyPlaying != NULL) {
    Serial.println("Currently playing:");
    printSummary(currentlyPlaying, depth + 1);
  }

  printNestedCollection(value, "albums", depth);
  printNestedCollection(value, "artists", depth);
  printNestedCollection(value, "tracks", depth);
  printNestedCollection(value, "playlists", depth);
  printNestedCollection(value, "categories", depth);
  printNestedCollection(value, "chapters", depth);
  printNestedCollection(value, "episodes", depth);
  printNestedCollection(value, "shows", depth);
  printNestedCollection(value, "audio_features", depth);
  printNestedCollection(value, "seeds", depth);
}

}  // namespace offbeat::spotify::examples::cbor
