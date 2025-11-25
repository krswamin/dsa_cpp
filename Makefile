# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Root build folder
BUILD := build

# Automatically find all subfolders
SUBDIRS := $(shell find . -maxdepth 1 -type d ! -name . ! -name $(BUILD) | sed 's|./||')

# Collect all source files in all subfolders
SOURCES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.cpp))

# Generate target executables in build/<subfolder>/<name>
TARGETS := $(patsubst %.cpp,$(BUILD)/%,$(SOURCES))

# Default target
all: $(TARGETS)

# Rule to build each executable
$(BUILD)/%: %.cpp
	@dir=$(dir $@); \
	mkdir -p $$dir; \
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean build folder
clean:
	rm -rf $(BUILD)
