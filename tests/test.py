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

def test_qr_decomp_func():
    mat1 = eigen_calculator.Matrix(3, 3)
    mat1[0,0] = 4.0
    mat1[0,1] = -2.0
    mat1[1,0] = -2.0
    mat1[1,1] = 4.0
    mat1[2,2] = 3.0
    mat1[0,2] = 1.0
    mat1[2,0] = 1.0
    mat1[1,2] = -2.0
    mat1[2,1] = -2.0
    Q, R = eigen_calculator.qr_decomposition(mat1)
    QR = eigen_calculator.multiply_naive(Q, R)
    for i in range(3):
        for j in range(3):
            assert np.allclose(QR[i, j], mat1[i, j], atol=1e-5)
    print("Q:")
    for i in range(3):
        for j in range(3):
            print(Q[i, j], end=' ')
        print()
    print("R:")
    for i in range(3):
        for j in range(3):
            print(R[i, j], end=' ')
        print()

    np_arr = np.array([[4.0, -2.0, 1.0], [-2.0, 4.0, -2.0], [1.0, -2.0, 3.0]])
    Q_np, R_np = np.linalg.qr(np_arr)
    print("Q_np:")
    print(Q_np)
    print("R_np:")
    print(R_np)

    for i in range(3):
        for j in range(3):
            assert np.allclose(abs(Q[i, j]), abs(Q_np[i, j]), atol=1e-5)
            assert np.allclose(abs(R[i, j]), abs(R_np[i, j]), atol=1e-5)
    
def test_qr():
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
    solver.setMethod(eigen_calculator.EigenMethod.QR)
    solver.setTol(1e-5)
    solver.setMaxIter(3000)
    solver.setSortFlag(True)
    solver.setQRMethod(eigen_calculator.QRMethod.NAIVE)
    #get time
    import time
    start = time.time()
    solver.calculateEigen()
    end = time.time()
    print("Time for simple eigen calculator(naive): ", end-start)
    
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

    print(np_eigenvalues_sorted)
    print(mat2_flatten_sorted)

    assert np.allclose(np_eigenvalues_sorted[0], mat2_flatten_sorted[0], atol = 1e-2)

def test_qr_tile():
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
    solver.setMethod(eigen_calculator.EigenMethod.QR)
    solver.setMultiplyMethod(eigen_calculator.MultiplyMethod.TILE)
    solver.setTol(1e-5)
    solver.setMaxIter(3000)
    solver.setSortFlag(True)
    solver.setQRMethod(eigen_calculator.QRMethod.MKL)
    #get time
    import time
    start = time.time()
    solver.calculateEigen()
    end = time.time()
    print("Time for simple eigen calculator(tile): ", end-start)
    
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

    assert np.allclose(np_eigenvalues_sorted, mat2_flatten_sorted, atol = 1e-2)

if __name__ == '__main__':
    test_jacobian()
    test_qr()
    test_qr_tile()