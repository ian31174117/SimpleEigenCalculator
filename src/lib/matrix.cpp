#include "matrix.hpp"

Matrix::Matrix(size_t _rows, size_t _cols) {
    this->rows = _rows;
    this->cols = _cols;
    this->data = new double[this->rows * this->cols];
    std::fill(this->data, this->data + this->rows * this->cols, 0.0);
}