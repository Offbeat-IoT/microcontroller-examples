from __future__ import annotations

import json
from pathlib import Path
import unittest

import cbor2


REPO_ROOT = Path(__file__).resolve().parents[1]
TESTDATA_ROOT = REPO_ROOT / "testdata" / "spotify"


def load_cbor_hex(path: Path) -> object:
    return cbor2.loads(bytes.fromhex(path.read_text(encoding="utf-8").strip()))


def normalize_devices(payload: dict[str, object]) -> list[tuple[str, str, int]]:
    devices = payload["spotify.devices.response"]
    assert isinstance(devices, dict)
    normalized: list[tuple[str, str, int]] = []
    for device_id, device in devices.items():
        assert isinstance(device, dict)
        normalized.append(
            (
                str(device_id),
                str(device.get("name", "unknown")),
                int(device.get("volume", -1)),
            )
        )
    return sorted(normalized)


def normalize_playback_state(payload: dict[str, object], response_key: str) -> dict[str, object]:
    response = payload[response_key]
    assert isinstance(response, dict)
    item = response["item"]
    device = response["device"]
    assert isinstance(item, dict)
    assert isinstance(device, dict)
    return {
        "isPlaying": bool(response["isPlaying"]),
        "trackName": str(item.get("name", "unknown")),
        "artist": str(item.get("artist", "unknown")),
        "album": str(item.get("album", "unknown")),
        "deviceId": str(device.get("id", "unknown")),
        "deviceName": str(device.get("name", "unknown")),
        "volumePercent": int(device.get("volumepercent", -1)),
        "hasShuffling": "shuffling" in response,
        "shuffling": response.get("shuffling"),
    }


class SpotifyContractTest(unittest.TestCase):
    def test_get_devices_json_request_contract(self) -> None:
        request_payload = json.loads((TESTDATA_ROOT / "get_devices_request.json").read_text(encoding="utf-8"))
        self.assertEqual({"spotify.devices": ""}, request_payload)

    def test_get_devices_cbor_request_contract(self) -> None:
        request_payload = load_cbor_hex(TESTDATA_ROOT / "get_devices_request.cbor.hex")
        self.assertEqual({"spotify.devices": ""}, request_payload)

    def test_get_devices_json_response_contract(self) -> None:
        response_payload = json.loads((TESTDATA_ROOT / "get_devices_response.json").read_text(encoding="utf-8"))
        self.assertEqual(
            [
                ("device-kitchen", "Kitchen", 42),
                ("device-office", "Office", 17),
            ],
            normalize_devices(response_payload),
        )

    def test_get_devices_cbor_response_contract(self) -> None:
        response_payload = load_cbor_hex(TESTDATA_ROOT / "get_devices_response.cbor.hex")
        self.assertEqual(
            [
                ("device-kitchen", "Kitchen", 42),
                ("device-office", "Office", 17),
            ],
            normalize_devices(response_payload),
        )

    def test_get_state_json_request_contract(self) -> None:
        request_payload = json.loads((TESTDATA_ROOT / "get_state_request.json").read_text(encoding="utf-8"))
        self.assertEqual({"spotify.state": ""}, request_payload)

    def test_get_state_cbor_request_contract(self) -> None:
        request_payload = load_cbor_hex(TESTDATA_ROOT / "get_state_request.cbor.hex")
        self.assertEqual({"spotify.state": ""}, request_payload)

    def test_get_state_json_response_contract(self) -> None:
        response_payload = json.loads((TESTDATA_ROOT / "get_state_response.json").read_text(encoding="utf-8"))
        self.assertEqual(
            {
                "isPlaying": True,
                "trackName": "Sample Track",
                "artist": "Sample Artist",
                "album": "Sample Album",
                "deviceId": "string",
                "deviceName": "Kitchen speaker",
                "volumePercent": 59,
                "hasShuffling": True,
                "shuffling": False,
            },
            normalize_playback_state(response_payload, "spotify.state.response"),
        )

    def test_get_state_cbor_response_contract(self) -> None:
        response_payload = load_cbor_hex(TESTDATA_ROOT / "get_state_response.cbor.hex")
        self.assertEqual(
            {
                "isPlaying": True,
                "trackName": "Sample Track",
                "artist": "Sample Artist",
                "album": "Sample Album",
                "deviceId": "string",
                "deviceName": "Kitchen speaker",
                "volumePercent": 59,
                "hasShuffling": True,
                "shuffling": False,
            },
            normalize_playback_state(response_payload, "spotify.state.response"),
        )

    def test_currently_playing_json_request_contract(self) -> None:
        request_payload = json.loads((TESTDATA_ROOT / "currently_playing_request.json").read_text(encoding="utf-8"))
        self.assertEqual({"spotify.currently-playing": ""}, request_payload)

    def test_currently_playing_cbor_request_contract(self) -> None:
        request_payload = load_cbor_hex(TESTDATA_ROOT / "currently_playing_request.cbor.hex")
        self.assertEqual({"spotify.currently-playing": ""}, request_payload)

    def test_currently_playing_json_response_contract(self) -> None:
        response_payload = json.loads((TESTDATA_ROOT / "currently_playing_response.json").read_text(encoding="utf-8"))
        self.assertEqual(
            {
                "isPlaying": False,
                "trackName": "Sample Track",
                "artist": "Sample Artist",
                "album": "Sample Album",
                "deviceId": "string",
                "deviceName": "Kitchen speaker",
                "volumePercent": 59,
                "hasShuffling": False,
                "shuffling": None,
            },
            normalize_playback_state(response_payload, "spotify.currently-playing.response"),
        )

    def test_currently_playing_cbor_response_contract(self) -> None:
        response_payload = load_cbor_hex(TESTDATA_ROOT / "currently_playing_response.cbor.hex")
        self.assertEqual(
            {
                "isPlaying": False,
                "trackName": "Sample Track",
                "artist": "Sample Artist",
                "album": "Sample Album",
                "deviceId": "string",
                "deviceName": "Kitchen speaker",
                "volumePercent": 59,
                "hasShuffling": False,
                "shuffling": None,
            },
            normalize_playback_state(response_payload, "spotify.currently-playing.response"),
        )

    def test_spotify_examples_keep_docs_tags(self) -> None:
        expectations = {
            REPO_ROOT / "examples" / "spotify" / "GetDevicesJson" / "GetDevicesJson.ino": "spotify-get-devices-json-docs",
            REPO_ROOT / "examples" / "spotify" / "GetDevicesCbor" / "GetDevicesCbor.ino": "spotify-get-devices-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "GetStateJson" / "GetStateJson.ino": "spotify-get-state-json-docs",
            REPO_ROOT / "examples" / "spotify" / "GetStateCbor" / "GetStateCbor.ino": "spotify-get-state-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "CurrentlyPlayingJson" / "CurrentlyPlayingJson.ino": "spotify-currently-playing-json-docs",
            REPO_ROOT / "examples" / "spotify" / "CurrentlyPlayingCbor" / "CurrentlyPlayingCbor.ino": "spotify-currently-playing-cbor-docs",
        }

        for path, tag_name in expectations.items():
            content = path.read_text(encoding="utf-8")
            self.assertIn(f"// tag::{tag_name}[]", content)
            self.assertIn(f"// end::{tag_name}[]", content)


if __name__ == "__main__":
    unittest.main()
