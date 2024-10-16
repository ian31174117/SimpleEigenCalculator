#include "matrix.hpp"

Matrix::Matrix(int _rows, int _cols) {
    this->rows = _rows;
    this->cols = _cols;
    this->data = (float*)malloc(rows * cols * sizeof(float));
    this->is_transposed = false;
}

Matrix::~Matrix() {
    free(this->data);
}

void Matrix::matrix_set(int row, int col, float val){
    
}

float Matrix::matrix_get(int row, int col) const{
    if(row < 0 || row >= this->get_rows() || col < 0 || col >= this->get_cols()){
        std::cerr << "Matrix index out of bounds" << std::endl;
        exit(1);
    }
    if(this->is_transposed){
        return this->data[col * this->rows + row];
    } else {
        return this->data[row * this->cols + col];
    }
}

void Matrix::transpose(){
    this->is_transposed = !this->is_transposed;
    int temp = this->rows;
    this->rows = this->cols;
    this->cols = temp;
    return;
}

Matrix Matrix::submatrix(int start_row, int end_row, int start_col, int end_col){
    if(start_row < 0 || start_row >= this->rows || end_row < 0 || end_row >= this->rows || start_col < 0 || start_col >= this->cols || end_col < 0 || end_col >= this->cols){
        std::cerr << "Matrix index out of bounds" << std::endl;
        exit(1);
    }
    if(start_row > end_row || start_col > end_col){
        std::cerr << "Invalid submatrix bounds" << std::endl;
        exit(1);
    }
    int new_rows = end_row - start_row + 1;
    int new_cols = end_col - start_col + 1;
    Matrix submatrix(new_rows, new_cols);
    for(int i = start_row; i <= end_row; i++){
        for(int j = start_col; j <= end_col; j++){
            submatrix.matrix_set(i - start_row, j - start_col, this->matrix_get(i, j));
        }
    }
    return submatrix;
}

Matrix Matrix::operator*(const Matrix& other){
    if(this->cols != other.get_rows()){
        std::cerr << "Matrix dimensions do not match for multiplication" << std::endl;
        exit(1);
    }
    Matrix result(this->rows, other.cols);
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < other.get_cols(); j++){
            float sum = 0;
            for(int k = 0; k < this->cols; k++){
                sum += this->matrix_get(i, k) * other.matrix_get(k, j);
            }
            result.matrix_set(i, j, sum);
        }
    }
    return result;
}