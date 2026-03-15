#pragma once

#include <stdint.h>

namespace offbeat::spotify {

inline constexpr char kGetDevicesCommand[] = "spotify.devices";
inline constexpr char kGetDevicesResponse[] = "spotify.devices.response";
inline constexpr int kUnknownVolume = -1;

struct SpotifyDevice {
  const char* id;
  const char* name;
  int volume;
};

enum class SpotifyGetDevicesParseStatus : uint8_t {
  kOk,
  kInvalidPayload,
  kMissingResponse,
};

}  // namespace offbeat::spotify
