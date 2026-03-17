# microcontroller-examples

Public Arduino examples for Offbeat integrations.

This repository is the source of truth for:

- user-facing example sketches that can be opened directly in Arduino IDE
- code snippets included in the Offbeat UI documentation
- small provider-specific helpers that keep the examples readable without turning into a generic framework

## Repository Shape

```text
src/offbeat/spotify
src/offbeat/fitbit
src/offbeat/alexa
src/offbeat/google_home
examples/spotify
examples/fitbit
examples/alexa
examples/google-home
testdata/spotify
tests
scripts
```

The naming stays generic at the repository level and specific inside each provider folder. That gives room for Spotify, Fitbit, Alexa, and Google Home without mixing their example flows together.

## Small Library Structure

The shared code is intentionally narrow:

- `src/offbeat/spotify/SpotifyGetDevices.h` defines the command keys, parse status, and the `SpotifyDevice` struct.
- `src/offbeat/spotify/SpotifyGetDevicesJson.h` builds the JSON request and visits parsed JSON devices.
- `src/offbeat/spotify/SpotifyGetDevicesCbor.h` builds the CBOR request and visits parsed CBOR devices.
- `src/offbeat/spotify/SpotifyPlaybackState.h` defines the request keys and the small playback-state structs used by `get state` and `currently playing`.
- `src/offbeat/spotify/SpotifyPlaybackStateJson.h` builds JSON playback-state requests and parses the matching response payloads.
- `src/offbeat/spotify/SpotifyPlaybackStateCbor.h` builds CBOR playback-state requests and parses the matching response payloads.
- `src/SpotifyGetDevicesJson.h` and `src/SpotifyGetDevicesCbor.h` are thin Arduino-friendly entry headers that forward to the provider-specific implementation.
- `src/SpotifyPlaybackStateJson.h` and `src/SpotifyPlaybackStateCbor.h` do the same for the playback-state examples.
- `src/offbeat/fitbit/FitbitExampleSupport.h` owns the shared WiFi setup used by the Fitbit examples.
- `src/offbeat/fitbit/FitbitJsonExampleSupport.h` and `src/offbeat/fitbit/FitbitCborExampleSupport.h` build Fitbit requests, parse payload roots, and print common response values.
- `src/FitbitJsonExampleSupport.h` and `src/FitbitCborExampleSupport.h` are the Arduino-friendly forwarding headers used from the real Fitbit sketches.
- `src/offbeat/core/WebsocketJsonExampleSupport.h` keeps the shared WiFi and incoming JSON command parsing helpers small for device-side command examples.
- `src/offbeat/alexa/AlexaExampleSupport.h` and `src/offbeat/google_home/GoogleHomeExampleSupport.h` define the small command-key helpers used by the Alexa and Google Home device examples.
- `src/AlexaExampleSupport.h` and `src/GoogleHomeExampleSupport.h` are the Arduino-friendly forwarding headers used from the assistant sketches.

The sketches still own:

- WiFi setup
- websocket wiring
- serial logging
- user-visible handling of parsed values

That keeps the examples easy for customers to follow and avoids growing a large library layer that may never be used.

## Testing

This repository keeps hardware out of the default test flow. The confidence model is:

1. Host-side contract tests validate the JSON and CBOR payload shapes.
2. `arduino-cli` compile checks prove the real sketches still build for the target board.
3. Manual board testing can be done later once a set of examples is stable.

GitHub Actions runs the same flow on every push and pull request via [.github/workflows/build.yml](./.github/workflows/build.yml).

Install the host-side test dependency:

```bash
python -m pip install -r requirements-test.txt
```

Run the contract tests:

```bash
python -m unittest discover -s tests -p "*_test.py"
```

Compile every example for NodeMCU / ESP8266:

```bash
python scripts/compile_examples.py --fqbn esp8266:esp8266:nodemcuv2
```

The compile script does the repetitive setup for you:

- installs the ESP8266 core with `arduino-cli`
- installs `ArduinoJson` and `WebSockets`
- clones `ArduinoCbor` into `.arduino-libraries/`
- patches `ArduinoCbor` locally with `#include <math.h>` so it builds on ESP8266
- copies each `offbeat_test_config.h.example` to a temporary local `offbeat_test_config.h`
- compiles every sketch under `examples/`
- removes the generated local config headers afterwards

## Provider Coverage

Current providers:

- `spotify`: real JSON and CBOR sketches for playback, library, browse, and profile requests
- `fitbit`: real JSON and CBOR sketches for activities, body, food, water, and sleep requests
- `alexa`: real device-side sketches for power, brightness, color, speaker, playback, channel, scene, and thermostat commands
- `google-home`: real device-side sketches for power, brightness, color, volume, media, and channel commands

## Current Example Dependencies

The current Spotify and Fitbit examples use:

- `ESP8266WiFi`
- `WebSockets`
- `ArduinoJson`
- `ArduinoCbor` from `https://github.com/bergos/ArduinoCbor`

The Alexa and Google Home device-side examples use:

- `ESP8266WiFi`
- `WebSockets`
- `ArduinoJson`

## Configuration

The example sketches expect a local, uncommitted file named:

```text
offbeat_test_config.h
```

Each example folder contains an `offbeat_test_config.h.example` template that can be copied and edited locally for manual use.

The compile script can generate temporary local config headers automatically for build verification.

## Documentation Includes

AsciiDoc pages should include tagged regions from the real `.ino` files rather than re-generating snippets elsewhere.
