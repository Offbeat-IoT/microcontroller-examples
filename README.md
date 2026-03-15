# microcontroller-examples

Public Arduino examples for Offbeat integrations.

This repository is the source of truth for:

- user-facing example sketches that can be opened directly in Arduino IDE
- code snippets included in the Offbeat UI documentation
- provider-oriented examples with room for Spotify, Fitbit, Alexa, and Google Home

## Structure

```text
src/offbeat/core
src/offbeat/spotify
src/offbeat/fitbit
src/offbeat/alexa
src/offbeat/google_home
examples/spotify
examples/fitbit
examples/alexa
examples/google-home
```

## Current Example Dependencies

The first Spotify examples use:

- `ESP8266WiFi`
- `WebSockets`
- `ArduinoJson`
- `ArduinoCbor` from `https://github.com/bergos/ArduinoCbor`

`ArduinoJson` and `WebSockets` can be installed with the Arduino Library Manager.

`ArduinoCbor` currently needs to be installed manually from GitHub.

## Configuration

The example sketches expect a local, uncommitted file named:

```text
offbeat_test_config.h
```

Each example folder contains an `offbeat_test_config.h.example` template that can be copied and edited locally.

The private `microcontroller-examples-tests` repository generates the real `offbeat_test_config.h` automatically before compile/upload.

## Documentation Includes

AsciiDoc pages should include tagged regions from the real `.ino` files rather than re-generating snippets elsewhere.
