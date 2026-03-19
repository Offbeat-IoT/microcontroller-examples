#pragma once

#include <offbeat/core/WebsocketJsonExampleSupport.h>

namespace offbeat::alexa::examples {

using ParseStatus = offbeat::core::examples::ParseStatus;
using offbeat::core::examples::connectWifi;
using offbeat::core::examples::parseRoot;
using offbeat::core::examples::printEndpoint;
using offbeat::core::examples::printLine;
using offbeat::core::examples::readBool;
using offbeat::core::examples::readDouble;
using offbeat::core::examples::readEndpointId;
using offbeat::core::examples::readLong;
using offbeat::core::examples::readString;

constexpr char kAdjustBrightnessPercentKey[] = "adjustBrightnessPercent";
constexpr char kAdjustBrightnessWeightKey[] = "adjustBrightnessWeight";
constexpr char kBrightnessKey[] = "brightness";
constexpr char kHueKey[] = "hue";
constexpr char kMuteKey[] = "mute";
constexpr char kPlayerControlKey[] = "playerControl";
constexpr char kPowerStateKey[] = "powerstate";
constexpr char kRangeValueKey[] = "rangeValue";
constexpr char kRangeValueDeltaKey[] = "rangeValueDelta";
constexpr char kSceneStateKey[] = "scenestate";
constexpr char kSaturationKey[] = "saturation";
constexpr char kSetChannelKey[] = "SetChannel";
constexpr char kSkipChannelKey[] = "skipChannel";
constexpr char kThermostatModeKey[] = "thermMode";
constexpr char kVolumeKey[] = "volume";
constexpr char kVolumeStepsKey[] = "volumesteps";

}  // namespace offbeat::alexa::examples
