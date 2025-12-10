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

# Find all .cpp and .h files (recursive, remove leading ./)
SOURCES := $(shell find . -type f -name '*.cpp' | sed 's|^\./||')
HEADERS := $(shell find . -type f -name '*.h' | sed 's|^\./||')
SRCFILES := $(SOURCES) $(HEADERS)

# Convert src.cpp -> build/src_folder/src (no .cpp in executable)
TARGETS := $(patsubst %.cpp,$(BUILD)/%,$(SOURCES))

# Dependency files
DEPS := $(TARGETS:%=%.d)

# ----------------------------------------
# Default build: format/lint modified files then compile
# ----------------------------------------
all: prebuild $(TARGETS)

# ----------------------------------------
# Pattern rule: build each executable
# $@ = build/.../name
# $< = source file with .cpp
$(BUILD)/%: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

# ----------------------------------------
# Pre-build: format and lint only modified files (fast)
# ----------------------------------------
prebuild: format_modified lint_modified

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
.PHONY: all prebuild format format_modified lint lint_modified rebuild clean