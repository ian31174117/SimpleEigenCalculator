#pragma once

#include <iostream>

class Matrix {
    public:
        Matrix(size_t _rows, size_t _cols);
        ~Matrix() = default;
        Matrix(const Matrix & other){
            this->rows = other.rows;
            this->cols = other.cols;
            this->data = new double[this->rows * this->cols];
            for(size_t i = 0; i < this->rows; i++){
                for(size_t j = 0; j < this->cols; j++){
                    this->data[i * this->cols + j] = other.data[i * this->cols + j];
                }
            }
        };
        size_t get_rows() const { return this->rows; };
        size_t get_cols() const { return this->cols; };
        double operator() (size_t i, size_t j) const { return data[i * cols + j]; };
        double& operator() (size_t i, size_t j) { return data[i * cols + j]; };
        Matrix & operator=(Matrix && other){
            if(this == &other){
                return *this;
            }
            delete[] this->data;
            this->rows = other.rows;
            this->cols = other.cols;
            this->data = other.data;
            other.data = nullptr;
            return *this;
        };
        Matrix & operator=(const Matrix & other){
            if(this == &other){
                return *this;
            }
            delete[] this->data;
            this->rows = other.rows;
            this->cols = other.cols;
            this->data = new double[this->rows * this->cols];
            for(size_t i = 0; i < this->rows; i++){
                for(size_t j = 0; j < this->cols; j++){
                    this->data[i * this->cols + j] = other.data[i * this->cols + j];
                }
            }
            return *this;
        };
        size_t rows;
        size_t cols;
        double* buffer_ref() const {return const_cast<double*>(this->data);};
    private:
        
        double* data;
};
