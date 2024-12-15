#pragma once
#include<iostream>
#include<vector>
#include<math.h>
#include "matrix.hpp"

Matrix multiply_naive(const Matrix &A, const Matrix &B);
std::pair<Matrix, Matrix> qr_decomposition(const Matrix &A);
