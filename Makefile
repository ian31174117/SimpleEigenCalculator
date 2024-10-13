CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` -I./

all:

.PHONY: clean test

clean:

test: