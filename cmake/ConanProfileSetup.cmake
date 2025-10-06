# Use the CONAN_HOME from the environment, or default to a local directory.
if(NOT DEFINED ENV{CONAN_HOME})
    set(CONAN_HOME "${CMAKE_SOURCE_DIR}/build/sdk")
    message(STATUS "CONAN_HOME not set, defaulting to: ${CONAN_HOME}")
else()
    set(CONAN_HOME "$ENV{CONAN_HOME}")
endif()

set(DEFAULT_PROFILE "${CONAN_HOME}/profiles/default")


if(NOT EXISTS "${DEFAULT_PROFILE}")
    message(STATUS "Conan default profile not found. Detecting a new one...")
    set(ENV{CONAN_HOME} "${CONAN_HOME}")
    execute_process(
            COMMAND "${CMAKE_SOURCE_DIR}/build/bin/conan" profile detect --name=default --force
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            RESULT_VARIABLE return_code
    )
    unset(ENV{CONAN_HOME})

    if(NOT return_code EQUAL 0)
        message(FATAL_ERROR "Conan profile detection failed with exit code: ${return_code}")
    endif()
endif()

message(STATUS "Appending custom settings to Conan default profile...")

set(CUSTOM_SETTINGS "
compiler.cppstd=17
")

if(WIN32)
    message(STATUS "Windows detected. Appending static runtime setting.")
    string(APPEND CUSTOM_SETTINGS "
compiler.runtime=static
")
endif()

file(APPEND "${DEFAULT_PROFILE}" "${CUSTOM_SETTINGS}")

message(STATUS "Conan profile setup is complete.")