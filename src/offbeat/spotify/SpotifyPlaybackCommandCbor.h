#pragma once

#include <ArduinoCbor.h>

#include <offbeat/spotify/SpotifyPlaybackCommand.h>

namespace offbeat::spotify {

inline size_t buildPlaybackCommandCborRequest(
    const char* command,
    const char* value,
    uint8_t* output,
    size_t capacity) {
  CborBuffer buffer(96);
  CborObject payload(buffer);
  payload.set(command, value);
  return payload.encode(output, capacity);
}

inline size_t buildPlayCborRequest(uint8_t* output, size_t capacity) {
  return buildPlaybackCommandCborRequest(kPlayCommand, "", output, capacity);
}

inline size_t buildPauseCborRequest(uint8_t* output, size_t capacity) {
  return buildPlaybackCommandCborRequest(kPauseCommand, "", output, capacity);
}

inline size_t buildNextCborRequest(uint8_t* output, size_t capacity) {
  return buildPlaybackCommandCborRequest(kNextCommand, "", output, capacity);
}

inline size_t buildPreviousCborRequest(uint8_t* output, size_t capacity) {
  return buildPlaybackCommandCborRequest(kPreviousCommand, "", output, capacity);
}

inline size_t buildSetVolumeCborRequest(int volumePercent, uint8_t* output, size_t capacity) {
  char volumeBuffer[12];
  snprintf(volumeBuffer, sizeof(volumeBuffer), "%d", volumePercent);
  return buildPlaybackCommandCborRequest(kVolumeCommand, volumeBuffer, output, capacity);
}

inline size_t buildShuffleCborRequest(const char* shuffleState, uint8_t* output, size_t capacity) {
  return buildPlaybackCommandCborRequest(kShuffleCommand, shuffleState, output, capacity);
}

inline size_t buildRepeatCborRequest(const char* repeatState, uint8_t* output, size_t capacity) {
  return buildPlaybackCommandCborRequest(kRepeatCommand, repeatState, output, capacity);
}

inline SpotifyPlaybackCommandParseStatus parsePlaybackCommandCborResponse(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    const char* responseKey,
    SpotifyPlaybackCommandResult& result) {
  CborVariant rootVariant = buffer.decode(const_cast<uint8_t*>(payload), length);
  if (!rootVariant.isObject()) {
    return SpotifyPlaybackCommandParseStatus::kInvalidPayload;
  }

  CborObject root = rootVariant.asObject();
  CborVariant responseVariant = root.get(responseKey);
  if (!responseVariant.isObject()) {
    return SpotifyPlaybackCommandParseStatus::kMissingResponse;
  }

  CborObject response = responseVariant.asObject();
  CborVariant resultVariant = response.get("result");
  if (!resultVariant.isString()) {
    return SpotifyPlaybackCommandParseStatus::kMissingResult;
  }

  CborVariant endpointIdVariant = root.get("endpointId");
  result.endpointId = endpointIdVariant.isString() ? endpointIdVariant.asString() : kUnknownEndpointId;
  result.result = resultVariant.asString();
  return SpotifyPlaybackCommandParseStatus::kOk;
}

inline SpotifyPlaybackCommandParseStatus parsePlayCborResponse(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandCborResponse(payload, length, buffer, kPlayResponse, result);
}

inline SpotifyPlaybackCommandParseStatus parsePauseCborResponse(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandCborResponse(payload, length, buffer, kPauseResponse, result);
}

inline SpotifyPlaybackCommandParseStatus parseNextCborResponse(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandCborResponse(payload, length, buffer, kNextResponse, result);
}

inline SpotifyPlaybackCommandParseStatus parsePreviousCborResponse(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandCborResponse(payload, length, buffer, kPreviousResponse, result);
}

inline SpotifyPlaybackCommandParseStatus parseSetVolumeCborResponse(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandCborResponse(payload, length, buffer, kVolumeResponse, result);
}

inline SpotifyPlaybackCommandParseStatus parseShuffleCborResponse(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandCborResponse(payload, length, buffer, kShuffleResponse, result);
}

inline SpotifyPlaybackCommandParseStatus parseRepeatCborResponse(
    const uint8_t* payload,
    size_t length,
    CborBuffer& buffer,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandCborResponse(payload, length, buffer, kRepeatResponse, result);
}

}  // namespace offbeat::spotify
