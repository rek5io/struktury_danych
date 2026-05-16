CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -pedantic -O3

SRC_DIR = src
BUILD_DIR = build

SRCS = $(SRC_DIR)/main.cpp

TARGET = $(BUILD_DIR)/main

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SRCS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

run: clean all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
