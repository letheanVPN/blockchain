[![Discord](https://img.shields.io/discord/379876792003067906?label=discord&logo=discord)](https://discord.gg/pfgT2Kz)

### Dependencies
| component / version                                                                                 | minimum <br>(not recommended but may work) | recommended    | most recent of what we have ever tested |
|-----------------------------------------------------------------------------------------------------|--------------------------------------------|----------------|-----------------------------------------|
| gcc (Linux)                                                                                         | 8.4.0                                      | 9.4.0          | 12.3.0                                  |
| llvm/clang (Linux)                                                                                  | UNKNOWN                                    | 7.0.1          | 8.0.0                                   |
| [MSVC](https://visualstudio.microsoft.com/downloads/) (Windows)                                     | 2017 (15.9.30)                             | 2022 (17.11.5) | 2022 (17.12.3)                          |
| [XCode](https://developer.apple.com/downloads/) (macOS)                                             | 12.3                                       | 14.3           | 15.2                                    |
| [CMake](https://cmake.org/download/)                                                                | 3.26.3                                     | 3.26.3         | 3.31.6                                  |


## Cloning

Be sure to clone the repository properly, with `--recursive` flag, or you'll get angry:
`git clone --recursive https://github.com/letheanVPN/blockchain.git`

# Building
--------

The project uses a `Makefile` that provides a simple and powerful interface for building. It automatically handles dependency installation with Conan and compilation with CMake.

## Simple Workflow Builds (Recommended)

For most use cases, these two commands are all you need. They handle the entire build process from start to finish.

*   **Build for Mainnet:**
    ```shell
    make mainnet
    ```

*   **Build for Testnet:**
    ```shell
    make testnet
    ```

## Custom Builds

You can use the `make build` target with variables for more control over the final binaries.

*   **Build a `testnet` version:**
    ```shell
    make build TESTNET=1
    ```
*   **Build a statically-linked version:**
    ```shell
    make build STATIC=1
    ```

## Creating Release Packages

To create distributable packages (e.g., `.zip`, `.deb`), run the `release` target. This will build the project, build the documentation, and then package everything.

 ```shell
 make release
 ```
The final packages will be located in the `build/release/` directory

## Advanced Build Customization (Makefile Variables)

For advanced use cases, you can override variables in the `Makefile` to customize the build process.

Example:
```shell
make build BUILD_TYPE=Debug CPU_CORES=8
```

| Variable           | Description                                                            | Default Value                                                     |
|--------------------|------------------------------------------------------------------------|-------------------------------------------------------------------|
| `BUILD_TYPE`       | Sets the build configuration (e.g., `Release`, `Debug`).               | `Release`                                                         |
| `TESTNET`          | Set to `1` to build for the test network.                              | `0`                                                               |
| `STATIC`           | Set to `1` to link libraries statically.                               | `0`                                                               |
| `CPU_CORES`        | Number of CPU cores to use for parallel compilation.                   | Auto-detected                                                     |
| `BUILD_VERSION`    | The version string to embed in the binaries.                           | `6.0.1`                                                           |
| `BUILD_FOLDER`     | The output directory for the build.                                    | `build/release`                                                   |
| `PRESET_CONFIGURE` | The CMake preset to use for the `configure` step.                      | `conan-release`                                                   |
| `PRESET_BUILD`     | The CMake preset to use for the `build` step.                          | `conan-release`                                                   |
| `CONAN_CACHE`      | The path for the local Conan cache, where the dependencies are stored. | `./build/sdk`                                                     |
| `CONAN_EXECUTABLE` | The path to the usable Conan executable.                               | `./build/bin/conan`                                               |
| `CONAN_URL`        | The URL for the Conan remote repository.                               | `https://artifacts.host.uk.com/artifactory/api/conan/conan-build` |
| `CONAN_USER`       | The username for the Conan remote.                                     | `public`                                                          |
| `CONAN_PASSWORD`   | The password for the Conan remote.                                     |                                                                   |