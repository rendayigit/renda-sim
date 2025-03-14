# Define the source directory as the directory of this Makefile
ROOT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

# Define the build directory
BUILD_DIR := $(ROOT_DIR)/build

# Define the CMake command
CMAKE := cmake

# Define the CFLAGS variable with the -g flag
CFLAGS := -g

# Default target
all: src tests

# Target to build the source
src: 
	@mkdir -p $(BUILD_DIR)/src/
	@$(CMAKE) -DCMAKE_CXX_FLAGS=$(CFLAGS) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON $(ROOT_DIR)/src -B$(BUILD_DIR)/src/
	@$(MAKE) -C $(BUILD_DIR)/src/
	@cp $(BUILD_DIR)/src/compile_commands.json $(BUILD_DIR)/compile_commands_src.json
	@$(MAKE) merge_compile_commands

# Target to build the tests
# tests: 
# 	@mkdir -p $(BUILD_DIR)/tests/
# 	@$(CMAKE) -DCMAKE_CXX_FLAGS=$(CFLAGS) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON $(ROOT_DIR)/tests -B$(BUILD_DIR)/tests/
# 	@$(MAKE) -C $(BUILD_DIR)/tests/
# 	@cp $(BUILD_DIR)/tests/compile_commands.json $(BUILD_DIR)/compile_commands_tests.json
# 	@$(MAKE) merge_compile_commands

# Merge the compile commands
merge_compile_commands:
	@if [ -f $(BUILD_DIR)/compile_commands_src.json ] && [ -f $(BUILD_DIR)/compile_commands_tests.json ]; then \
		jq -s '.[0] + .[1]' $(BUILD_DIR)/compile_commands_src.json $(BUILD_DIR)/compile_commands_tests.json > $(BUILD_DIR)/compile_commands.json; \
	else \
		if [ -f $(BUILD_DIR)/compile_commands_src.json ]; then \
			cp $(BUILD_DIR)/compile_commands_src.json $(BUILD_DIR)/compile_commands.json; \
		elif [ -f $(BUILD_DIR)/compile_commands_tests.json ]; then \
			cp $(BUILD_DIR)/compile_commands_tests.json $(BUILD_DIR)/compile_commands.json; \
		fi; \
	fi

# Target to build and run tests with coverage
coverage: 
	@mkdir -p $(BUILD_DIR)/tests_coverage/
	@$(CMAKE) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DENABLE_COVERAGE=ON $(ROOT_DIR)/tests -B$(BUILD_DIR)/tests_coverage/
	@$(MAKE) -C $(BUILD_DIR)/tests_coverage/
	@$(ROOT_DIR)/bin/model-tests
	@mkdir -p $(ROOT_DIR)/coverage/
	@python3 -m gcovr --config $(ROOT_DIR)/gcovr.cfg

# Clean target
clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(ROOT_DIR)/bin
	@rm -rf $(ROOT_DIR)/coverage
	@rm -rf $(ROOT_DIR)/../bin

# Distclean target (for removing everything including configure results)
distclean: clean
	@true

.PHONY: all src source tests coverage merge_compile_commands clean distclean

# Alias for src target
source: src

# Alias for test target
test: tests

# Alias for cov target
cov: coverage