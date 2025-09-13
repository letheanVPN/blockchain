> **Note on Attribution and Contributions**
> 
> The MCP CMake server code contained in the `context/` directory is based on the excellent `mcp-cmake` project by [hiono](https://github.com/hiono).
> 
> Please consider starring the original repository to show your support!
> 
> *   **Upstream Project (EN)**: [https://github.com/hiono/mcp-cmake](https://github.com/hiono/mcp-cmake)
> *   **Upstream Project (JA)**: [https://github.com/hiono/mcp-cmake/blob/main/README_ja.md](https://github.com/hiono/mcp-cmake/blob/main/README_ja.md)
> 
> If you have improvements or bug fixes for the MCP server itself, please submit your pull requests to the upstream repository. Contributions to the integration files (`Dockerfile`, `docker-compose.yml`, etc.) are welcome here.

---

# MCP CMake Server Environment

This directory contains the necessary files to build and run a containerized MCP (Model Context Protocol) server for this CMake project. The server provides a programmatic interface to configure, build, and test the project, making it ideal for IDE integration and automated testing.

## 1. Overview

The goal of this setup is to provide a consistent and reproducible build environment using Docker. The MCP server runs inside the container and has access to the project's source code, allowing it to execute CMake commands based on the project's `CMakePresets.json` file.

## 2. Components

*   **`Dockerfile`**: This file defines the environment for the MCP server. It:
    *   Starts from a `python:3.12-slim-bookworm` base image.
    *   Installs all necessary system dependencies and build tools (e.g., `cmake`, `g++`, `libicu-dev`, `libssl-dev`) required to compile the blockchain project.
    *   Installs the `uv` Python package manager.
    *   Installs the MCP server's Python dependencies from `context/pyproject.toml`.
    *   Copies the MCP server source code from the `context/` directory.
    *   Sets the entrypoint to automatically start the MCP server.

*   **`docker-compose.yml`**: This file simplifies the process of building and running the Docker container. It defines a single service that:
    *   Builds the Docker image using the local `Dockerfile`.
    *   Tags the image as `lthn/mcp-cmake-server:latest`.
    *   Mounts the entire project root directory into the `/workspace` directory inside the container, giving the server access to the source code.

*   **`context/`**: This directory contains the source code for the `mcp-cmake` server itself.

## 3. Usage

To build and run the MCP server, navigate to this directory (`utils/mcp/cmake/`) and run the following command:

```sh
docker-compose up --build
```

This command will:
1.  Build the `lthn/mcp-cmake-server:latest` Docker image if it doesn't already exist.
2.  Start a container from that image.
3.  The MCP server will launch automatically inside the container and use `/workspace` (your project root) as its working directory.

## 4. IDE Integration (e.g., CLion)

Once the container is running, you can configure your IDE to connect to it. The server will log its URL and port to the console. It will look something like this:

```
🔗 Server URL:      http://0.0.0.0:36908/mcp
```

Take note of the port number (e.g., `36908`).

### 4.1. MCP JSON Configuration

To connect, your IDE needs an MCP configuration file. Create a new file (e.g., `mcp-client.json`) and add the following content. **Remember to replace `PORT` with the actual port number from the server log.**

```json
{
  "mcpServers": {
    "cmake": {
      "command": "npx",
      "args": ["mcp-remote", "http://127.0.0.1:36908/mcp"]
    }
  }
}
```

For example, if the server is running on port `36908`, the file would be:

```json
{
  "servers": [
    {
      "name": "Lethean CMake MCP Server",
      "type": "mcp",
      "url": "http://127.0.0.1:36908/mcp"
    }
  ]
}
```

In your IDE's settings, add a new MCP connection and point it to this JSON file. This will resolve the `400 Bad Request` error by ensuring the IDE communicates using the correct protocol.

## 5. Performing Builds

Once connected, the client can issue commands to build the project using any of the presets defined in the root `CMakePresets.json` file.

### 5.1. Standard Release Build

To perform a standard release build, the client would call the `build_project` tool with the `release` preset.

**Example Client Call:**
```python
# Assuming 'client' is an MCP client connected to the server
client.call_tool("build_project", {"preset": "release"})
```

### 5.2. Testnet Build

To build the project for the testnet, use the `release-testnet` preset. This preset inherits its configuration from the `release` preset but sets the `TESTNET` variable to `ON`.

**Example Client Call:**
```python
# Assuming 'client' is an MCP client connected to the server
client.call_tool("build_project", {"preset": "release-testnet"})
```
