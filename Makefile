STD ?= 2a
BASENAME ?= a

CXX := g++
CXXFLAGS := -fdiagnostics-color=always -std=c++$(STD) -I. -Wall -Wextra

BUILD_DIR := bin
SRC := $(BASENAME).cpp
TARGET := $(BUILD_DIR)/$(BASENAME).out
DEBUG_TARGET := $(BUILD_DIR)/debug/$(BASENAME).out

.PHONY: clean debug release

release: CXXFLAGS += -O2
debug: CXXFLAGS += -g -O0 -fsanitize=undefined,address

release: $(TARGET)
debug: $(DEBUG_TARGET)
clean:
	$(RM) -r $(BUILD_DIR)

$(TARGET): $(SRC) $(BUILD_DIR)
	$(CXX) -o $@ $< $(CXXFLAGS)

$(DEBUG_TARGET): $(SRC) $(BUILD_DIR)/debug
	$(CXX) -o $@ $< $(CXXFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/debug:
	mkdir -p $(BUILD_DIR)/debug

