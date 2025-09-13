# C:/Users/snide/CLionProjects/snider/blockchain/cmake/clean_except.cmake
#
# Removes all files and directories in a given directory, except for one
# named item. This is a cross-platform replacement for a command like:
# `find <dir> -mindepth 1 -maxdepth 1 -not -name <name> -exec rm -rf {} +`
#
# Usage:
#   cmake -D CLEAN_DIR=<path> -D PRESERVE_NAME=<name> -P clean_except.cmake

if(NOT DEFINED CLEAN_DIR OR NOT EXISTS "${CLEAN_DIR}")
  message(FATAL_ERROR "CLEAN_DIR variable must be set to an existing directory.")
endif()

if(NOT DEFINED PRESERVE_NAME)
  message(FATAL_ERROR "PRESERVE_NAME variable must be set.")
endif()

file(GLOB CHILDREN LIST_DIRECTORIES true "${CLEAN_DIR}/*")

foreach(CHILD ${CHILDREN})
  get_filename_component(CHILD_NAME "${CHILD}" NAME)
  if(NOT "${CHILD_NAME}" STREQUAL "${PRESERVE_NAME}")
    message(STATUS "Removing: ${CHILD}")
    file(REMOVE_RECURSE "${CHILD}")
  endif()
endforeach()