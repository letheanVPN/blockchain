# cmake/CleanBuild.cmake

# Function to selectively clean the build directory.
#
# This function will remove most of the generated build files from the build
# directory, while preserving specific directories that contain downloaded
# tools or generated documentation.
#
# Golden Rules:
# - never delete build/
# - never delete build/bin
# - never delete build/docs
# - never delete build/sdk (non cache)
#
# It will:
# - purge build files
# - clean up conan build files, cached sources can always remain.
function(selective_clean_build_dir)
    if(EXISTS "${CMAKE_SOURCE_DIR}/build")
        message(STATUS "Selectively cleaning build directory: ${CMAKE_SOURCE_DIR}/build")

        # List of top-level items in the build directory to keep.
        set(golden_items
            "${CMAKE_SOURCE_DIR}/build/.ccache"
            "${CMAKE_SOURCE_DIR}/build/bin"
            "${CMAKE_SOURCE_DIR}/build/docs"
            "${CMAKE_SOURCE_DIR}/build/sdk"
        )

        # Get all top-level items in the build directory.
        file(GLOB top_level_items "${CMAKE_SOURCE_DIR}/build/*")

        foreach(item ${top_level_items})
            list(FIND golden_items "${item}" is_golden)
            if(is_golden STREQUAL "-1")
                string(FIND "${item}" "${CMAKE_SOURCE_DIR}/build" is_prefixed)
                if(is_prefixed EQUAL 0)
                    message(STATUS "Removing: ${item}")
                    if(IS_DIRECTORY "${item}")
                        file(REMOVE_RECURSE "${item}")
                    else()
                        file(REMOVE "${item}")
                    endif()
                else()
                    message(WARNING "Safety check failed: Will not remove '${item}' because it is not prefixed with CMAKE_SOURCE_DIR/build.")
                endif()
            else()
                message(STATUS "Keeping golden item: ${item}")
            endif()
        endforeach()

        message(STATUS "Selective clean complete.")
    else()
        message(STATUS "Build directory not found, skipping clean.")
    endif()
endfunction()

selective_clean_build_dir()
