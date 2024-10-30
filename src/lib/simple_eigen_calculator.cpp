#include "simple_eigen_calculator.hpp"

SimpleEigenCalculator::SimpleEigenCalculator(){
    this->matrix = nullptr;
    this->eigen_vectors = Matrix(0, 0);
}

SimpleEigenCalculator::~SimpleEigenCalculator(){
    if(this->matrix != nullptr){
        delete this->matrix;
    }
}

void SimpleEigenCalculator::setMatrix(const Matrix* _matrix){
    if(this->matrix != nullptr){
        delete this->matrix;
    }
    this->matrix = new Matrix(_matrix->get_rows(), _matrix->get_cols());
    for(int i = 0; i < _matrix->get_rows(); i++){
        for(int j = 0; j < _matrix->get_cols(); j++){
            this->matrix->matrix_set(i, j, _matrix->matrix_get(i, j));
        }
    }
}

void SimpleEigenCalculator::calculateEigen(){
    if(this->matrix == nullptr){
        std::cerr << "Matrix not set" << std::endl;
        exit(1);
    }
    if(this->method == EigenMethod::JACOBIAN){
        // Jacobian method
    } else {
        // QR method
    }
}

void SimpleEigenCalculator::setMethod(EigenMethod _method){
    this->method = _method;
}

std::vector<float> SimpleEigenCalculator::getEigenValues(){
    return this->eigen_values;
}

Matrix SimpleEigenCalculator::getEigenVectors(){
    return this->eigen_vectors;
}