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

enum class MultiplyMethod{
    NAIVE,
    TILE
};

enum class QRMethod{
    NAIVE,
    MKL
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
        void setMultiplyMethod(MultiplyMethod _method) { this->multiply_method = _method; };
        void setQRMethod(QRMethod _method) { this->qr_method = _method; };
        EigenMethod getMethod() { return this->method; };
        void setTol(float _tol) { this->tol = _tol; };
        void setMaxIter(int _max_iter) { this->max_iter = _max_iter; std::cout << "max_iter = " << this->max_iter << std::endl; };
        void setSortFlag(bool _sort_flag) { this->sort_flag = _sort_flag; std::cout << "sort_flag = " << this->sort_flag << std::endl; };
    private:
        Matrix matrix = Matrix(0, 0);
        Matrix eigen_vectors = Matrix(0, 0);
        EigenMethod method = EigenMethod::JACOBIAN;
        MultiplyMethod multiply_method = MultiplyMethod::NAIVE;
        QRMethod qr_method = QRMethod::NAIVE;
        float tol;
        int max_iter;
        void _jacobian();
        void _qr();
        void _rotate(size_t k, size_t l);
        bool sort_flag = true;
};