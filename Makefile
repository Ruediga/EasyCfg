CXX := g++
CXXFLAGS := -std=c++20 -Wall -fsanitize=address
SRC_DIR := src
BIN_DIR := build
TEST_DIR := tests

.PHONY: all clean run

$(OUTPUT_FILE): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(ROOT_DIR)/$@ $(SRCS)

# List of executables
BINARIES := test1 test2

SRC_FILES := $(wildcard $(SRC_DIR)/*)

# Define rules for each executable
$(BIN_DIR)/test1: $(SRC_FILES) $(TEST_DIR)/test1.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_FILES) $(TEST_DIR)/test1.cpp

$(BIN_DIR)/test2: $(SRC_DIR)/easycfg.h
	$(CXX) $(CXXFLAGS) -o $@ $<

# The default target builds all executables
all: $(addprefix $(BIN_DIR)/,$(EXECUTABLES))

# Clean up compiled executables
clean:
	rm -f $(BIN_DIR)/*

test1: $(TEST_DIR)/test1.cpp
	$(BIN_DIR)/test1