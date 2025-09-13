# MCP-CMake: A Tool for CMake Project Management

[日本語のドキュメントはこちら (View in Japanese)](./README_ja.md)

MCP-CMake provides a set of tools to manage CMake-based projects through the Model Context Protocol (MCP). It allows you to configure, build, and test your CMake projects programmatically.

## 🚀 Getting Started

### Server Setup

The MCP-CMake server needs to be started with a path to your CMake project's root directory. This directory must contain a `CMakePresets.json` file.

```bash
python3 -m mcp_cmake.server -w /Users/snider/Code/snider/blockchain
```

Once the server starts, it performs an initial health check. If successful, the server becomes `Healthy` and is ready to accept tool calls.

### Server State

The server maintains two internal states:
-   `WORKING_DIRECTORY`: The absolute path to the CMake project being managed.
-   `IS_HEALTHY`: A boolean flag indicating if the server is ready. This must be `true` for most tools to work.

## 🛠️ Available Tools

### 1. `health_check`

Verifies the development environment and sets the server to a `Healthy` state if successful. This tool can also be used to switch the working directory to a new project.

-   **Arguments:**
    -   `working_dir` (Optional[str]): The absolute path to a CMake project directory. If provided, the server will switch to this directory.
-   **Returns:** A dictionary containing the check results.

**Example:**
```python
# Run a health check on the current working directory
client.call_tool("health_check")

# Switch to a new project and check its health
client.call_tool("health_check", {"working_dir": "/path/to/another/project"})
```

### 2. `list_presets`

Lists the available `configurePresets` from the `CMakePresets.json` file in the current working directory.

-   **Arguments:** None
-   **Returns:** A list of preset name strings.

**Example:**
```python
presets = client.call_tool("list_presets")
print(presets.text)
# Output: ['default', 'ninja-multi-config', 'windows-msvc']
```

### 3. `create_project`

Configures the CMake project using a specified preset. This tool automatically detects the compiler and enables structured diagnostic logging (JSON for GCC/Clang, SARIF for MSVC).

-   **Arguments:**
    -   `preset` (str): The name of the configure preset to use.
    -   `cmake_defines` (Optional[dict]): A dictionary of CMake defines to pass with the `-D` flag (e.g., `{"MY_VAR": "VALUE"}`).
-   **Returns:** A success or failure response.

**Example:**
```python
client.call_tool("create_project", {"preset": "default"})
```

### 4. `build_project`

Builds the project using a specified build preset. If the build fails, it returns a structured error report parsed from the compiler's output.

-   **Arguments:**
    -   `preset` (str): The name of the build preset to use.
    -   `targets` (Optional[list[str]]): A list of specific targets to build.
    -   `verbose` (Optional[bool]): If `True`, enables verbose build output.
    -   `parallel_jobs` (Optional[int]): The number of parallel jobs to use for building.
-   **Returns:** A success or failure response with detailed error information.

**Example:**
```python
# Build the default target
client.call_tool("build_project", {"preset": "default"})

# Build a specific target with 4 parallel jobs
client.call_tool("build_project", {"preset": "default", "targets": ["my_executable"], "parallel_jobs": 4})
```

### 5. `test_project`

Runs tests for the project using a specified test preset.

-   **Arguments:**
    -   `preset` (str): The name of the test preset to use.
    -   `test_filter` (Optional[str]): A regex to filter which tests to run.
    -   `verbose` (Optional[bool]): If `True`, enables verbose test output.
    -   `parallel_jobs` (Optional[int]): The number of parallel tests to run.
-   **Returns:** A success or failure response.

**Example:**
```python
# Run all tests
client.call_tool("test_project", {"preset": "default"})

# Run tests matching a specific name
client.call_tool("test_project", {"preset": "default", "test_filter": "MyTest*"})
```
