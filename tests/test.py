import pytest
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