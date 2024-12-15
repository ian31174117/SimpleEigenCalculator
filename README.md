# SimpleEigenCalculator
A light-weighted eigen calculator that supports Jacobian algorithm and QR algorithm.

## Prerequisites

### Python Packages
For neccessary tests to be performed with Python3.8, run:

```pip install numpy pytest pybind11```

## Usage
The library may be compiled/ tested in the following way:

### Compilation
Type `make` and the `.so` file will be generated, stored in `build/simple_eigen_calculator.so`

### Test
Type `make test` and the outcome will be verified with numpy and pytest.

### Performance
Type `make timer` to compare the performance of this light-weighted library and official implementation in numpy.