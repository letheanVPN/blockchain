# Set modern CMake policies for the project.
# With a minimum required version of 3.26.3, most if() guards are redundant.

cmake_policy(SET CMP0043 NEW) # Ignore CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES
cmake_policy(SET CMP0074 NEW) # find_package uses <PackageName>_ROOT variables.
cmake_policy(SET CMP0135 NEW) # ExternalProject_Add DOWNLOAD_EXTRACT_TIMESTAMP
cmake_policy(SET CMP0144 NEW) # find_package uses reading <PackageName>_ROOT from cache.

# CMP0167 was introduced in CMake 3.27, so we need to guard it.
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()
