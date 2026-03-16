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


def normalize_command_result(payload: dict[str, object], response_key: str) -> dict[str, str]:
    response = payload[response_key]
    assert isinstance(response, dict)
    return {
        "endpointId": str(payload.get("endpointId", "unknown")),
        "result": str(response.get("result", "unknown")),
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

    def test_play_json_request_contract(self) -> None:
        request_payload = json.loads((TESTDATA_ROOT / "play_request.json").read_text(encoding="utf-8"))
        self.assertEqual({"spotify.play": ""}, request_payload)

    def test_play_cbor_request_contract(self) -> None:
        request_payload = load_cbor_hex(TESTDATA_ROOT / "play_request.cbor.hex")
        self.assertEqual({"spotify.play": ""}, request_payload)

    def test_play_json_response_contract(self) -> None:
        response_payload = json.loads((TESTDATA_ROOT / "play_response.json").read_text(encoding="utf-8"))
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.play.response"),
        )

    def test_play_cbor_response_contract(self) -> None:
        response_payload = load_cbor_hex(TESTDATA_ROOT / "play_response.cbor.hex")
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.play.response"),
        )

    def test_pause_json_request_contract(self) -> None:
        request_payload = json.loads((TESTDATA_ROOT / "pause_request.json").read_text(encoding="utf-8"))
        self.assertEqual({"spotify.pause": ""}, request_payload)

    def test_pause_cbor_request_contract(self) -> None:
        request_payload = load_cbor_hex(TESTDATA_ROOT / "pause_request.cbor.hex")
        self.assertEqual({"spotify.pause": ""}, request_payload)

    def test_pause_json_response_contract(self) -> None:
        response_payload = json.loads((TESTDATA_ROOT / "pause_response.json").read_text(encoding="utf-8"))
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.pause.response"),
        )

    def test_pause_cbor_response_contract(self) -> None:
        response_payload = load_cbor_hex(TESTDATA_ROOT / "pause_response.cbor.hex")
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.pause.response"),
        )

    def test_next_json_request_contract(self) -> None:
        request_payload = json.loads((TESTDATA_ROOT / "next_request.json").read_text(encoding="utf-8"))
        self.assertEqual({"spotify.next": ""}, request_payload)

    def test_next_cbor_request_contract(self) -> None:
        request_payload = load_cbor_hex(TESTDATA_ROOT / "next_request.cbor.hex")
        self.assertEqual({"spotify.next": ""}, request_payload)

    def test_next_json_response_contract(self) -> None:
        response_payload = json.loads((TESTDATA_ROOT / "next_response.json").read_text(encoding="utf-8"))
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.next.response"),
        )

    def test_next_cbor_response_contract(self) -> None:
        response_payload = load_cbor_hex(TESTDATA_ROOT / "next_response.cbor.hex")
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.next.response"),
        )

    def test_previous_json_request_contract(self) -> None:
        request_payload = json.loads((TESTDATA_ROOT / "previous_request.json").read_text(encoding="utf-8"))
        self.assertEqual({"spotify.previous": ""}, request_payload)

    def test_previous_cbor_request_contract(self) -> None:
        request_payload = load_cbor_hex(TESTDATA_ROOT / "previous_request.cbor.hex")
        self.assertEqual({"spotify.previous": ""}, request_payload)

    def test_previous_json_response_contract(self) -> None:
        response_payload = json.loads((TESTDATA_ROOT / "previous_response.json").read_text(encoding="utf-8"))
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.previous.response"),
        )

    def test_previous_cbor_response_contract(self) -> None:
        response_payload = load_cbor_hex(TESTDATA_ROOT / "previous_response.cbor.hex")
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.previous.response"),
        )

    def test_set_volume_json_request_contract(self) -> None:
        request_payload = json.loads((TESTDATA_ROOT / "set_volume_request.json").read_text(encoding="utf-8"))
        self.assertEqual({"spotify.volume": "12"}, request_payload)

    def test_set_volume_cbor_request_contract(self) -> None:
        request_payload = load_cbor_hex(TESTDATA_ROOT / "set_volume_request.cbor.hex")
        self.assertEqual({"spotify.volume": "12"}, request_payload)

    def test_set_volume_json_response_contract(self) -> None:
        response_payload = json.loads((TESTDATA_ROOT / "set_volume_response.json").read_text(encoding="utf-8"))
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.volume.response"),
        )

    def test_set_volume_cbor_response_contract(self) -> None:
        response_payload = load_cbor_hex(TESTDATA_ROOT / "set_volume_response.cbor.hex")
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.volume.response"),
        )

    def test_shuffle_json_request_contract(self) -> None:
        request_payload = json.loads((TESTDATA_ROOT / "shuffle_request.json").read_text(encoding="utf-8"))
        self.assertEqual({"spotify.shuffle": "on"}, request_payload)

    def test_shuffle_cbor_request_contract(self) -> None:
        request_payload = load_cbor_hex(TESTDATA_ROOT / "shuffle_request.cbor.hex")
        self.assertEqual({"spotify.shuffle": "on"}, request_payload)

    def test_shuffle_json_response_contract(self) -> None:
        response_payload = json.loads((TESTDATA_ROOT / "shuffle_response.json").read_text(encoding="utf-8"))
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.shuffle.response"),
        )

    def test_shuffle_cbor_response_contract(self) -> None:
        response_payload = load_cbor_hex(TESTDATA_ROOT / "shuffle_response.cbor.hex")
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.shuffle.response"),
        )

    def test_repeat_json_request_contract(self) -> None:
        request_payload = json.loads((TESTDATA_ROOT / "repeat_request.json").read_text(encoding="utf-8"))
        self.assertEqual({"spotify.repeat": "track"}, request_payload)

    def test_repeat_cbor_request_contract(self) -> None:
        request_payload = load_cbor_hex(TESTDATA_ROOT / "repeat_request.cbor.hex")
        self.assertEqual({"spotify.repeat": "track"}, request_payload)

    def test_repeat_json_response_contract(self) -> None:
        response_payload = json.loads((TESTDATA_ROOT / "repeat_response.json").read_text(encoding="utf-8"))
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.repeat.response"),
        )

    def test_repeat_cbor_response_contract(self) -> None:
        response_payload = load_cbor_hex(TESTDATA_ROOT / "repeat_response.cbor.hex")
        self.assertEqual(
            {
                "endpointId": "test-endpoint-id",
                "result": "OK",
            },
            normalize_command_result(response_payload, "spotify.repeat.response"),
        )

    def test_spotify_examples_keep_docs_tags(self) -> None:
        expectations = {
            REPO_ROOT / "examples" / "spotify" / "GetDevicesJson" / "GetDevicesJson.ino": "spotify-get-devices-json-docs",
            REPO_ROOT / "examples" / "spotify" / "GetDevicesCbor" / "GetDevicesCbor.ino": "spotify-get-devices-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "GetStateJson" / "GetStateJson.ino": "spotify-get-state-json-docs",
            REPO_ROOT / "examples" / "spotify" / "GetStateCbor" / "GetStateCbor.ino": "spotify-get-state-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "CurrentlyPlayingJson" / "CurrentlyPlayingJson.ino": "spotify-currently-playing-json-docs",
            REPO_ROOT / "examples" / "spotify" / "CurrentlyPlayingCbor" / "CurrentlyPlayingCbor.ino": "spotify-currently-playing-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "PlayJson" / "PlayJson.ino": "spotify-play-json-docs",
            REPO_ROOT / "examples" / "spotify" / "PlayCbor" / "PlayCbor.ino": "spotify-play-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "PausePlaybackJson" / "PausePlaybackJson.ino": "spotify-pause-json-docs",
            REPO_ROOT / "examples" / "spotify" / "PausePlaybackCbor" / "PausePlaybackCbor.ino": "spotify-pause-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "NextTrackJson" / "NextTrackJson.ino": "spotify-next-json-docs",
            REPO_ROOT / "examples" / "spotify" / "NextTrackCbor" / "NextTrackCbor.ino": "spotify-next-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "PreviousTrackJson" / "PreviousTrackJson.ino": "spotify-previous-json-docs",
            REPO_ROOT / "examples" / "spotify" / "PreviousTrackCbor" / "PreviousTrackCbor.ino": "spotify-previous-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "SetVolumeJson" / "SetVolumeJson.ino": "spotify-set-volume-json-docs",
            REPO_ROOT / "examples" / "spotify" / "SetVolumeCbor" / "SetVolumeCbor.ino": "spotify-set-volume-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "ShuffleOnJson" / "ShuffleOnJson.ino": "spotify-shuffle-on-json-docs",
            REPO_ROOT / "examples" / "spotify" / "ShuffleOnCbor" / "ShuffleOnCbor.ino": "spotify-shuffle-on-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "ShuffleOffJson" / "ShuffleOffJson.ino": "spotify-shuffle-off-json-docs",
            REPO_ROOT / "examples" / "spotify" / "ShuffleOffCbor" / "ShuffleOffCbor.ino": "spotify-shuffle-off-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "RepeatTrackJson" / "RepeatTrackJson.ino": "spotify-repeat-track-json-docs",
            REPO_ROOT / "examples" / "spotify" / "RepeatTrackCbor" / "RepeatTrackCbor.ino": "spotify-repeat-track-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "RepeatContextJson" / "RepeatContextJson.ino": "spotify-repeat-context-json-docs",
            REPO_ROOT / "examples" / "spotify" / "RepeatContextCbor" / "RepeatContextCbor.ino": "spotify-repeat-context-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "RepeatOffJson" / "RepeatOffJson.ino": "spotify-repeat-off-json-docs",
            REPO_ROOT / "examples" / "spotify" / "RepeatOffCbor" / "RepeatOffCbor.ino": "spotify-repeat-off-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "StopPlaybackJson" / "StopPlaybackJson.ino": "spotify-stop-json-docs",
            REPO_ROOT / "examples" / "spotify" / "StopPlaybackCbor" / "StopPlaybackCbor.ino": "spotify-stop-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "LikeCurrentTrackJson" / "LikeCurrentTrackJson.ino": "spotify-like-json-docs",
            REPO_ROOT / "examples" / "spotify" / "LikeCurrentTrackCbor" / "LikeCurrentTrackCbor.ino": "spotify-like-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "UnlikeCurrentTrackJson" / "UnlikeCurrentTrackJson.ino": "spotify-unlike-json-docs",
            REPO_ROOT / "examples" / "spotify" / "UnlikeCurrentTrackCbor" / "UnlikeCurrentTrackCbor.ino": "spotify-unlike-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "PlayContextJson" / "PlayContextJson.ino": "spotify-play-context-json-docs",
            REPO_ROOT / "examples" / "spotify" / "PlayContextCbor" / "PlayContextCbor.ino": "spotify-play-context-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "PlaySingleTrackJson" / "PlaySingleTrackJson.ino": "spotify-play-single-track-json-docs",
            REPO_ROOT / "examples" / "spotify" / "PlaySingleTrackCbor" / "PlaySingleTrackCbor.ino": "spotify-play-single-track-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "PlayUrisJson" / "PlayUrisJson.ino": "spotify-play-uris-json-docs",
            REPO_ROOT / "examples" / "spotify" / "PlayUrisCbor" / "PlayUrisCbor.ino": "spotify-play-uris-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "PlayOnDeviceJson" / "PlayOnDeviceJson.ino": "spotify-play-on-device-json-docs",
            REPO_ROOT / "examples" / "spotify" / "PlayOnDeviceCbor" / "PlayOnDeviceCbor.ino": "spotify-play-on-device-cbor-docs",
            REPO_ROOT / "examples" / "spotify" / "PlayItemsOnDeviceJson" / "PlayItemsOnDeviceJson.ino": "spotify-play-items-on-device-json-docs",
            REPO_ROOT / "examples" / "spotify" / "PlayItemsOnDeviceCbor" / "PlayItemsOnDeviceCbor.ino": "spotify-play-items-on-device-cbor-docs",
        }

        for path, tag_name in expectations.items():
            content = path.read_text(encoding="utf-8")
            self.assertIn(f"// tag::{tag_name}[]", content)
            self.assertIn(f"// end::{tag_name}[]", content)

    def test_every_spotify_sketch_exposes_doc_tags(self) -> None:
        spotify_sketches = sorted((REPO_ROOT / "examples" / "spotify").glob("*/*.ino"))
        self.assertTrue(spotify_sketches)

        for sketch in spotify_sketches:
            content = sketch.read_text(encoding="utf-8")
            self.assertIn("// tag::spotify-", content, sketch.as_posix())
            self.assertIn("// end::spotify-", content, sketch.as_posix())


if __name__ == "__main__":
    unittest.main()
