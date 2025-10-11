PACKAGE_VERSION?=6.0.1
BASE_DIR:=$(CURDIR)
BUILD_DIR:=$(BASE_DIR)/../../build/packages
SDK_TARGETS := $(patsubst packages/%.json,%,$(wildcard packages/*.json))

# Default target to build all SDKs. This is the main entry point.
all: build

build: $(SDK_TARGETS)
	@echo "All SDKs have been processed."

# Rule to build each SDK package using OpenAPI Generator.
# It reads the corresponding JSON config file and generates the SDK in the build directory.
$(SDK_TARGETS): %: packages/%.json
	@echo "--- Building package $@ with version $(PACKAGE_VERSION) ---"
	rm -rf "$(BUILD_DIR)/$@/*"
	export TS_POST_PROCESS_FILE="/usr/local/bin/prettier --write" && \
	openapi-generator generate --skip-validate-spec \
		-i "$(BASE_DIR)/spec/oas-3.0.0.json" \
		-g "$@" \
		-o "$(BUILD_DIR)/$@" \
		-c "$<" \
		--artifact-version "$(PACKAGE_VERSION)" \
		--group-id "lethean" \
		-p packageVersion="$(PACKAGE_VERSION)" \
		--global-property "apiTests=true" \
		--additional-properties=npmVersion="$(PACKAGE_VERSION)",artifactVersion="$(PACKAGE_VERSION)"

# Phony targets to avoid conflicts with file names and to ensure they always run.
.PHONY: all build $(SDK_TARGETS)
