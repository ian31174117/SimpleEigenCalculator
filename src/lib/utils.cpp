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

std::pair<Matrix, Matrix> qr_decomposition(const Matrix &A){
    if(A.get_rows() != A.get_cols()){
        throw std::invalid_argument("Matrix must be square");
    }

    size_t n = A.get_rows();
    Matrix Q(n, n);
    Matrix R(n, n);
    std::vector<Matrix> u(n, Matrix(n, 1));

    for (size_t k = 0; k < n; k++) {
        // Copy column k of *this to u[k]
        for (size_t i = 0; i < n; i++)
            u[k](i, 0) = A(i, k);

        for (size_t j = 0; j < k; j++) {
            double dot = 0.0;
            for (size_t i = 0; i < n; i++){
                dot += u[k](i, 0) * Q(i, j);
            }

            for (size_t i = 0; i < n; i++){
                u[k](i, 0) -= dot * Q(i, j);
            }
        }

            double norm = 0.0;
            for (size_t i = 0; i < n; i++){
                norm += u[k](i, 0) * u[k](i, 0);
            }
            norm = std::sqrt(norm);

            for (size_t i = 0; i < n; i++){
                Q(i, k) = u[k](i, 0) / norm;
            }

            for (size_t j = k; j < n; j++) {
                double dot = 0.0;
                for (size_t i = 0; i < n; i++){
                    dot += Q(i, k) * A(i, j);
                }
                R(k, j) = dot;
            }
        }
        return {Q, R};
};