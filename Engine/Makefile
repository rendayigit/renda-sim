# Define the build directory
BUILD_DIR := build

# Define the source directory as the directory of this Makefile
ROOT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

# Define the CMake command
CMAKE := cmake

# Define the CFLAGS variable with the -g flag
CFLAGS := -g

# Default target
all: src tests

# Target to build the source
src: 
	@mkdir -p $(BUILD_DIR)/src/
	@$(CMAKE) -DCMAKE_CXX_FLAGS=$(CFLAGS) $(ROOT_DIR)/src -B$(BUILD_DIR)/src/
	@$(MAKE) -C $(BUILD_DIR)/src/

# Target to build the tests
tests: 
	@mkdir -p $(BUILD_DIR)/tests/
	@$(CMAKE) -DCMAKE_CXX_FLAGS=$(CFLAGS) $(ROOT_DIR)/tests -B$(BUILD_DIR)/tests/
	@$(MAKE) -C $(BUILD_DIR)/tests/

# Clean target
clean:
	@rm -rf $(BUILD_DIR)

# Distclean target (for removing everything including configure results)
distclean: clean
	@true

.PHONY: all src source tests clean distclean

# Alias for src target
source: src

# Alias for test target
test: tests