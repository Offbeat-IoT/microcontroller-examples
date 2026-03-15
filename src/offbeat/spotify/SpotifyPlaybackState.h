#pragma once

#include <stdint.h>

namespace offbeat::spotify {

inline constexpr char kGetStateCommand[] = "spotify.state";
inline constexpr char kGetStateResponse[] = "spotify.state.response";
inline constexpr char kCurrentlyPlayingCommand[] = "spotify.currently-playing";
inline constexpr char kCurrentlyPlayingResponse[] = "spotify.currently-playing.response";
inline constexpr int kUnknownVolumePercent = -1;

struct SpotifyPlaybackItem {
  const char* name = "unknown";
  const char* artist = "unknown";
  const char* album = "unknown";
};

struct SpotifyPlaybackDevice {
  const char* id = "unknown";
  const char* name = "unknown";
  int volumePercent = kUnknownVolumePercent;
};

struct SpotifyPlaybackState {
  bool isPlaying = false;
  SpotifyPlaybackItem item;
  SpotifyPlaybackDevice device;
  bool shuffling = false;
  bool hasShuffling = false;
};

enum class SpotifyPlaybackStateParseStatus : uint8_t {
  kOk,
  kInvalidPayload,
  kMissingResponse,
};

}  // namespace offbeat::spotify
