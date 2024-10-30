#pragma once

#include <iostream>

class Matrix {
    public:
        Matrix(int _rows, int _cols);
        ~Matrix();
        int get_rows() const { return this->rows; };
        int get_cols() const { return this->cols; };
        void matrix_set(int row, int col, float val);
        float matrix_get(int row, int col) const;
        void transpose();
        bool is_transpose() const { return this->is_transposed; };
        Matrix submatrix(int start_row, int end_row, int start_col, int end_col);
        Matrix operator*(const Matrix& other);
    private:
        int rows;
        int cols;
        float* data;
        bool is_transposed;
};
