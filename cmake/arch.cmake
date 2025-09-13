# This file contains platform-specific logic for setting architecture-related
# compiler and linker flags. It helps centralize architecture handling across the
# project.

if(APPLE)
    # On Apple platforms, the architecture must be defined before other modules
    # that might depend on it.
    if(NOT CMAKE_OSX_ARCHITECTURES)
        string(TOLOWER "${CMAKE_HOST_SYSTEM_PROCESSOR}" HOST_ARCH)
        if(HOST_ARCH STREQUAL "arm64")
            message(STATUS "Host is Apple Silicon, defaulting CMAKE_OSX_ARCHITECTURES to arm64 for compatibility.")
            set(CMAKE_OSX_ARCHITECTURES "arm64")
            set(CXX_EXTENSIONS OFF)
        else()
            message(STATUS "Defaulting CMAKE_OSX_ARCHITECTURES to ${HOST_ARCH}")
            set(CMAKE_OSX_ARCHITECTURES "${HOST_ARCH}")
        endif()
    endif()

    message(STATUS "[arch.cmake] CMAKE_OSX_ARCHITECTURES is set to: ${CMAKE_OSX_ARCHITECTURES}")

    # Explicitly pass the target architecture to the compiler and linker.
    # While CMAKE_OSX_ARCHITECTURES is the modern way, passing the flags
    # directly is more robust for some external projects.
#    set(ARCH_FLAG "-arch ${CMAKE_OSX_ARCHITECTURES}")
#    set(ARCH_C_FLAGS "${ARCH_FLAG}")
#    set(ARCH_CXX_FLAGS "${ARCH_FLAG}")
#    set(ARCH_LINKER_FLAGS "${ARCH_FLAG}")

elseif(NOT MSVC)
    # For non-MSVC builds (like GCC and Clang on Linux), allow specifying the
    # target architecture via the -march flag.
    set(ARCH default CACHE STRING "CPU to build for: -march value or default")
    if("${ARCH}" STREQUAL "default")
        set(ARCH_FLAG "")
    else()
        set(ARCH_FLAG "-march=${ARCH}")
    endif()
    set(ARCH_C_FLAGS "${ARCH_FLAG}")
    set(ARCH_CXX_FLAGS "${ARCH_FLAG}")
endif()
