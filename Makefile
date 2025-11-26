# ----------------------------------------
# Makefile for DSA C++ Repo
# ----------------------------------------

# Enable parallel builds
MAKEFLAGS += -j

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -MMD -MP

# Formatter
CLANG_FORMAT := clang-format

# Root build directory
BUILD := build

# Automatically find all subdirectories (exclude build)
SUBDIRS := $(shell find . -maxdepth 1 -type d ! -name . ! -name $(BUILD) | sed 's|./||')

# Find all .cpp and .h files
SOURCES := $(foreach d,$(SUBDIRS),$(wildcard $(d)/*.cpp))
HEADERS := $(foreach d,$(SUBDIRS),$(wildcard $(d)/*.h))
SRCFILES := $(SOURCES) $(HEADERS)

# Convert src.cpp -> build/src_folder/src
TARGETS := $(patsubst %.cpp,$(BUILD)/%,$(SOURCES))

# Dependency files
DEPS := $(TARGETS:%=%.d)

# ----------------------------------------
# Default build: format modified files then compile
# ----------------------------------------
all: format_modified $(TARGETS)

# ----------------------------------------
# Pattern rule: build each executable
# ----------------------------------------
$(BUILD)/%: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

# ----------------------------------------
# Format ALL files (manual)
# ----------------------------------------
format:
	@echo "Formatting ALL C++ files..."
	@$(CLANG_FORMAT) -i $(SRCFILES)

# ----------------------------------------
# Format only modified files (fast, automatic)
# ----------------------------------------
format_modified:
	@echo "Formatting modified C++ files..."
	@changed=$$(git diff --name-only --diff-filter=ACM | grep -E '\.(cpp|h)$$'); \
	if [ -n "$$changed" ]; then \
		$(CLANG_FORMAT) -i $$changed; \
	else \
		echo "No modified files to format."; \
	fi

# ----------------------------------------
# Include dependency files for incremental build
# ----------------------------------------
-include $(DEPS)

# ----------------------------------------
# Clean build artifacts
# ----------------------------------------
clean:
	rm -rf $(BUILD)