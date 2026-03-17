# microcontroller-examples

## Goal

Keep the public examples easy to copy into Arduino IDE while still proving that the protocol shape is correct without real hardware in CI.

## Done When

Run these checks from the repository root:

```bash
python -m pip install -r requirements-test.txt
python -m unittest discover -s tests -p "*_test.py"
python scripts/compile_examples.py --fqbn esp8266:esp8266:nodemcuv2
```

## Testing Notes

- `tests/` contains host-side contract tests for the JSON and CBOR request/response fixtures.
- `scripts/compile_examples.py` compiles every sketch under `examples/`.
- The compile script copies `offbeat_test_config.h.example` to a temporary local `offbeat_test_config.h` when needed, then deletes the generated file afterwards.
- The compile script installs `ArduinoJson` and `WebSockets` with `arduino-cli`.
- `ArduinoCbor` is cloned into `.arduino-libraries/` and patched locally with `#include <math.h>` so the ESP8266 build works.
- Keep docs snippets inside the runnable `.ino` files using the existing AsciiDoc tags.
- Do not commit real WiFi credentials or production endpoints.

## Library Shape

- Keep shared code feature-specific.
- Put reusable Spotify get-devices helpers in `src/offbeat/spotify/`.
- Put assistant device-command helpers in `src/offbeat/alexa/`, `src/offbeat/google_home/`, and shared incoming-json utilities in `src/offbeat/core/` only when both providers genuinely need them.
- Keep WiFi setup, websocket wiring, and serial printing inside the example sketches so customers can understand the full flow quickly.
- Do not add generic provider frameworks unless two examples genuinely need the same logic.
