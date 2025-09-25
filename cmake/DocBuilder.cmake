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

# Name of the target that launches the dev server
add_custom_target(
        serve_docs                     # ← invoke with `make serve_docs`
        COMMAND ${CMAKE_COMMAND} -E env PYTHONUNBUFFERED=1
        # On Windows we need to run the command through the shell
        # so that the `&&` operator works correctly.
        ${CMAKE_COMMAND} -E env
        mkdocs serve
        --dev-addr "127.0.0.1:8000"      # optional – explicit bind address
        --watch "${MKDOCS_SRC}" # watch source files for changes
        --config-file "${MKDOCS_SRC}/mkdocs.yml"
        WORKING_DIRECTORY "${MKDOCS_SRC}"
        USES_TERMINAL                  # tells CMake to attach the child process to the console
        COMMENT "Starting MkDocs live‑preview server (Ctrl‑C to stop)"
        VERBATIM
)

add_dependencies(serve_docs docs)   # ensures the static site is up‑to‑date before serving