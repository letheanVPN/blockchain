PACKAGE_VERSION?=6.0.1
BASE_DIR:=$(CURDIR)
# Default build directory. Can be overridden from the parent Makefile.
# e.g., `make sdk BUILD_DIR=client` will output to the `client/` directory.
BUILD_DIR?=$(BASE_DIR)/../../build/packages
SDK_TARGETS := $(patsubst packages/%.json,%,$(wildcard packages/*.json))

# --- Target-Specific Hooks ---
# Define pre- and post-build steps for specific languages.
# By default, these hooks are empty.

PRE_BUILD_HOOK  = @true
POST_BUILD_HOOK = @true

 # For the 'go' target, create an ignore file to prevent unwanted files from being generated.
 go: PRE_BUILD_HOOK = @echo "--> Creating .openapi-generator-ignore file for Go client"; \
 	echo "go.sum" >> $(BUILD_DIR)/go/.openapi-generator-ignore

# For the 'go' target, define specific post-build steps.
go: POST_BUILD_HOOK = @echo "--> Setting Go module path..."; \
	echo "--> Fixing import paths in generated Go files..."; \
	find "$(BUILD_DIR)/go" -type f -name '*.go' -exec sed -i '' 's|github.com/letheanVPN/blockchain/lthn|github.com/letheanVPN/blockchain/utils/sdk/client/go|g' {} +; \
	find "$(BUILD_DIR)/go" -type f -name '*.md' -exec sed -i '' 's|github.com/letheanVPN/blockchain/lthn|github.com/letheanVPN/blockchain/utils/sdk/client/go|g' {} +; \
	echo "--> Tidying Go module...";(cd $(BUILD_DIR)/go && go mod edit -module github.com/letheanVPN/blockchain/utils/sdk/client/go && go mod tidy)

# For the 'go' target, set the generator name correctly.
go: GENERATOR_NAME=go
php: GENERATOR_NAME=php-nextgen
angular: GENERATOR_NAME=typescript-angular
# --- Main Targets ---

all: build

build: $(SDK_TARGETS)
	@echo "All SDKs have been processed."

# Rule to build each SDK package using OpenAPI Generator.
# It reads the corresponding JSON config file and generates the SDK in the build directory.
$(SDK_TARGETS): %: packages/%.json
	# Default generator name is the target name itself.
	$(eval GENERATOR_NAME = $@)
	rm -rf "$(BUILD_DIR)/$@"
	# Ensure the output directory exists, cross-platform.
	@cmake -E make_directory "$(BUILD_DIR)/$@"
	@echo "--> Creating .openapi-generator-ignore file"
	@echo "git_push.sh" > "$(BUILD_DIR)/$@/.openapi-generator-ignore"
	@echo ".travis.yml" >> "$(BUILD_DIR)/$@/.openapi-generator-ignore"
	@echo "README.md" >> "$(BUILD_DIR)/$@/.openapi-generator-ignore"

	@echo "--- Building package $@ with version $(PACKAGE_VERSION) ---"
	# Run pre-build hook
	$(PRE_BUILD_HOOK)
	export TS_POST_PROCESS_FILE="/usr/local/bin/prettier --write" && \
	openapi-generator generate  --minimal-update --git-host "github.com" --git-repo-id "blockchain" --git-user-id "letheanVPN" \
		-i "$(BASE_DIR)/spec/oas-3.0.0.json" \
		-p 'developerEmail=support@lt.hn,developerName=Lethean Community,developerOrganization=lethean,developerOrganizationUrl=https://lt.hn' \
		-p "packageName=lthn,licenseName=EUPL-1.2" \
		-g "$(GENERATOR_NAME)" \
		-o "$(BUILD_DIR)/$@" \
		-c "$<" \
		--artifact-version "$(PACKAGE_VERSION)"
	# Run post-build hook
	$(POST_BUILD_HOOK)

# Phony targets to avoid conflicts with file names and to ensure they always run.
.PHONY: all build $(SDK_TARGETS)
