#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
//#include <pybind11/operators.h>
#include "matrix.hpp"
#include "utils.hpp"

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
    m.def("multiply_naive", &multiply_naive);
}