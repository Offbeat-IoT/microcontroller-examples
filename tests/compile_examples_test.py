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
