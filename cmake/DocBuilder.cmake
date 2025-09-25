set(MKDOCS_SRC "${CMAKE_SOURCE_DIR}/docs")
set(MKDOCS_OUT "${CMAKE_BINARY_DIR}/../docs")

message("MKDocs src: ${MKDOCS_SRC} > ${MKDOCS_OUT}")

file(MAKE_DIRECTORY "${MKDOCS_OUT}")

add_custom_target(docs
        COMMAND ${CMAKE_COMMAND} -E env PYTHONUNBUFFERED=1
        mkdocs build
        --clean
        --site-dir "${MKDOCS_OUT}"
        --config-file "${MKDOCS_SRC}/mkdocs.yml"
        WORKING_DIRECTORY "${MKDOCS_SRC}"
        COMMENT "Generating documentation with MkDocs"
        VERBATIM
)

# Optional install step
install(DIRECTORY "${MKDOCS_OUT}/"
        DESTINATION "share/doc/${PROJECT_NAME}"
        COMPONENT docs)

add_custom_target(install-docs
        DEPENDS docs
        COMMAND "${CMAKE_COMMAND}" --install . --component docs
        COMMENT "Installing documentation")