#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

#include <offbeat/spotify/SpotifyPlaybackState.h>

namespace offbeat::spotify {

inline bool buildPlaybackStateJsonRequest(const char* command, String& output) {
  StaticJsonDocument<64> payload;
  payload[command] = "";

  output = "";
  return serializeJson(payload, output) > 0;
}

inline bool buildGetStateJsonRequest(String& output) {
  return buildPlaybackStateJsonRequest(kGetStateCommand, output);
}

inline bool buildCurrentlyPlayingJsonRequest(String& output) {
  return buildPlaybackStateJsonRequest(kCurrentlyPlayingCommand, output);
}

template <typename JsonDocumentType>
inline SpotifyPlaybackStateParseStatus parsePlaybackStateJsonResponse(
    const uint8_t* payload,
    size_t length,
    JsonDocumentType& document,
    const char* responseKey,
    SpotifyPlaybackState& playbackState) {
  DeserializationError error = deserializeJson(document, payload, length);
  if (error) {
    return SpotifyPlaybackStateParseStatus::kInvalidPayload;
  }

  JsonObjectConst response = document[responseKey].template as<JsonObjectConst>();
  if (response.isNull()) {
    return SpotifyPlaybackStateParseStatus::kMissingResponse;
  }

  JsonObjectConst item = response["item"].template as<JsonObjectConst>();
  JsonObjectConst device = response["device"].template as<JsonObjectConst>();
  JsonVariantConst shufflingVariant = response["shuffling"];

  playbackState.isPlaying = response["isPlaying"] | false;
  playbackState.item = SpotifyPlaybackItem{
      item["name"] | "unknown",
      item["artist"] | "unknown",
      item["album"] | "unknown",
  };
  playbackState.device = SpotifyPlaybackDevice{
      device["id"] | "unknown",
      device["name"] | "unknown",
      device["volumepercent"] | kUnknownVolumePercent,
  };
  playbackState.hasShuffling = !shufflingVariant.isNull();
  playbackState.shuffling = shufflingVariant | false;
  return SpotifyPlaybackStateParseStatus::kOk;
}

template <typename JsonDocumentType>
inline SpotifyPlaybackStateParseStatus parseGetStateJsonResponse(
    const uint8_t* payload,
    size_t length,
    JsonDocumentType& document,
    SpotifyPlaybackState& playbackState) {
  return parsePlaybackStateJsonResponse(payload, length, document, kGetStateResponse, playbackState);
}

template <typename JsonDocumentType>
inline SpotifyPlaybackStateParseStatus parseCurrentlyPlayingJsonResponse(
    const uint8_t* payload,
    size_t length,
    JsonDocumentType& document,
    SpotifyPlaybackState& playbackState) {
  return parsePlaybackStateJsonResponse(payload, length, document, kCurrentlyPlayingResponse, playbackState);
}

}  // namespace offbeat::spotify
