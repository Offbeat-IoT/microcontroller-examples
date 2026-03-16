#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

#include <offbeat/spotify/SpotifyPlaybackCommand.h>

namespace offbeat::spotify {

inline bool buildPlaybackCommandJsonRequest(const char* command, const char* value, String& output) {
  StaticJsonDocument<96> payload;
  payload[command] = value;

  output = "";
  return serializeJson(payload, output) > 0;
}

inline bool buildPlayJsonRequest(String& output) {
  return buildPlaybackCommandJsonRequest(kPlayCommand, "", output);
}

inline bool buildPauseJsonRequest(String& output) {
  return buildPlaybackCommandJsonRequest(kPauseCommand, "", output);
}

inline bool buildNextJsonRequest(String& output) {
  return buildPlaybackCommandJsonRequest(kNextCommand, "", output);
}

inline bool buildPreviousJsonRequest(String& output) {
  return buildPlaybackCommandJsonRequest(kPreviousCommand, "", output);
}

inline bool buildSetVolumeJsonRequest(int volumePercent, String& output) {
  char volumeBuffer[12];
  snprintf(volumeBuffer, sizeof(volumeBuffer), "%d", volumePercent);
  return buildPlaybackCommandJsonRequest(kVolumeCommand, volumeBuffer, output);
}

inline bool buildShuffleJsonRequest(const char* shuffleState, String& output) {
  return buildPlaybackCommandJsonRequest(kShuffleCommand, shuffleState, output);
}

inline bool buildRepeatJsonRequest(const char* repeatState, String& output) {
  return buildPlaybackCommandJsonRequest(kRepeatCommand, repeatState, output);
}

template <typename JsonDocumentType>
inline SpotifyPlaybackCommandParseStatus parsePlaybackCommandJsonResponse(
    const uint8_t* payload,
    size_t length,
    JsonDocumentType& document,
    const char* responseKey,
    SpotifyPlaybackCommandResult& result) {
  DeserializationError error = deserializeJson(document, payload, length);
  if (error) {
    return SpotifyPlaybackCommandParseStatus::kInvalidPayload;
  }

  JsonObjectConst root = document.template as<JsonObjectConst>();
  JsonObjectConst response = root[responseKey].template as<JsonObjectConst>();
  if (response.isNull()) {
    return SpotifyPlaybackCommandParseStatus::kMissingResponse;
  }

  const char* commandResult = response["result"] | nullptr;
  if (commandResult == nullptr) {
    return SpotifyPlaybackCommandParseStatus::kMissingResult;
  }

  result.endpointId = root["endpointId"] | kUnknownEndpointId;
  result.result = commandResult;
  return SpotifyPlaybackCommandParseStatus::kOk;
}

template <typename JsonDocumentType>
inline SpotifyPlaybackCommandParseStatus parsePlayJsonResponse(
    const uint8_t* payload,
    size_t length,
    JsonDocumentType& document,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandJsonResponse(payload, length, document, kPlayResponse, result);
}

template <typename JsonDocumentType>
inline SpotifyPlaybackCommandParseStatus parsePauseJsonResponse(
    const uint8_t* payload,
    size_t length,
    JsonDocumentType& document,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandJsonResponse(payload, length, document, kPauseResponse, result);
}

template <typename JsonDocumentType>
inline SpotifyPlaybackCommandParseStatus parseNextJsonResponse(
    const uint8_t* payload,
    size_t length,
    JsonDocumentType& document,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandJsonResponse(payload, length, document, kNextResponse, result);
}

template <typename JsonDocumentType>
inline SpotifyPlaybackCommandParseStatus parsePreviousJsonResponse(
    const uint8_t* payload,
    size_t length,
    JsonDocumentType& document,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandJsonResponse(payload, length, document, kPreviousResponse, result);
}

template <typename JsonDocumentType>
inline SpotifyPlaybackCommandParseStatus parseSetVolumeJsonResponse(
    const uint8_t* payload,
    size_t length,
    JsonDocumentType& document,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandJsonResponse(payload, length, document, kVolumeResponse, result);
}

template <typename JsonDocumentType>
inline SpotifyPlaybackCommandParseStatus parseShuffleJsonResponse(
    const uint8_t* payload,
    size_t length,
    JsonDocumentType& document,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandJsonResponse(payload, length, document, kShuffleResponse, result);
}

template <typename JsonDocumentType>
inline SpotifyPlaybackCommandParseStatus parseRepeatJsonResponse(
    const uint8_t* payload,
    size_t length,
    JsonDocumentType& document,
    SpotifyPlaybackCommandResult& result) {
  return parsePlaybackCommandJsonResponse(payload, length, document, kRepeatResponse, result);
}

}  // namespace offbeat::spotify
