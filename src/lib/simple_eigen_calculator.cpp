#include "simple_eigen_calculator.hpp"

SimpleEigenCalculator::SimpleEigenCalculator(){
    this->eigen_vectors = Matrix(0, 0);
    this->matrix = Matrix(0, 0);
}

SimpleEigenCalculator::~SimpleEigenCalculator(){
}

void SimpleEigenCalculator::setMatrix(Matrix _matrix){
    this->matrix = Matrix(_matrix.get_rows(), _matrix.get_cols());
    for(size_t i = 0; i < _matrix.get_rows(); i++){
        for(size_t j = 0; j < _matrix.get_cols(); j++){
            this->matrix(i, j) = _matrix(i, j);
        }
    }
    return;
}

void SimpleEigenCalculator::calculateEigen(){
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