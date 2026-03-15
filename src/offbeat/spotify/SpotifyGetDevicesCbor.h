#pragma once

#include <Arduino.h>
#include <ArduinoCbor.h>

#include <offbeat/spotify/SpotifyGetDevices.h>

namespace offbeat::spotify {

inline size_t buildGetDevicesCborRequest(uint8_t* output, size_t capacity) {
  CborBuffer buffer(64);
  CborObject payload(buffer);
  payload.set(kGetDevicesCommand, "");
  return payload.encode(output, capacity);
}

template <typename DeviceHandler>
inline SpotifyGetDevicesParseStatus visitGetDevicesCborResponse(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    DeviceHandler&& handleDevice) {
  cn_cbor_errback error;
  cn_cbor* root = cn_cbor_decode(payload, length, &buffer.context, &error);
  if (root == NULL) {
    return SpotifyGetDevicesParseStatus::kInvalidPayload;
  }

  cn_cbor* devicesNode = cn_cbor_mapget_string(root, kGetDevicesResponse);
  if (devicesNode == NULL || devicesNode->type != CN_CBOR_MAP) {
    return SpotifyGetDevicesParseStatus::kMissingResponse;
  }

  for (cn_cbor* entry = devicesNode->first_child;
       entry != NULL && entry->next != NULL;
       entry = entry->next->next) {
    const char* deviceId = entry->v.str != NULL ? entry->v.str : "unknown";
    CborObject device(buffer, entry->next);
    CborVariant nameVariant = device.get("name");
    CborVariant volumeVariant = device.get("volume");

    handleDevice(SpotifyDevice{
        deviceId,
        nameVariant.isString() ? nameVariant.asString() : "unknown",
        volumeVariant.isInteger() ? static_cast<int>(volumeVariant.asInteger()) : kUnknownVolume,
    });
  }

  return SpotifyGetDevicesParseStatus::kOk;
}

}  // namespace offbeat::spotify
