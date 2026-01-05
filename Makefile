# Makefile for Magical Pets Kingdom
# SFML Game Refactored Build System
# Configured for MSYS2 UCRT64

# Detect MSYS2 UCRT64 environment
MSYS2_UCRT64 := $(shell test -d /ucrt64 && echo "/ucrt64" || test -d /c/msys64/ucrt64 && echo "/c/msys64/ucrt64" || echo "")

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# If SFML is installed via MSYS2 pacman, it should be in the default paths
# If you need to specify custom paths, uncomment and modify these:
# SFML_INCLUDE = /ucrt64/include
# SFML_LIB = /ucrt64/lib
# CXXFLAGS += -I$(SFML_INCLUDE)
# LDFLAGS += -L$(SFML_LIB)

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Main target
TARGET = KingdomQuest

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory structure
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/Pets

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)
	@echo "Clean complete"

# Run the game
run: $(TARGET)
	@echo "Running $(TARGET)..."
ifeq ($(OS),Windows_NT)
	./$(TARGET).exe
else
	./$(TARGET)
endif

# Phony targets
.PHONY: all clean run

