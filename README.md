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
- `src/SpotifyGetDevicesJson.h` and `src/SpotifyGetDevicesCbor.h` are thin Arduino-friendly entry headers that forward to the provider-specific implementation.

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

## Current Example Dependencies

The first Spotify examples use:

- `ESP8266WiFi`
- `WebSockets`
- `ArduinoJson`
- `ArduinoCbor` from `https://github.com/bergos/ArduinoCbor`

## Configuration

The example sketches expect a local, uncommitted file named:

```text
offbeat_test_config.h
```

Each example folder contains an `offbeat_test_config.h.example` template that can be copied and edited locally for manual use.

The compile script can generate temporary local config headers automatically for build verification.

## Documentation Includes

AsciiDoc pages should include tagged regions from the real `.ino` files rather than re-generating snippets elsewhere.
