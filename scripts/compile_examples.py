from __future__ import annotations

import argparse
from pathlib import Path
import shutil
import subprocess
import sys


REQUIRED_LIBRARIES = (
    "ArduinoJson",
    "WebSockets",
)

MANUAL_LIBRARY_REPOS = {
    "ArduinoCbor": "https://github.com/bergos/ArduinoCbor.git",
}

ESP8266_PACKAGE_INDEX = "https://arduino.esp8266.com/stable/package_esp8266com_index.json"


def run(command: list[str], cwd: Path) -> None:
    print("$", " ".join(command))
    completed = subprocess.run(command, cwd=cwd, text=True, check=False)
    if completed.returncode != 0:
        raise RuntimeError(f"Command failed: {' '.join(command)}")


def find_sketch_directories(repo_root: Path) -> list[Path]:
    return sorted({path.parent for path in repo_root.glob("examples/*/*/*.ino")})


def ensure_local_config_headers(sketch_directories: list[Path]) -> list[Path]:
    created_headers: list[Path] = []
    for sketch_directory in sketch_directories:
        local_header = sketch_directory / "offbeat_test_config.h"
        if local_header.exists():
            continue

        example_header = sketch_directory / "offbeat_test_config.h.example"
        if not example_header.exists():
            provider_header = sketch_directory.parent / "offbeat_test_config.h.example"
            if provider_header.exists():
                example_header = provider_header
            else:
                continue

        shutil.copyfile(example_header, local_header)
        created_headers.append(local_header)
    return created_headers


def cleanup_generated_config_headers(headers: list[Path]) -> None:
    for header in headers:
        if header.exists():
            header.unlink()


def patch_arduino_cbor_for_esp8266(libraries_directory: Path) -> None:
    cbor_variant = libraries_directory / "ArduinoCbor" / "src" / "CborVariant.cpp"
    if not cbor_variant.exists():
        return

    content = cbor_variant.read_text(encoding="utf-8")
    if "#include <math.h>" in content:
        return

    lines = content.splitlines()
    insert_at = 0
    while insert_at < len(lines) and lines[insert_at].startswith("#include"):
        insert_at += 1
    lines.insert(insert_at, "#include <math.h>")
    cbor_variant.write_text("\n".join(lines) + "\n", encoding="utf-8")


def ensure_arduino_cli_available() -> None:
    if shutil.which("arduino-cli") is None:
        raise RuntimeError("arduino-cli is not available on PATH")


def additional_urls(fqbn: str) -> list[str]:
    if fqbn.startswith("esp8266:"):
        return ["--additional-urls", ESP8266_PACKAGE_INDEX]
    return []


def ensure_core_installed(repo_root: Path, fqbn: str) -> None:
    platform_name = ":".join(fqbn.split(":")[:2])
    run(["arduino-cli", "core", "update-index", *additional_urls(fqbn)], cwd=repo_root)

    completed = subprocess.run(
        ["arduino-cli", "core", "list"],
        cwd=repo_root,
        text=True,
        capture_output=True,
        check=False,
    )
    if platform_name in completed.stdout:
        return

    run(
        ["arduino-cli", "core", "install", *additional_urls(fqbn), platform_name],
        cwd=repo_root,
    )


def ensure_library_installed(repo_root: Path, library_name: str) -> None:
    completed = subprocess.run(
        ["arduino-cli", "lib", "list"],
        cwd=repo_root,
        text=True,
        capture_output=True,
        check=False,
    )
    if library_name in completed.stdout:
        return

    run(["arduino-cli", "lib", "install", library_name], cwd=repo_root)


def ensure_libraries_installed(repo_root: Path) -> Path:
    run(["arduino-cli", "lib", "update-index"], cwd=repo_root)
    for library_name in REQUIRED_LIBRARIES:
        ensure_library_installed(repo_root, library_name)

    libraries_directory = repo_root / ".arduino-libraries"
    libraries_directory.mkdir(parents=True, exist_ok=True)
    for library_name, repository in MANUAL_LIBRARY_REPOS.items():
        destination = libraries_directory / library_name
        if destination.exists():
            continue
        run(["git", "clone", "--depth", "1", repository, str(destination)], cwd=repo_root)

    patch_arduino_cbor_for_esp8266(libraries_directory)
    return libraries_directory


def compile_sketches(repo_root: Path, fqbn: str) -> None:
    sketch_directories = find_sketch_directories(repo_root)
    if not sketch_directories:
        raise RuntimeError("No sketches found in examples/")

    ensure_arduino_cli_available()
    ensure_core_installed(repo_root, fqbn)
    libraries_directory = ensure_libraries_installed(repo_root)

    generated_headers = ensure_local_config_headers(sketch_directories)
    try:
        for sketch_directory in sketch_directories:
            relative_directory = sketch_directory.relative_to(repo_root)
            build_directory = repo_root / ".build" / relative_directory
            if build_directory.exists():
                shutil.rmtree(build_directory)
            run(
                [
                    "arduino-cli",
                    "compile",
                    "--fqbn",
                    fqbn,
                    "--build-path",
                    str(build_directory),
                    "--libraries",
                    str(repo_root),
                    "--libraries",
                    str(libraries_directory),
                    str(sketch_directory),
                ],
                cwd=repo_root,
            )
    finally:
        cleanup_generated_config_headers(generated_headers)


def parse_args(argv: list[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Compile every Arduino example in this repository.")
    parser.add_argument(
        "--fqbn",
        default="esp8266:esp8266:nodemcuv2",
        help="Arduino board FQBN to compile against.",
    )
    parser.add_argument(
        "--repo-root",
        default=Path(__file__).resolve().parents[1],
        type=Path,
        help="Repository root. Defaults to the current checkout.",
    )
    return parser.parse_args(argv)


def main(argv: list[str] | None = None) -> int:
    arguments = parse_args(argv or sys.argv[1:])
    compile_sketches(arguments.repo_root.resolve(), arguments.fqbn)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
