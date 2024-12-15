#pragma once
#include "matrix.hpp"
#include "utils.hpp"

#include<vector>
#include<utility>
#include<math.h>
#include<algorithm>

enum class EigenMethod{
    JACOBIAN,
    QR
};

class SimpleEigenCalculator{
    public:
        SimpleEigenCalculator();
        ~SimpleEigenCalculator();
        void setMatrix(Matrix _matrix);
        void calculateEigen();
        Matrix getEigenValues();
        Matrix getEigenVectors();
        void setMethod(EigenMethod _method);
        EigenMethod getMethod() { return this->method; };
    private:
        Matrix matrix = Matrix(0, 0);
        Matrix eigen_vectors = Matrix(0, 0);
        EigenMethod method = EigenMethod::JACOBIAN;
        float tol = 1e-8;
        int max_iter = 1000;
        void _jacobian();
        void _rotate(size_t k, size_t l);
        bool sort_flag = true;
};