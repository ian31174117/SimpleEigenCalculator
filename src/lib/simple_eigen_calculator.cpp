#include "simple_eigen_calculator.hpp"

SimpleEigenCalculator::SimpleEigenCalculator(){
    this->eigen_vectors = Matrix(0, 0);
    this->matrix = Matrix(0, 0);
    this->max_iter = 1000;
    this->tol = 1e-8;
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
        _jacobian();
    } else {
        // QR method
    }
}

void SimpleEigenCalculator::setMethod(EigenMethod _method){
    this->method = _method;
}

Matrix SimpleEigenCalculator::getEigenValues(){
    return this->matrix;
}

Matrix SimpleEigenCalculator::getEigenVectors(){
    return this->eigen_vectors;
}

void SimpleEigenCalculator::_jacobian(){
    /*//print initial matrix
    std::cout << "Initial matrix: " << std::endl;
    for(size_t i = 0; i < this->matrix.get_rows(); i++){
        for(size_t j = 0; j < this->matrix.get_cols(); j++){
            std::cout << this->matrix(i, j) << " ";
        }
        std::cout << std::endl;
    }*/
    if(this->matrix.get_rows() == 0 || this->matrix.get_cols() == 0){
        throw std::invalid_argument("Matrix not set");
    }
    if(this->matrix.get_rows() != this->matrix.get_cols()){
        throw std::invalid_argument("Matrix must be square");
    }
    size_t n = this->matrix.get_rows();
    this->eigen_vectors = Matrix(n, n);
    for(size_t i = 0; i < n; i++){//make identity matrix
        this->eigen_vectors(i, i) = 1.0;
    }
    for(int iter = 0; iter < this->max_iter; iter++){
        float max_off_diag = 0.0;
        size_t p = 0;
        size_t q = 0;
        for(size_t i = 0; i < n - 1; i++){//find max off diagonal element
            for(size_t j = i + 1; j < n; j++){
                if(std::abs(this->matrix(i, j)) >= max_off_diag){
                    max_off_diag = std::abs(this->matrix(i, j));
                    p = i;
                    q = j;
                }
            }
        }
        if(max_off_diag < this->tol){
            /*//print current matrix
            std::cout << "Eigen values: " << std::endl;
            for(size_t i = 0; i < n; i++){
                for(size_t j = 0; j < n; j++){
                    std::cout << this->matrix(i, j) << " ";
                }
                std::cout << std::endl;
            }
            //print current eigen vectors
            std::cout << "Eigen vectors: " << std::endl;
            for(size_t i = 0; i < n; i++){
                for(size_t j = 0; j < n; j++){
                    std::cout << this->eigen_vectors(i, j) << " ";
                }
                std::cout << std::endl;
            }*/
            //throw std::invalid_argument("Experiment:, iter = " + std::to_string(iter) + ", max_off_diag = " + std::to_string(max_off_diag));
            break;
        }
        if(iter == this->max_iter - 1){
            //hrow std::invalid_argument("Max iteration reached: " + std::to_string(iter) + ", max_off_diag = " + std::to_string(max_off_diag));
        }
        _rotate(p, q);//rotation
    }
    /*//print eigen vectors before sort
    std::cout<<"Eigen vectors before sort: "<<std::endl;
    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < n; j++){
            std::cout<<this->eigen_vectors(i, j)<<" ";
        }
        std::cout<<std::endl;
    }
    //print eigen values before sort
    std::cout<<"Eigen values before sort: "<<std::endl;
    for(size_t i = 0; i < n; i++){
        std::cout<<this->matrix(i, i)<<" ";
    }
    std::cout<<std::endl;*/
    if(sort_flag){
        std::vector<std::pair<double, size_t>> eigen_values_idx;
        for(size_t i = 0; i < n; i++){
            eigen_values_idx.push_back(std::make_pair(this->matrix(i, i), i));
        }
        Matrix eigen_vectors_temp = this->eigen_vectors;
        std::sort(eigen_values_idx.begin(), eigen_values_idx.end(), std::greater<std::pair<double, size_t>>());
        for(size_t i = 0; i < n; i++){
            this->matrix(i, i) = eigen_values_idx[i].first;
            for(size_t j = 0; j < n; j++){
                this->eigen_vectors(j, i) = eigen_vectors_temp(j, eigen_values_idx[i].second);
            }
        }
    }
    /*//print eigen vectors after sort
    std::cout<<"Eigen vectors after sort: "<<std::endl;
    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < n; j++){
            std::cout<<this->eigen_vectors(i, j)<<" ";
        }
        std::cout<<std::endl;
    }
    //print eigen values after sort
    std::cout<<"Eigen values after sort: "<<std::endl;
    for(size_t i = 0; i < n; i++){
        std::cout<<this->matrix(i, i)<<" ";
    }
    std::cout<<std::endl;*/
    return;
}

void SimpleEigenCalculator::_rotate(size_t k, size_t l){
    size_t n = this->matrix.get_rows();
    double matDiff = this->matrix(l, l) - this->matrix(k, k);
    double t = 0.0;
    if(std::abs(this->matrix(k, l)) < std::abs(matDiff) * 1.0e-36){
        t = this->matrix(k, l) / matDiff;
    } else {
        float phi = matDiff / (2.0 * this->matrix(k, l));
        t = 1.0 / (std::abs(phi) + std::sqrt(phi * phi + 1.0));
        if(phi < 0.0){
            t = -t;
        }
    }
    double c = 1.0 / std::sqrt(t * t + 1.0);
    double s = t * c;
    double tau = s / (1.0 + c);
    double temp = this->matrix(k, l);
    this->matrix(k, l) = 0.0;
    this->matrix(k, k) -= t * temp;
    this->matrix(l, l) += t * temp;
    for(size_t i = 0; i < k; i++){
        temp = this->matrix(i, k);
        this->matrix(i, k) = temp - s * (this->matrix(i, l) + temp * tau);
        this->matrix(i, l) = this->matrix(i, l) + s * (temp - this->matrix(i, l) * tau);
    }
    for(size_t i = k + 1; i < l; i++){
        temp = this->matrix(k, i);
        this->matrix(k, i) = temp - s * (this->matrix(i, l) + this->matrix(k, i) * tau);
        this->matrix(i, l) = this->matrix(i, l) + s * (temp - this->matrix(i, l) * tau);
    }
    for(size_t i = l + 1; i < n; i++){
        temp = this->matrix(k, i);
        this->matrix(k, i) = temp - s * (this->matrix(l, i) + temp * tau);
        this->matrix(l, i) = this->matrix(l, i) + s * (temp - this->matrix(l, i) * tau);
    }
    for(size_t i = 0; i < n; i++){
        temp = this->eigen_vectors(i, k);
        this->eigen_vectors(i, k) = temp - s * (this->eigen_vectors(i, l) + temp * tau);
        this->eigen_vectors(i, l) = this->eigen_vectors(i, l) + s * (temp - this->eigen_vectors(i, l) * tau);
    }
    /*for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix(i, j) = 0.0;
        }
    }*/
    return;
}