#pragma once
#include<iostream>
#include<vector>
#include<math.h>
#include <mkl.h>
#include <memory>
#include "matrix.hpp"

Matrix multiply_naive(const Matrix &A, const Matrix &B);
Matrix multiply_tile(const Matrix &A, const Matrix &B, size_t tile_size);
std::pair<Matrix, Matrix> qr_decomposition(const Matrix &A);
std::pair<Matrix, Matrix> qr_decomposition_mkl(const Matrix &A);
