from __future__ import annotations

import json
from pathlib import Path
import unittest


REPO_ROOT = Path(__file__).resolve().parents[1]
TESTDATA_ROOT = REPO_ROOT / "testdata" / "camera"
SKETCH = REPO_ROOT / "examples" / "camera" / "ChunkedVideoStream" / "ChunkedVideoStream.ino"

# Server-side camera.stream.* defaults documented in connection-transport
# (docs/camera-chunked-stream.md). An agreement outside these bounds is rejected before any
# chunk is accepted, so the example has to stay inside them.
MAX_CHUNK_BYTES = 32768
MAX_CHUNKS = 128
MAX_IMAGE_BYTES = 262144


def load_json(path: Path) -> object:
    return json.loads(path.read_text(encoding="utf-8"))


class CameraChunkedStreamContractTest(unittest.TestCase):
    def test_chunked_confirmation_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "chunked_confirmation.json")
        self.assertEqual({"cameraStream": "chunked-v1"}, payload)

    def test_stream_agreement_stays_inside_server_limits(self) -> None:
        payload = load_json(TESTDATA_ROOT / "stream_agreement.json")
        agreement = payload["cameraStream"]

        self.assertGreater(agreement["chunkSize"], 0)
        self.assertGreater(agreement["chunkCount"], 0)
        self.assertLessEqual(agreement["chunkSize"], MAX_CHUNK_BYTES)
        self.assertLessEqual(agreement["chunkCount"], MAX_CHUNKS)
        self.assertLessEqual(agreement["chunkSize"] * agreement["chunkCount"], MAX_IMAGE_BYTES)

    def test_end_stream_contract(self) -> None:
        payload = load_json(TESTDATA_ROOT / "end_stream.json")
        self.assertEqual({"cameraStream": None}, payload)

    def test_control_commands_contract(self) -> None:
        self.assertEqual({"startVideo": 5}, load_json(TESTDATA_ROOT / "start_video.json"))
        self.assertEqual({"stopVideo": ""}, load_json(TESTDATA_ROOT / "stop_video.json"))

    def test_sketch_negotiates_the_protocol_header(self) -> None:
        content = SKETCH.read_text(encoding="utf-8")
        self.assertIn("X-Offbeat-Camera-Stream: chunked-v1", content)

    def test_sketch_sends_an_agreement_and_frames_chunks(self) -> None:
        sketch = SKETCH.read_text(encoding="utf-8")
        support = (
            REPO_ROOT / "src" / "offbeat" / "camera" / "CameraChunkedStreamExampleSupport.h"
        ).read_text(encoding="utf-8")

        # The agreement must carry both fields the server validates.
        self.assertIn('\\"chunkSize\\"', support)
        self.assertIn('\\"chunkCount\\"', support)
        self.assertIn("buildAgreement", sketch)
        # The loop has to run between writes, otherwise a stopVideo that arrives mid-image is
        # only read after the whole frame was pushed.
        self.assertIn("webSocket.loop();", sketch)
        self.assertIn("webSocket.sendBIN(frame->buf + offset, length)", sketch)

    def test_sketch_exposes_docs_tags(self) -> None:
        content = SKETCH.read_text(encoding="utf-8")
        self.assertIn("// tag::camera-chunked-stream-docs[]", content)
        self.assertIn("// end::camera-chunked-stream-docs[]", content)

    def test_config_example_keeps_placeholder_credentials(self) -> None:
        content = (REPO_ROOT / "examples" / "camera" / "offbeat_test_config.h.example").read_text(
            encoding="utf-8"
        )
        self.assertIn('"replace-me"', content)
        self.assertNotIn("www.offbeat-iot.com", content)


if __name__ == "__main__":
    unittest.main()
