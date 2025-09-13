# mcp_cmake/core.py

import json
import os
import shutil
import subprocess
import sys
from typing import Any, Dict, List, Optional

from .models import ErrorDetail, FailureResponse, SuccessResponse


def health_check(working_dir: Optional[str] = None) -> Dict[str, Any]:
    """
    Checks the development environment's health.
    """
    if not working_dir or not os.path.isdir(working_dir):
        return {
            "working_directory": working_dir,
            "is_healthy": False,
            "error": "Working directory not set or does not exist.",
        }

    working_dir = os.path.abspath(working_dir)

    def find_executable(name):
        path = shutil.which(name)
        return {"found": bool(path), "path": path}

    cmakepresets_path = os.path.join(working_dir, "CMakePresets.json")

    checks = {
        "cmake_executable": find_executable("cmake"),
        "ctest_executable": find_executable("ctest"),
        "cmakepresets_file": {
            "found": os.path.isfile(cmakepresets_path),
            "path": cmakepresets_path,
        },
        "preset_consistency": {"passed": False, "details": "Check not implemented."},
    }

    all_checks_passed = all(check["found"] for name, check in checks.items() if name != "preset_consistency")

    # For now, preset_consistency is not a blocking check.
    # This can be implemented later.
    if all_checks_passed:
        checks["preset_consistency"]["passed"] = True
        checks["preset_consistency"]["details"] = "Consistency check passed (placeholder)."

    return {
        "working_directory": working_dir,
        "is_healthy": all_checks_passed,
        "checks": checks,
    }


def list_presets(working_dir: str) -> List[str]:
    """
    Lists available configure presets from CMakePresets.json.
    """
    presets_file = os.path.join(working_dir, "CMakePresets.json")
    if not os.path.exists(presets_file):
        return []

    with open(presets_file, "r") as f:
        try:
            data = json.load(f)
            return [preset["name"] for preset in data.get("configurePresets", [])]
        except (json.JSONDecodeError, KeyError):
            return []


def create_project(working_dir: str, preset: str, cmake_defines: Optional[Dict[str, str]] = None) -> Dict[str, Any]:
    """
    Configures the CMake project.
    """
    try:
        # 1. Initial configure to determine compiler
        build_dir = os.path.join(working_dir, "build", preset)
        if not os.path.exists(build_dir):
            os.makedirs(build_dir)

        initial_cmd = ["cmake", "-S", working_dir, "-B", build_dir, f"--preset={preset}"]
        subprocess.run(initial_cmd, check=True, cwd=working_dir, capture_output=True, text=True)

        # 2. Read compiler ID from CMakeCache.txt
        cache_file = os.path.join(build_dir, "CMakeCache.txt")
        compiler_id = None
        with open(cache_file, "r") as f:
            for line in f:
                if line.startswith("CMAKE_CXX_COMPILER_ID"):
                    compiler_id = line.split("=")[1].strip()
                    break

        if not compiler_id:
            return FailureResponse(summary="Could not determine compiler ID.").dict()

        # 3. Set flags for structured diagnostics
        diag_flags = ""
        if compiler_id in ["GNU", "Clang"]:
            diag_flags = "-fdiagnostics-format=json"
        elif compiler_id == "MSVC":
            diag_flags = "/diagnostics:sarif"

        # 4. Final configure with diagnostic flags
        final_cmd = ["cmake", "-S", working_dir, "-B", build_dir, f"--preset={preset}"]
        if diag_flags:
            final_cmd.append(f"-DCMAKE_CXX_FLAGS_INIT={diag_flags}")

        if cmake_defines:
            for key, value in cmake_defines.items():
                final_cmd.append(f"-D{key}={value}")

        result = subprocess.run(final_cmd, check=True, cwd=working_dir, capture_output=True, text=True)

        if result.returncode == 0:
            return SuccessResponse().dict()
        else:
            return FailureResponse(
                summary="CMake configuration failed.", errors=[ErrorDetail(message=result.stderr, severity="error")]
            ).dict()

    except (subprocess.CalledProcessError, FileNotFoundError) as e:
        error_message = e.stderr if isinstance(e, subprocess.CalledProcessError) else str(e)
        return FailureResponse(
            summary="CMake configuration failed.", errors=[ErrorDetail(message=error_message, severity="error")]
        ).dict()


def build_project(
    working_dir: str,
    preset: str,
    targets: Optional[List[str]] = None,
    verbose: bool = False,
    parallel_jobs: Optional[int] = None,
) -> Dict[str, Any]:
    """
    Builds the project.
    """
    try:
        build_dir = os.path.join(working_dir, "build", preset)
        cmd = ["cmake", "--build", build_dir, f"--preset={preset}"]
        if targets:
            cmd.extend(["--target", *targets])
        if verbose:
            cmd.append("--verbose")
        if parallel_jobs:
            cmd.extend(["--parallel", str(parallel_jobs)])

        result = subprocess.run(cmd, cwd=working_dir, capture_output=True, text=True)

        if result.returncode == 0:
            return SuccessResponse().dict()
        else:
            # Determine compiler to know the error format
            cache_file = os.path.join(build_dir, "CMakeCache.txt")
            compiler_id = "Unknown"
            with open(cache_file, "r") as f:
                for line in f:
                    if line.startswith("CMAKE_CXX_COMPILER_ID"):
                        compiler_id = line.split("=")[1].strip()
                        break

            error_format = "raw"
            if compiler_id in ["GNU", "Clang"]:
                error_format = "json"
            elif compiler_id == "MSVC":
                error_format = "sarif"

            formatted_error = format_error_for_llm_analysis(result.stderr, error_format)
            return FailureResponse(**formatted_error).dict()

    except (subprocess.CalledProcessError, FileNotFoundError) as e:
        error_message = e.stderr if isinstance(e, subprocess.CalledProcessError) else str(e)
        return FailureResponse(summary="Build failed.", errors=[ErrorDetail(message=error_message, severity="error")]).dict()


def test_project(
    working_dir: str,
    preset: str,
    test_filter: Optional[str] = None,
    verbose: bool = False,
    parallel_jobs: Optional[int] = None,
) -> Dict[str, Any]:
    """
    Runs tests for the project.
    """
    try:
        build_dir = os.path.join(working_dir, "build", preset)
        cmd = ["ctest", f"--preset={preset}"]
        if test_filter:
            cmd.extend(["-R", test_filter])
        if verbose:
            cmd.append("--verbose")
        if parallel_jobs:
            cmd.extend(["-j", str(parallel_jobs)])

        result = subprocess.run(cmd, cwd=build_dir, capture_output=True, text=True)

        if result.returncode == 0:
            return SuccessResponse(message="All tests passed.").dict()
        else:
            # CTest output is not structured, so we treat it as raw text.
            return FailureResponse(
                summary="Tests failed.", errors=[ErrorDetail(message=result.stdout + result.stderr, severity="error")]
            ).dict()

    except (subprocess.CalledProcessError, FileNotFoundError) as e:
        error_message = e.stderr if isinstance(e, subprocess.CalledProcessError) else str(e)
        return FailureResponse(
            summary="Test execution failed.", errors=[ErrorDetail(message=error_message, severity="error")]
        ).dict()
