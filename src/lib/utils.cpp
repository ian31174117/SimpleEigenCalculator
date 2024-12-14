#include "utils.hpp"

Matrix multiply_naive(const Matrix &A, const Matrix &B){
    if(A.get_cols() != B.get_rows()){
        throw std::invalid_argument("col of A does not match row of B");
    }
    Matrix result(A.get_rows(), B.get_cols());
    //init result
    for(size_t i = 0; i < A.get_rows(); ++i){
        for(size_t j = 0; j < B.get_cols(); ++j){
            double sum = 0;
            for(size_t k = 0; k < A.get_cols(); ++k){
                sum += A(i, k) * B(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
};