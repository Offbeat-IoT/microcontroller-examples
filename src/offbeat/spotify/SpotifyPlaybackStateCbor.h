#pragma once

#include <ArduinoCbor.h>

#include <offbeat/spotify/SpotifyPlaybackState.h>

namespace offbeat::spotify {

inline size_t buildPlaybackStateCborRequest(const char* command, uint8_t* output, size_t capacity) {
  CborBuffer buffer(64);
  CborObject payload(buffer);
  payload.set(command, "");
  return payload.encode(output, capacity);
}

inline size_t buildGetStateCborRequest(uint8_t* output, size_t capacity) {
  return buildPlaybackStateCborRequest(kGetStateCommand, output, capacity);
}

inline size_t buildCurrentlyPlayingCborRequest(uint8_t* output, size_t capacity) {
  return buildPlaybackStateCborRequest(kCurrentlyPlayingCommand, output, capacity);
}

inline SpotifyPlaybackStateParseStatus parsePlaybackStateCborResponse(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    const char* responseKey,
    SpotifyPlaybackState& playbackState) {
  CborVariant rootVariant = buffer.decode(const_cast<uint8_t*>(payload), length);
  if (!rootVariant.isObject()) {
    return SpotifyPlaybackStateParseStatus::kInvalidPayload;
  }

  CborObject root = rootVariant.asObject();
  CborVariant responseVariant = root.get(responseKey);
  if (!responseVariant.isObject()) {
    return SpotifyPlaybackStateParseStatus::kMissingResponse;
  }

  CborObject response = responseVariant.asObject();
  CborVariant itemVariant = response.get("item");
  CborVariant deviceVariant = response.get("device");
  CborObject item = itemVariant.isObject() ? itemVariant.asObject() : CborObject(buffer);
  CborObject device = deviceVariant.isObject() ? deviceVariant.asObject() : CborObject(buffer);
  CborVariant shufflingVariant = response.get("shuffling");

  playbackState.isPlaying = response.get("isPlaying").isBool() ? response.get("isPlaying").asBool() : false;
  playbackState.item = SpotifyPlaybackItem{
      item.get("name").isString() ? item.get("name").asString() : "unknown",
      item.get("artist").isString() ? item.get("artist").asString() : "unknown",
      item.get("album").isString() ? item.get("album").asString() : "unknown",
  };
  playbackState.device = SpotifyPlaybackDevice{
      device.get("id").isString() ? device.get("id").asString() : "unknown",
      device.get("name").isString() ? device.get("name").asString() : "unknown",
      device.get("volumepercent").isInteger() ? static_cast<int>(device.get("volumepercent").asInteger()) : kUnknownVolumePercent,
  };
  playbackState.hasShuffling = shufflingVariant.isBool();
  playbackState.shuffling = shufflingVariant.isBool() ? shufflingVariant.asBool() : false;
  return SpotifyPlaybackStateParseStatus::kOk;
}

inline SpotifyPlaybackStateParseStatus parseGetStateCborResponse(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    SpotifyPlaybackState& playbackState) {
  return parsePlaybackStateCborResponse(payload, length, buffer, kGetStateResponse, playbackState);
}

inline SpotifyPlaybackStateParseStatus parseCurrentlyPlayingCborResponse(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    SpotifyPlaybackState& playbackState) {
  return parsePlaybackStateCborResponse(payload, length, buffer, kCurrentlyPlayingResponse, playbackState);
}

}  // namespace offbeat::spotify
