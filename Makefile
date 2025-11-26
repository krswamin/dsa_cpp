# ----------------------------------------
# Makefile for DSA C++ Repo
# ----------------------------------------

# Enable parallel builds
MAKEFLAGS += -j

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -MMD -MP

# Root build directory
BUILD := build

# Formatter & Linters
CLANG_FORMAT := clang-format
CLANG_TIDY := clang-tidy
CPPCHECK := cppcheck

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
# Default build: format/lint modified files then compile
# ----------------------------------------
all: prebuild $(TARGETS)

# ----------------------------------------
# Pattern rule: build each executable
# ----------------------------------------
$(BUILD)/%: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

# ----------------------------------------
# Pre-build: format and lint only modified files (fast)
# ----------------------------------------
prebuild: format_modified lint_modified cppcheck_modified

# ----------------------------------------
# Format ALL files (manual, full run)
# ----------------------------------------
format:
	@echo "Formatting ALL C++ files..."
	@$(CLANG_FORMAT) -i $(SRCFILES)

# Format only modified files (fast, automatic)
format_modified:
	@echo "Formatting modified C++ files..."
	@changed=$$(git diff --name-only --diff-filter=ACM | grep -E '\.(cpp|h)$$'); \
	if [ -n "$$changed" ]; then \
		$(CLANG_FORMAT) -i $$changed; \
	else \
		echo "No modified files to format."; \
	fi

# ----------------------------------------
# Lint ALL files (manual, full run)
# ----------------------------------------
lint:
	@echo "Running clang-tidy on ALL C++ files..."
	@$(CLANG_TIDY) $(SOURCES) -- -I.

# Lint only modified files (fast, automatic)
lint_modified:
	@echo "Running clang-tidy on modified files..."
	@changed=$$(git diff --name-only --diff-filter=ACM | grep -E '\.cpp$$'); \
	if [ -n "$$changed" ]; then \
		$(CLANG_TIDY) $$changed -- -I.; \
	else \
		echo "No modified files to lint."; \
	fi

# ----------------------------------------
# Static analysis with cppcheck (full run)
# ----------------------------------------
cppcheck:
	@echo "Running cppcheck on ALL C++ files..."
	@$(CPPCHECK) --enable=all --inconclusive --std=c++17 --suppress=missingIncludeSystem $(SRCFILES)

# cppcheck only on modified files
cppcheck_modified:
	@echo "Running cppcheck on modified files..."
	@changed=$$(git diff --name-only --diff-filter=ACM | grep -E '\.cpp$$'); \
	if [ -n "$$changed" ]; then \
		$(CPPCHECK) --enable=all --inconclusive --std=c++17 --suppress=missingIncludeSystem $$changed; \
	else \
		echo "No modified files for cppcheck."; \
	fi

# ----------------------------------------
# Run cppcheck on a specific folder
# Usage: make cppcheck_dir DIR=foldername
# ----------------------------------------
cppcheck_dir:
	@if [ -z "$(DIR)" ]; then \
		echo "Usage: make cppcheck_dir DIR=foldername"; \
		exit 1; \
	fi
	@echo "Running cppcheck on folder $(DIR)..."
	@$(CPPCHECK) --enable=all --inconclusive --std=c++17 --suppress=missingIncludeSystem $(DIR)

# ----------------------------------------
# Full rebuild (clean + build)
# ----------------------------------------
rebuild: clean all

# ----------------------------------------
# Clean build artifacts
# ----------------------------------------
clean:
	rm -rf $(BUILD)

# ----------------------------------------
# Include dependency files for incremental build
# ----------------------------------------
-include $(DEPS)

# ----------------------------------------
# Declare phony targets
# ----------------------------------------
.PHONY: all prebuild format format_modified lint lint_modified cppcheck cppcheck_modified cppcheck_dir rebuild clean