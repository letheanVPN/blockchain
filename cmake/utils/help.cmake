# C:/Users/snide/CLionProjects/snider/blockchain/cmake/help.cmake
#
# Parses the Makefile to generate a help message.
# A cross-platform replacement for the echo/awk-based help target.

message("Lethean Blockchain - Build System")
message("")
message("Usage:  make <target> [OPTIONS...]")
message("")
message("Core Targets:")

file(STRINGS "Makefile" makefile_lines)

foreach(line ${makefile_lines})
    if(line MATCHES "^([a-zA-Z0-9_-]+):[^#]*## (.*)")
        set(target ${CMAKE_MATCH_1})
        set(comment ${CMAKE_MATCH_2})
        if(NOT comment MATCHES "@hidden")
            # Manual padding for legacy CMake compatibility. This avoids using
            # `string(FORMAT ...)` which is unsupported in older versions of
            # CMake that may be incorrectly invoked by buggy `make`
            # implementations on Windows when paths contain spaces.
            string(LENGTH "${target}" target_len)
            math(EXPR pad_len "21 - ${target_len}")
            if(${pad_len} LESS 1)
                set(pad_len 1)
            endif()

            set(padding_template "                         ") # 25 spaces
            string(SUBSTRING "${padding_template}" 0 ${pad_len} padding)
            message("  ${target}${padding}${comment}")
        endif()
    endif()
endforeach()

message("")
message("Options:")
message("  BUILD_TYPE=<type>    Specify build type (e.g., Debug, Release). Default: ${BUILD_TYPE}")
message("  BUILD_GUI=<ON/OFF>   Enable or disable GUI build. Default: ${BUILD_GUI}")
message("  STATIC_BUILD=<ON/OFF> Enable or disable static build. Default: ${STATIC_BUILD}")
message("  BUILD_TESTS=<ON/OFF> Enable or disable building tests. Default: ${BUILD_TESTS}")
message("  TESTNET=<ON/OFF>     Build for testnet. Default: ${TESTNET}")
message("  DISABLE_TOR=<ON/OFF> Build without TOR support. Default: ${DISABLE_TOR}")
message("")
message("For more information:")
message("  Documentation: https://lt.hn")
message("  Discord:       https://discord.lethean.io")
message("  GitHub:        https://github.com/letheanVPN")