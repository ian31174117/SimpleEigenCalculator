CXX = g++
CXXFLAGS = -Wall -fPIC -I./src/include
LDFLAGS = -shared

INCLUDE_DIR = ./src/include
LIB_DIR = ./src/lib
BUILD_DIR = ./build

TARGET_DIR = ./build/eigen_calculator.so

SRC = $(wildcard $(LIB_DIR)/*.cpp)
OBJ = $(SRC:$(LIB_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(TARGET_DIR)

$(TARGET_DIR): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ)

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean test

test:

clean:
	rm -rf $(BUILD_DIR)