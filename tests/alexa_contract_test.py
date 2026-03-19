from __future__ import annotations

import json
from pathlib import Path
import unittest


REPO_ROOT = Path(__file__).resolve().parents[1]
TESTDATA_ROOT = REPO_ROOT / "testdata" / "alexa"


def load_json(path: Path) -> object:
    return json.loads(path.read_text(encoding="utf-8"))


class AlexaContractTest(unittest.TestCase):
    def test_brightness_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "brightness_command.json")
        self.assertEqual(59, payload["setBrightness"]["adjustBrightnessPercent"])
        self.assertEqual(-3, payload["adjustBrightness"]["adjustBrightnessWeight"])

    def test_power_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "power_command.json")
        self.assertEqual("TurnOn", payload["turnOn"]["powerstate"])
        self.assertEqual("TurnOff", payload["turnOff"]["powerstate"])

    def test_color_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "color_command.json")
        self.assertEqual(
            {"endpointId": "alexa-light-01", "hue": 350.5, "saturation": 0.7138, "brightness": 0.6524},
            payload,
        )

    def test_speaker_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "speaker_command.json")
        self.assertEqual(30, payload["setVolume"]["volume"])
        self.assertEqual(20, payload["adjustVolume"]["volumesteps"])
        self.assertFalse(payload["mute"]["mute"])

    def test_playback_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "playback_command.json")
        self.assertEqual("Play", payload["play"]["playerControl"])
        self.assertEqual("Pause", payload["pause"]["playerControl"])
        self.assertEqual("Next", payload["next"]["playerControl"])
        self.assertEqual("Prev", payload["previous"]["playerControl"])
        self.assertEqual("Stop", payload["stop"]["playerControl"])

    def test_channel_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "channel_command.json")
        self.assertEqual(1, payload["setChannel"]["SetChannel"])
        self.assertEqual(1, payload["skipChannel"]["skipChannel"])

    def test_scene_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "scene_command.json")
        self.assertEqual("TurnOn", payload["activate"]["scenestate"])
        self.assertEqual("TurnOff", payload["deactivate"]["scenestate"])

    def test_thermostat_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "thermostat_command.json")
        self.assertEqual("COOL", payload["thermMode"])

    def test_blind_tilt_command_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "blind_tilt_command.json")
        self.assertEqual(60, payload["set"]["rangeValue"])
        self.assertEqual(-10, payload["adjust"]["rangeValueDelta"])

    def test_alexa_examples_keep_docs_tags(self) -> None:
        expectations = {
            REPO_ROOT / "examples" / "alexa" / "BrightnessCommand" / "BrightnessCommand.ino": "alexa-brightness-command-docs",
            REPO_ROOT / "examples" / "alexa" / "PowerCommand" / "PowerCommand.ino": "alexa-power-command-docs",
            REPO_ROOT / "examples" / "alexa" / "ColorCommand" / "ColorCommand.ino": "alexa-color-command-docs",
            REPO_ROOT / "examples" / "alexa" / "SpeakerCommand" / "SpeakerCommand.ino": "alexa-speaker-command-docs",
            REPO_ROOT / "examples" / "alexa" / "PlaybackCommand" / "PlaybackCommand.ino": "alexa-playback-command-docs",
            REPO_ROOT / "examples" / "alexa" / "ChannelCommand" / "ChannelCommand.ino": "alexa-channel-command-docs",
            REPO_ROOT / "examples" / "alexa" / "SceneCommand" / "SceneCommand.ino": "alexa-scene-command-docs",
            REPO_ROOT / "examples" / "alexa" / "ThermostatCommand" / "ThermostatCommand.ino": "alexa-thermostat-command-docs",
            REPO_ROOT / "examples" / "alexa" / "BlindTiltCommand" / "BlindTiltCommand.ino": "alexa-blind-tilt-command-docs",
        }

        for path, tag_name in expectations.items():
            content = path.read_text(encoding="utf-8")
            self.assertIn(f"// tag::{tag_name}[]", content)
            self.assertIn(f"// end::{tag_name}[]", content)

    def test_every_alexa_sketch_exposes_doc_tags(self) -> None:
        alexa_sketches = sorted((REPO_ROOT / "examples" / "alexa").glob("*/*.ino"))
        self.assertTrue(alexa_sketches)

        for sketch in alexa_sketches:
            content = sketch.read_text(encoding="utf-8")
            self.assertIn("// tag::alexa-", content, sketch.as_posix())
            self.assertIn("// end::alexa-", content, sketch.as_posix())


if __name__ == "__main__":
    unittest.main()
