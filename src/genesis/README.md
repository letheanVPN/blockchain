# Genesis Block Update Instructions

This document outlines the steps to trigger a genesis block update. The following instructions are based on the provided Makefile snippet.

## Prerequisites

*   CMake
*   Make

## Steps

1.  **Generate Premine Wallet (Optional):**

    This step generates a premine wallet. It sets the `GENERATE_PREMINE_WALLET` CMake option to `1` and the `PREMINE_WALLET_PASSWORD` to `12345678`.

    ```bash
    cmake <cmake_release> <testnet> -DGENERATE_PREMINE_WALLET=1 -DPREMINE_WALLET_PASSWORD=12345678
    cmake --build ./src --target premine_wallet
    ```

2.  **Generate Fresh Genesis Block:**

    This step generates a fresh genesis block. It sets the `GENERATE_FRESH_GENESIS` CMake option to `1`.

    ```bash
    cmake <cmake_release> <testnet> -DGENERATE_FRESH_GENESIS=1
    cmake --build ./src --target genesis_generator
    ```

3.  **Build the Project:**

    This step builds the entire project.

    ```bash
    cmake <cmake_release> <testnet>
    make
    ```

## Notes

*   Replace `<cmake_release>` and `<testnet>` with the actual values used in your environment. These are likely variables defined elsewhere in the Makefile.
*   The `|| true` at the end of the `premine_wallet` build command ensures that the script continues even if the build fails.
*   This process assumes that the `CMAKE` macro and other variables like `dir_release` are properly defined in the Makefile.
*   The exact impact of these steps on the genesis block update depends on the codebase. Consult the source code for more details.
