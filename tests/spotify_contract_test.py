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

    def test_spotify_examples_keep_docs_tags(self) -> None:
        expectations = {
            REPO_ROOT / "examples" / "spotify" / "GetDevicesJson" / "GetDevicesJson.ino": "spotify-get-devices-json-docs",
            REPO_ROOT / "examples" / "spotify" / "GetDevicesCbor" / "GetDevicesCbor.ino": "spotify-get-devices-cbor-docs",
        }

        for path, tag_name in expectations.items():
            content = path.read_text(encoding="utf-8")
            self.assertIn(f"// tag::{tag_name}[]", content)
            self.assertIn(f"// end::{tag_name}[]", content)


if __name__ == "__main__":
    unittest.main()
