include(${CMAKE_SOURCE_DIR}/cmake/config-vars.cmake)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CPACK_PACKAGE_NAME "${package_name}")
    set(CPACK_PACKAGE_VENDOR "${package_vendor}")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${package_description}")
    set(CPACK_PACKAGE_VERSION "${package_version}")
    set(CPACK_PACKAGE_CONTACT "${package_contact}")
    set(CPACK_PACKAGE_HOMEPAGE_URL "${package_website}")

#    set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")   # Linux/macOS default
#    if(WIN32)
#        set(CPACK_PACKAGING_INSTALL_PREFIX "C:/Program Files/${PROJECT_NAME}")
#    endif()

    if(APPLE)
        if("${package_macos_installer}" STREQUAL "DMG")
            set(CPACK_GENERATOR "DragNDrop")
#            set(CPACK_DMG_BACKGROUND_IMAGE "${CMAKE_SOURCE_DIR}/resources/dmg_background.png")
            set(CPACK_DMG_VOLUME_NAME "${CPACK_PACKAGE_NAME} ${CPACK_PACKAGE_VERSION}")
            message("Registered CPACK_GENERATOR: DragNDrop")
        else ()
            set(CPACK_GENERATOR "productbuild")
            set(CPACK_PRODUCTBUILD_IDENTIFIER "${package_macos_pkg_productbuild_identifier}")
#            set(CPACK_PRODUCTBUILD_SIGNING_IDENTITY "Developer ID Installer: Your Company (TEAMID)")
            message("Registered CPACK_GENERATOR: productbuild")
        endif ()
    elseif(WIN32)
        set(CPACK_GENERATOR "WIX")
        message("Registered CPACK_GENERATOR: WIX")
#        set(CPACK_WIX_PRODUCT_ICON "${CMAKE_SOURCE_DIR}/resources/windows_icon.ico")
#        set(CPACK_WIX_LICENSE_RTF "${CMAKE_SOURCE_DIR}/LICENSE.rtf")
#        set(CPACK_WIX_UPGRADE_GUID "D3F5A9C1-4B2E-4F5A-9C71-123456789ABC") # change once per major version
    else()
        set(CPACK_GENERATOR "DEB")
        message("Registered CPACK_GENERATOR: deb")
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${package_contact}")
        set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.28)")
        set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
        set(CPACK_DEBIAN_ARCHITECTURE "${CMAKE_SYSTEM_PROCESSOR}")
        # post‑install script (e.g., to register a systemd service)
#        set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
#                "${CMAKE_SOURCE_DIR}/scripts/postinstall.sh")
    endif()

    list(APPEND CPACK_GENERATOR "TXZ" "ZIP")
    message( "Registered CPACK_GENERATOR: tgz")
    message( "Registered CPACK_GENERATOR: zip")
    set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
    set(CPACK_ARCHIVE_COMPONENT_INSTALL OFF)
    set(CPACK_COMPONENTS_ALL)
    set(CPACK_GENERATE_SHASUM ON)
    set(CPACK_SHASUM_ALGORITHM SHA256)
    message( "Using SHA256 Checksums")

    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")
#    set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

    set(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/packages")

    install(FILES README.md LICENSE.txt
            DESTINATION .
    )

    set(_arch "${CMAKE_SYSTEM_PROCESSOR}")

    if(_arch MATCHES "AMD64|x86_64")
        set(_arch "x86_64")
    elseif(_arch MATCHES "arm64|aarch64")
        set(_arch "arm64")
    endif()

    string(TOLOWER "${CMAKE_SYSTEM_NAME}" _sys_name_lc)

    set(CPACK_PACKAGE_FILE_NAME
            "${package_name}-${CPACK_PACKAGE_VERSION}-${_sys_name_lc}-${_arch}")

    include(CPack)
endif()