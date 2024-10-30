#include "matrix.hpp"
#include "utils.hpp"

#include<vector>
#include<utility>

enum class EigenMethod{
    JACOBIAN,
    QR
};

class SimpleEigenCalculator{
    public:
        SimpleEigenCalculator();
        ~SimpleEigenCalculator();
        void setMatrix(const Matrix* _matrix);
        void calculateEigen();
        std::vector<float> getEigenValues();
        Matrix getEigenVectors();
        void setMethod(EigenMethod _method);
    private:
        Matrix* matrix;
        Matrix eigen_vectors = Matrix(0, 0);
        EigenMethod method = EigenMethod::JACOBIAN;
        std::vector<float> eigen_values;
        float tol = 1e-8;
        int max_iter = 1000;
};