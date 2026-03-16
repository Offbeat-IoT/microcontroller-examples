#pragma once

#include <Arduino.h>

namespace offbeat::spotify {

inline constexpr const char* kPlayCommand = "spotify.play";
inline constexpr const char* kPauseCommand = "spotify.pause";
inline constexpr const char* kNextCommand = "spotify.next";
inline constexpr const char* kPreviousCommand = "spotify.previous";
inline constexpr const char* kVolumeCommand = "spotify.volume";
inline constexpr const char* kShuffleCommand = "spotify.shuffle";
inline constexpr const char* kRepeatCommand = "spotify.repeat";

inline constexpr const char* kPlayResponse = "spotify.play.response";
inline constexpr const char* kPauseResponse = "spotify.pause.response";
inline constexpr const char* kNextResponse = "spotify.next.response";
inline constexpr const char* kPreviousResponse = "spotify.previous.response";
inline constexpr const char* kVolumeResponse = "spotify.volume.response";
inline constexpr const char* kShuffleResponse = "spotify.shuffle.response";
inline constexpr const char* kRepeatResponse = "spotify.repeat.response";

inline constexpr const char* kUnknownEndpointId = "unknown";
inline constexpr const char* kUnknownResult = "UNKNOWN";

enum class SpotifyPlaybackCommandParseStatus {
  kOk,
  kInvalidPayload,
  kMissingResponse,
  kMissingResult,
};

struct SpotifyPlaybackCommandResult {
  const char* endpointId = kUnknownEndpointId;
  const char* result = kUnknownResult;
};

}  // namespace offbeat::spotify
