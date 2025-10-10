[![Discord](https://img.shields.io/discord/379876792003067906?label=discord&logo=discord)](https://discord.gg/pfgT2Kz)

### Dependencies
| component / version                                                         | minimum <br>(not recommended but may work) | recommended    | most recent of what we have ever tested |
|-----------------------------------------------------------------------------|--------------------------------------------|----------------|-----------------------------------------|
| gcc (Linux)                                                                 | 8.4.0                                      | 9.4.0          | 12.3.0                                  |
| llvm/clang (Linux)                                                          | UNKNOWN                                    | 7.0.1          | 8.0.0                                   |
| [MSVC](https://visualstudio.microsoft.com/downloads/) (Windows)             | 2017 (15.9.30)                             | 2022 (17.11.5) | 2022 (17.12.3)                          |
| [XCode](https://developer.apple.com/downloads/) (macOS)                     | 12.3                                       | 14.3           | 15.2                                    |
| [CMake](https://cmake.org/download/)                                        | 3.26.3                                     | 3.26.3         | 3.31.6                                  |

## Cloning

Be sure to clone the repository properly, with `--recursive` flag, or you'll get angry:<br/>
`git clone --recursive https://github.com/letheanVPN/blockchain.git`

# Building

The project uses a `Makefile` that provides a simple and powerful interface for building.
It automatically handles dependency installation with Conan and compilation with CMake.

You need CMake and Make installed on your system, other than that you don't need to worry about Python, Conan, Boost, OpenSSL, or any other dependencies.

The final packages are created as they are due to a historical distribution method used in china: USB Stick, CD, DVD, etc.

We use CPack, so our pakages are self-contained, have searchable HTML documentation, and are ready to be installed on any system.

To skip the packing step, use `make build` as defined in the section below for Advanced Build Customization

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

## Creating Release Packages

To create distributable packages (e.g., `.zip`, `.msi`, `.pkg`, `.deb`), run the `release` target. This will build the project, build the documentation, and then package everything.

 ```shell
 make release TESTNET=1
 ```
The final packages will be located in the `build/packages/` directory

## Advanced Build Customization (Makefile Variables)

For advanced use cases, you can override variables in the `Makefile` to customize the build process.

*   **Build a `testnet` version:**
    ```shell
    make build TESTNET=1
    ```
*   **Build a statically-linked version:**
    ```shell
    make build STATIC=1
    ```
*   **Build a Debug build with 8 compile threads:**
    ```shell
    make build BUILD_TYPE=Debug CPU_CORES=8
    ```
*   **Use custom CMakePresets:**
    ```shell
    make build PRESET_CONFIGURE=my-config-preset PRESET_BUILD=my-build-preset
    ```

| Variable           | Description                                                            | Default Value           |
|--------------------|------------------------------------------------------------------------|-------------------------|
| `BUILD_TYPE`       | Sets the build configuration (e.g., `Release`, `Debug`).               | `Release`               |
| `TESTNET`          | Set to `1` to build for the test network.                              | `0`                     |
| `STATIC`           | Set to `1` to link libraries statically.                               | `0`                     |
| `CPU_CORES`        | Number of CPU cores to use for parallel compilation.                   | Auto-detected           |
| `BUILD_VERSION`    | The version string to embed in the binaries.                           | `6.0.1`                 |
| `BUILD_FOLDER`     | The output directory for the build.                                    | `build/release`         |
| `PRESET_CONFIGURE` | The CMake preset to use for the `configure` step.                      | `conan-release`         |
| `PRESET_BUILD`     | The CMake preset to use for the `build` step.                          | `conan-release`         |
| `CONAN_CACHE`      | The path for the local Conan cache, where the dependencies are stored. | `./build/sdk`           |
| `CONAN_EXECUTABLE` | The path to the usable Conan executable.                               | `./build/bin/conan`     |
| `CONAN_URL`        | The URL for the Conan remote repository.                               | `artifacts.host.uk.com` |
| `CONAN_USER`       | The username for the Conan remote.                                     | `public`                |
| `CONAN_PASSWORD`   | The password for the Conan remote.                                     |                         |

## Cleaning the Build Directory

ALWAYS USE `make clean` to clean the build directory, manually deleting the `build/release`, `build/SOME_FOLDER` will cause you issues.

Our `make clean` triggers a cmake script that completely resets the build directory &amp; dynamically added CMakePresets to its cached warm-up state,  
the selective clean script can be edited here: `cmake/CleanBuild.cmake` or directly run from the repo root `cmake -P cmake/CleanBuild.cmake`

You can NUKE the build directory with `make clean-build` which is `rm -rf build`.

If you do manually delete build folders and get CMake errors (if you have compiled anything previously, you will), 
the ConanPresets.json file has entries in the `include` property, delete them all and try again.

This happens because CMakePresets.json includes ConanPresets.json, that has the list of toolchains to use that gets populated during the CMake config step, 
when you manually delete a folder, the toolchain is now a broken path, and CMake throws a fatal error.