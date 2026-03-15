#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

#include <offbeat/spotify/SpotifyGetDevices.h>

namespace offbeat::spotify {

inline bool buildGetDevicesJsonRequest(String& output) {
  StaticJsonDocument<64> payload;
  payload[kGetDevicesCommand] = "";

  output = "";
  return serializeJson(payload, output) > 0;
}

template <typename JsonDocumentType, typename DeviceHandler>
inline SpotifyGetDevicesParseStatus visitGetDevicesJsonResponse(
    const uint8_t* payload,
    size_t length,
    JsonDocumentType& document,
    DeviceHandler&& handleDevice) {
  DeserializationError error = deserializeJson(document, payload, length);
  if (error) {
    return SpotifyGetDevicesParseStatus::kInvalidPayload;
  }

  JsonObjectConst devices = document[kGetDevicesResponse].template as<JsonObjectConst>();
  if (devices.isNull()) {
    return SpotifyGetDevicesParseStatus::kMissingResponse;
  }

  for (JsonPairConst deviceEntry : devices) {
    JsonObjectConst deviceObject = deviceEntry.value().template as<JsonObjectConst>();
    const char* name = deviceObject["name"] | "unknown";
    int volume = deviceObject["volume"] | kUnknownVolume;
    handleDevice(SpotifyDevice{
        deviceEntry.key().c_str(),
        name,
        volume,
    });
  }

  return SpotifyGetDevicesParseStatus::kOk;
}

}  // namespace offbeat::spotify
