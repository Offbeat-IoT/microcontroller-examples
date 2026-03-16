from __future__ import annotations

from importlib.util import module_from_spec, spec_from_file_location
from pathlib import Path
import tempfile
import unittest


REPO_ROOT = Path(__file__).resolve().parents[1]
SCRIPT_PATH = REPO_ROOT / "scripts" / "compile_examples.py"
SPEC = spec_from_file_location("compile_examples", SCRIPT_PATH)
COMPILE_EXAMPLES = module_from_spec(SPEC)
assert SPEC.loader is not None
SPEC.loader.exec_module(COMPILE_EXAMPLES)


class CompileExamplesTest(unittest.TestCase):
    def test_find_sketch_directories_discovers_spotify_examples(self) -> None:
        sketch_directories = COMPILE_EXAMPLES.find_sketch_directories(REPO_ROOT)

        self.assertIn(REPO_ROOT / "examples" / "spotify" / "GetDevicesJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "GetDevicesCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "GetStateJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "GetStateCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "CurrentlyPlayingJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "CurrentlyPlayingCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlayJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlayCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PausePlaybackJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PausePlaybackCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "NextTrackJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "NextTrackCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PreviousTrackJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PreviousTrackCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "SetVolumeJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "SetVolumeCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "ShuffleOnJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "ShuffleOnCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "ShuffleOffJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "ShuffleOffCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "RepeatTrackJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "RepeatTrackCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "RepeatContextJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "RepeatContextCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "RepeatOffJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "RepeatOffCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "StopPlaybackJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "StopPlaybackCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "LikeCurrentTrackJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "LikeCurrentTrackCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "UnlikeCurrentTrackJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "UnlikeCurrentTrackCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlayContextJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlayContextCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlaySingleTrackJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlaySingleTrackCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlayUrisJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlayUrisCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlayOnDeviceJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlayOnDeviceCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlayItemsOnDeviceJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlayItemsOnDeviceCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "AlbumsJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "AlbumsCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "ArtistsJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "ArtistsCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "AudiobooksJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "AudiobooksCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "BrowseJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "BrowseCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "ChaptersJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "ChaptersCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "EpisodesJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "EpisodesCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlayerAdvancedJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlayerAdvancedCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlaylistsJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "PlaylistsCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "SearchJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "SearchCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "ShowsJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "ShowsCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "TracksJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "TracksCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "UsersJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "spotify" / "UsersCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "fitbit" / "ActivitiesJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "fitbit" / "ActivitiesCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "fitbit" / "BodyJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "fitbit" / "BodyCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "fitbit" / "FoodJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "fitbit" / "FoodCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "fitbit" / "WaterJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "fitbit" / "WaterCbor", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "fitbit" / "SleepJson", sketch_directories)
        self.assertIn(REPO_ROOT / "examples" / "fitbit" / "SleepCbor", sketch_directories)

    def test_ensure_local_config_headers_copies_missing_config(self) -> None:
        with tempfile.TemporaryDirectory() as temp_directory_name:
            temp_directory = Path(temp_directory_name)
            sketch_directory = temp_directory / "examples" / "spotify" / "GetDevicesJson"
            sketch_directory.mkdir(parents=True)
            example_header = sketch_directory / "offbeat_test_config.h.example"
            example_header.write_text("#define OFFBEAT_WIFI_SSID \"replace-me\"\n", encoding="utf-8")

            created_headers = COMPILE_EXAMPLES.ensure_local_config_headers([sketch_directory])

            created_header = sketch_directory / "offbeat_test_config.h"
            self.assertEqual([created_header], created_headers)
            self.assertEqual(example_header.read_text(encoding="utf-8"), created_header.read_text(encoding="utf-8"))

            COMPILE_EXAMPLES.cleanup_generated_config_headers(created_headers)
            self.assertFalse(created_header.exists())

    def test_patch_arduino_cbor_for_esp8266_injects_math_include_once(self) -> None:
        with tempfile.TemporaryDirectory() as temp_directory_name:
            temp_directory = Path(temp_directory_name)
            cbor_directory = temp_directory / "ArduinoCbor" / "src"
            cbor_directory.mkdir(parents=True)
            variant_file = cbor_directory / "CborVariant.cpp"
            variant_file.write_text('#include "CborVariant.h"\n\nint main() { return 0; }\n', encoding="utf-8")

            COMPILE_EXAMPLES.patch_arduino_cbor_for_esp8266(temp_directory)
            COMPILE_EXAMPLES.patch_arduino_cbor_for_esp8266(temp_directory)

            content = variant_file.read_text(encoding="utf-8")
            self.assertEqual(1, content.count("#include <math.h>"))


if __name__ == "__main__":
    unittest.main()
