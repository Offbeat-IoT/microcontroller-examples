from __future__ import annotations

import json
from pathlib import Path
import unittest


REPO_ROOT = Path(__file__).resolve().parents[1]
TESTDATA_ROOT = REPO_ROOT / "testdata" / "google_home"


def load_json(path: Path) -> object:
    return json.loads(path.read_text(encoding="utf-8"))


class GoogleHomeContractTest(unittest.TestCase):
    def test_brightness_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "brightness_command.json")
        self.assertEqual(456, payload["absolute"]["brightness"])
        self.assertEqual(20, payload["relativePercent"]["adjustBrightnessPercent"])
        self.assertEqual(-1, payload["relativeWeight"]["adjustBrightnessWeight"])

    def test_power_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "power_command.json")
        self.assertEqual("TurnOn", payload["turnOn"]["powerstate"])
        self.assertEqual("TurnOff", payload["turnOff"]["powerstate"])

    def test_color_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "color_command.json")
        self.assertEqual(
            {"endpointId": "google-light-01", "hue": 665.0, "saturation": 123.0, "brightness": 456.0},
            payload,
        )

    def test_volume_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "volume_command.json")
        self.assertEqual(665, payload["setVolume"]["volume"])
        self.assertEqual(-1, payload["adjustVolume"]["volumesteps"])

    def test_media_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "media_command.json")
        self.assertEqual("Pause", payload["pause"]["playerControl"])
        self.assertEqual("Repeat", payload["repeat"]["playerControl"])
        self.assertEqual(30000, payload["seekAbsolute"]["SeekAbsolute"])
        self.assertEqual(-10000, payload["seekRelative"]["Seek"])

    def test_channel_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "channel_command.json")
        self.assertEqual(9, payload["setChannel"]["SetChannel"])
        self.assertEqual(1, payload["skipForward"]["skipChannel"])
        self.assertEqual(-1, payload["skipBack"]["skipChannel"])

    def test_google_home_examples_keep_docs_tags(self) -> None:
        expectations = {
            REPO_ROOT / "examples" / "google-home" / "BrightnessCommand" / "BrightnessCommand.ino": "google-home-brightness-command-docs",
            REPO_ROOT / "examples" / "google-home" / "PowerCommand" / "PowerCommand.ino": "google-home-power-command-docs",
            REPO_ROOT / "examples" / "google-home" / "ColorCommand" / "ColorCommand.ino": "google-home-color-command-docs",
            REPO_ROOT / "examples" / "google-home" / "VolumeCommand" / "VolumeCommand.ino": "google-home-volume-command-docs",
            REPO_ROOT / "examples" / "google-home" / "MediaCommand" / "MediaCommand.ino": "google-home-media-command-docs",
            REPO_ROOT / "examples" / "google-home" / "ChannelCommand" / "ChannelCommand.ino": "google-home-channel-command-docs",
        }

        for path, tag_name in expectations.items():
            content = path.read_text(encoding="utf-8")
            self.assertIn(f"// tag::{tag_name}[]", content)
            self.assertIn(f"// end::{tag_name}[]", content)

    def test_every_google_home_sketch_exposes_doc_tags(self) -> None:
        google_home_sketches = sorted((REPO_ROOT / "examples" / "google-home").glob("*/*.ino"))
        self.assertTrue(google_home_sketches)

        for sketch in google_home_sketches:
            content = sketch.read_text(encoding="utf-8")
            self.assertIn("// tag::google-home-", content, sketch.as_posix())
            self.assertIn("// end::google-home-", content, sketch.as_posix())


if __name__ == "__main__":
    unittest.main()
