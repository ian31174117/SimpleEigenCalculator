import pytest
import numpy as np
import eigen_calculator

def test_multiply_naive():
    def populate(mat):
        for i in range(mat.nrow):
            for j in range(mat.ncol):
                mat[i, j] = 0.5
    def print_mat(mat):
        for i in range(mat.nrow):
            for j in range(mat.ncol):
                print(mat[i, j], end=' ')
    mat1 = eigen_calculator.Matrix(3, 3)
    mat2 = eigen_calculator.Matrix(3, 3)
    populate(mat1)
    populate(mat2)
    result = eigen_calculator.multiply_naive(mat1, mat2)
    for i in range(result.nrow):
        for j in range(result.ncol):
            assert result[i, j] == 0.75 

def test_method():
    method1 = eigen_calculator.EigenMethod.JACOBIAN
    method2 = eigen_calculator.EigenMethod.QR
    solver = eigen_calculator.SimpleEigenCalculator()
    assert method1 == solver.getMethod()
    solver.setMethod(method2)
    assert method2 == solver.getMethod()
    mat1 = eigen_calculator.Matrix(3, 3)
    solver.setMatrix(mat1)

def test_not_set():
    solver = eigen_calculator.SimpleEigenCalculator()
    with pytest.raises(ValueError):
        solver.calculateEigen()
    mat1 = eigen_calculator.Matrix(3, 2)
    def populate(mat):
        for i in range(mat.nrow):
            for j in range(mat.ncol):
                mat[i, j] = i * j + 0.5
    populate(mat1)
    solver.setMatrix(mat1)
    with pytest.raises(ValueError):
        solver.calculateEigen()

def test_jacobian():
    n = 60
    solver = eigen_calculator.SimpleEigenCalculator()
    mat1 = eigen_calculator.Matrix(n, n)
    np_mat = np.zeros((n, n))
    def populate_symmetric(mat, np_mat):
        np.random.seed(0)
        for i in range(mat.nrow):
            for j in range(i+1):
                mat[i, j] = np.random.rand()
                mat[j, i] = mat[i, j]
                np_mat[i, j] = mat[i, j]
                np_mat[j, i] = mat[j, i]
    populate_symmetric(mat1, np_mat)
    solver.setMatrix(mat1)
    solver.setMethod(eigen_calculator.EigenMethod.JACOBIAN)
    solver.setTol(1e-8)
    solver.setMaxIter(5 * n**2)
    solver.setSortFlag(True)
    #get time
    import time
    start = time.time()
    solver.calculateEigen()
    end = time.time()
    print("Time for simple eigen calculator: ", end-start)
    
    mat_eigenValues = solver.getEigenValues()
    mat_eigenVectors = solver.getEigenVectors()
    mat2_flatten = np.zeros(n)
    start = time.time()
    np_eigenvalues, np_eigenvectors = np.linalg.eig(np_mat)
    end = time.time()
    print("Time for numpy eigen calculator: ", end-start)
    for i in range(n):
        mat2_flatten[i] = mat_eigenValues[i, i]
    np_eigenvalues_sorted = np.sort(np_eigenvalues)
    mat2_flatten_sorted = np.sort(mat2_flatten)
    np_eigenvalues_sorted_args = np.argsort(np_eigenvalues)
    np_eigenvalues_sorted_args = np_eigenvalues_sorted_args[::-1]
    np_eigenvectors_sorted = np.zeros((n, n))
    for i in range(n):
        np_eigenvectors_sorted[:, i] = np_eigenvectors[:, np_eigenvalues_sorted_args[i]]

    assert np.allclose(np_eigenvalues_sorted, mat2_flatten_sorted, atol = 1e-5)

    for i in range(n):
        for j in range(n):
            assert np.allclose(abs(np_eigenvectors_sorted[i, j]), abs(mat_eigenVectors[i, j]), atol=1e-5)


if __name__ == '__main__':
    test_jacobian()