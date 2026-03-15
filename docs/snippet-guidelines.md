# Snippet Guidelines

Use the real example sketches as the source of truth for documentation snippets.

Rules:

- keep the sketch runnable as-is once `offbeat_test_config.h` is provided
- mark the exact region intended for docs with AsciiDoc tags
- prefer one tag per user-visible example flow
- keep machine-readable serial markers in the runnable sketch so hardware tests can verify behavior
- do not commit real WiFi credentials or production endpoints

Current tag names:

- `spotify-get-devices-json-docs`
- `spotify-get-devices-cbor-docs`

