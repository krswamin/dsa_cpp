# Enable parallel builds automatically, to use all available cores
MAKEFLAGS += -j

# Compiler and flags
# -MMD -MP generates .d dependency files automatically.
# Only the relevant executable will rebuild — not the whole project.
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -MMD -MP

# Root build directory
BUILD := build

# Automatically find all subdirectories (exclude build)
SUBDIRS := $(shell find . -maxdepth 1 -type d ! -name . ! -name $(BUILD) | sed 's|./||')

# Find all .cpp files in all subdirs
SOURCES := $(foreach d,$(SUBDIRS),$(wildcard $(d)/*.cpp))

# Convert src.cpp -> build/src_folder/src
TARGETS := $(patsubst %.cpp,$(BUILD)/%,$(SOURCES))

# Corresponding dependency files
DEPS := $(TARGETS:%=%.d)

# Default build
all: $(TARGETS)

# Pattern rule for building executables
# Enables incremental build
$(BUILD)/%: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

# Include dependency files (auto-create if missing)
# Needed for incremental build
-include $(DEPS)

# Clean everything
clean:
	rm -rf $(BUILD)