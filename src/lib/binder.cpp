#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
//#include <pybind11/operators.h>
#include "matrix.hpp"
#include "utils.hpp"
#include "simple_eigen_calculator.hpp"

PYBIND11_MODULE(eigen_calculator, m){
    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def_property("nrow", &Matrix::get_rows, nullptr)
        .def_property("ncol", &Matrix::get_cols, nullptr)
        .def("__getitem__", [](Matrix &self, std::pair<size_t, size_t> i) {
            return self(i.first, i.second);
        })
        .def("__setitem__", [](Matrix &self, std::pair<size_t, size_t> i, double val) {
            self(i.first, i.second) = val;
        });
    pybind11::enum_<EigenMethod>(m, "EigenMethod")
        .value("JACOBIAN", EigenMethod::JACOBIAN)
        .value("QR", EigenMethod::QR);
    pybind11::enum_<MultiplyMethod>(m, "MultiplyMethod")
        .value("NAIVE", MultiplyMethod::NAIVE)
        .value("TILE", MultiplyMethod::TILE);
    pybind11::class_<SimpleEigenCalculator>(m, "SimpleEigenCalculator")
        .def(pybind11::init<>())
        .def("setMatrix", &SimpleEigenCalculator::setMatrix)
        .def("calculateEigen", &SimpleEigenCalculator::calculateEigen)
        .def("getEigenValues", &SimpleEigenCalculator::getEigenValues)
        .def("getEigenVectors", &SimpleEigenCalculator::getEigenVectors)
        .def("setMethod", &SimpleEigenCalculator::setMethod)
        .def("getMethod", &SimpleEigenCalculator::getMethod)
        .def("setMultiplyMethod", &SimpleEigenCalculator::setMultiplyMethod)
        .def("setTol", &SimpleEigenCalculator::setTol)
        .def("setMaxIter", &SimpleEigenCalculator::setMaxIter)
        .def("setSortFlag", &SimpleEigenCalculator::setSortFlag);
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("qr_decomposition", &qr_decomposition);
}