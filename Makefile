CXX = g++
CXXFLAGS = -Wall -fPIC -I./src/include `python3 -m pybind11 --includes` -I/usr/include/mkl -lblas -lmkl_rt
LDFLAGS = -shared

INCLUDE_DIR = ./src/include
LIB_DIR = ./src/lib
BUILD_DIR = ./build

TARGET_DIR = ./build/eigen_calculator.so

SRC = $(wildcard $(LIB_DIR)/*.cpp)
OBJ = $(SRC:$(LIB_DIR)/%.cpp=$(BUILD_DIR)/%.o)

MODULE_PATH = ./build/

all: $(TARGET_DIR)

$(TARGET_DIR): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) -lblas -lmkl_rt

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean test timer

test: $(TARGET_DIR) tests/test.py
	PYTHONPATH=$(BUILD_DIR):$(PYTHONPATH) python3 -m pytest -v tests/test.py

timer: $(TARGET_DIR) tests/test.py
	PYTHONPATH=$(BUILD_DIR):$(PYTHONPATH) python3 tests/test.py

clean:
	rm -rf $(BUILD_DIR)