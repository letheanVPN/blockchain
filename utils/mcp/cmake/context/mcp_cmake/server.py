# mcp_cmake/server.py
import argparse
import os
from functools import wraps
from typing import List, Optional, Union

from fastmcp import Context, FastMCP

from . import core
from .models import FailureResponse

# Initialize the FastMCP server
mcp = FastMCP(
    "mcp-cmake-server",
    instructions="""
        First, run `health_check` to ensure CMake is available and to set the project's root directory.
        If the health check is successful, use `list_presets` to see the available CMake configuration presets.
        To configure the project, call `create_project` with one of the available presets.
        After configuration, you can build specific targets using `build_project`.
        Finally, run tests with `test_project`.
        If you encounter issues, re-run `health_check` with the correct working directory.
""",
    include_fastmcp_meta=True,
)

# --- Server State ---
WORKING_DIRECTORY: Optional[str] = None
IS_HEALTHY: bool = False


def update_state(healthy: bool, working_dir: Optional[str] = None):
    """Updates the server's health and working directory."""
    global IS_HEALTHY, WORKING_DIRECTORY
    IS_HEALTHY = healthy
    if working_dir:
        WORKING_DIRECTORY = working_dir


# --- Decorators ---
def require_healthy_state(func):
    """
    A decorator that ensures the server is in a healthy state before executing a tool.
    If the server is not healthy, it returns a standardized error response.
    """

    @wraps(func)
    def wrapper(ctx: Context, *args, **kwargs):
        if not IS_HEALTHY:
            return FailureResponse(
                summary="Server is not in a healthy state.",
            )
        return func(ctx, *args, **kwargs)

    return wrapper


# Add a GET handler to satisfy client health checks (like from CLion)
@mcp.custom_route("/mcp", methods=["GET"])
def health_check_get():
    """
    Handles GET requests to the /mcp endpoint, which are often sent by clients
    to check for server availability. Returns a simple status OK.
    """
    return {"status": "ok", "healthy": IS_HEALTHY}


@mcp.tool
def health_check(ctx: Context, working_dir: Optional[str] = None) -> dict:
    """
    Checks the development environment's health, updates server state, and
    optionally sets a new working directory. This is the first command that should be run.
    """
    result = core.health_check(working_dir or WORKING_DIRECTORY)
    update_state(result.get("is_healthy", False), result.get("working_directory"))
    return result


@mcp.tool
@require_healthy_state
def list_presets(ctx: Context) -> Union[list[str], dict]:
    """Lists available configure presets."""
    return core.list_presets(WORKING_DIRECTORY)


@mcp.tool
@require_healthy_state
def create_project(
    ctx: Context, preset: str, cmake_defines: Optional[dict] = None
) -> dict:
    """Configures the CMake project."""
    return core.create_project(WORKING_DIRECTORY, preset, cmake_defines)


@mcp.tool
@require_healthy_state
def build_project(
    ctx: Context,
    preset: str,
    targets: Optional[List[str]] = None,
    verbose: bool = False,
    parallel_jobs: Optional[int] = None,
) -> dict:
    """Builds the project."""
    return core.build_project(
        WORKING_DIRECTORY, preset, targets, verbose, parallel_jobs
    )


@mcp.tool
@require_healthy_state
def test_project(
    ctx: Context,
    preset: str,
    test_filter: Optional[str] = None,
    verbose: bool = False,
    parallel_jobs: Optional[int] = None,
) -> dict:
    """Runs tests for the project."""
    return core.test_project(
        WORKING_DIRECTORY, preset, test_filter, verbose, parallel_jobs
    )


def main():
    """
    Initializes and starts the McpServer, handling command-line arguments.
    """
    parser = argparse.ArgumentParser(description="MCP-CMake Server")
    parser.add_argument(
        "-w",
        "--working-dir",
        type=str,
        help="Set the initial CMake project working directory.",
    )
    # Add arguments for transport, but let FastMCP handle them
    parser.add_argument(
        "--stdio", action="store_true", help="Run with stdio transport (default)."
    )
    parser.add_argument("--http", action="store_true", help="Run with HTTP transport.")
    parser.add_argument(
        "--host", type=str, default="0.0.0.0", help="Host for HTTP transport."
    )
    parser.add_argument(
        "--port", type=int, default=8000, help="Port for HTTP transport."
    )

    args = parser.parse_args()

    # Set initial working directory from argument or use current directory
    initial_dir = os.path.abspath(args.working_dir) if args.working_dir else os.getcwd()
    print(f"Initializing with working directory: {initial_dir}")

    # Run initial health check
    result = core.health_check(initial_dir)
    update_state(result.get("is_healthy", False), result.get("working_directory"))
    print(f"Initial health check {'succeeded' if IS_HEALTHY else 'failed'}.")

    # FastMCP's run method can handle the transport arguments directly
    if args.http:
        mcp.run(transport="http", host=args.host, port=args.port)
    else:
        mcp.run(transport="stdio")


if __name__ == "__main__":
    main()
