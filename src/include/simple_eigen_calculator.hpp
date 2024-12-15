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
        void setTol(float _tol) { this->tol = _tol; };
        void setMaxIter(int _max_iter) { this->max_iter = _max_iter; std::cout << "max_iter = " << this->max_iter << std::endl; };
        void setSortFlag(bool _sort_flag) { this->sort_flag = _sort_flag; std::cout << "sort_flag = " << this->sort_flag << std::endl; };
    private:
        Matrix matrix = Matrix(0, 0);
        Matrix eigen_vectors = Matrix(0, 0);
        EigenMethod method = EigenMethod::JACOBIAN;
        float tol;
        int max_iter;
        void _jacobian();
        void _rotate(size_t k, size_t l);
        bool sort_flag = true;
};