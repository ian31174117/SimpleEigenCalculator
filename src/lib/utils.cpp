#include "utils.hpp"

Matrix multiply_naive(const Matrix& A, const Matrix& B){
    if(A.get_cols() != B.get_rows()){
        std::cerr << "Matrix dimensions do not match for multiplication" << std::endl;
        exit(1);
    }
    Matrix C(A.get_rows(), B.get_cols());
    for(int i = 0; i < A.get_rows(); i++){
        for(int j = 0; j < B.get_cols(); j++){
            float sum = 0;
            for(int k = 0; k < A.get_cols(); k++){
                sum += A.matrix_get(i, k) * B.matrix_get(k, j);
            }
            C.matrix_set(i, j, sum);
        }
    }
    return C;
}