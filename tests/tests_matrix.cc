#include "include.hh"

TEST(MatrixTest, ImplementationTest)
{
    float grid[][4] = {
            {1, 2, 3, 4},
            {5.5, 6.5, 7.5, 8.5},
            {9, 10, 11, 12},
            {13.5, 14.5, 15.5, 16.5}};
    auto M = Matrix(grid);
    ASSERT_FLOAT_EQ(M[0][0], 1);
    ASSERT_FLOAT_EQ(M[0][3], 4);
    ASSERT_FLOAT_EQ(M[1][0], 5.5);
    ASSERT_FLOAT_EQ(M[1][2], 7.5);
    ASSERT_FLOAT_EQ(M[2][2], 11);
    ASSERT_FLOAT_EQ(M[3][0], 13.5);
    ASSERT_FLOAT_EQ(M[3][2], 15.5);
}

TEST(MatrixTest, Implementation2X2)
{
    float grid[][2] = {
        {-3, 5},
        {1, -2}
    };
    auto M = Matrix(grid);
    ASSERT_FLOAT_EQ(M[0][0], -3);
    ASSERT_FLOAT_EQ(M[0][1], 5);
    ASSERT_FLOAT_EQ(M[1][0], 1);
    ASSERT_FLOAT_EQ(M[1][1], -2);
}

TEST(MatrixTest, Implementation3X3)
{
    float grid[][3] = {
        {-3, 5, 0},
        {1, -2, 7},
        {0, 1, 1}
    };
    auto M = Matrix(grid);
    ASSERT_FLOAT_EQ(M[0][0], -3);
    ASSERT_FLOAT_EQ(M[1][1], -2);
    ASSERT_FLOAT_EQ(M[2][2], 1);
}

TEST(MatrixTest, MultiplicationTest)
{
    float gridA[][4] = {
        {1, 2, 3, 4},
        {2, 3, 4, 5},
        {3, 4, 5, 6},
        {4, 5, 6, 7}
    };
    auto A = Matrix(gridA);
    float gridB[][4] = {
        {0, 1, 2, 4},
        {1, 2, 4, 8},
        {2, 4, 8, 16},
        {4, 8, 16, 32}
    };
    auto B = Matrix(gridB);
    float gridC[][4] = {
        {24, 49, 98, 196},
        {31, 64, 128, 256},
        {38, 79, 158, 316},
        {45, 94, 188, 376}
    };
    ASSERT_EQ(A * B, Matrix(gridC));
}

TEST(MatrixTest, MultiplicationTuple)
{
    float gridA[][4] = {
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1}
    };
    auto A = Matrix(gridA);
    auto b = Tuple(1, 2, 3, 1);
    ASSERT_EQ(A * b, Tuple(18, 24, 33, 1));
}

TEST(MatrixTest, MultiplicationMatrixIdentity)
{
    float grid[][4] = {
        {0, 1, 2, 4},
        {1, 2, 4, 8},
        {2, 4, 8, 16},
        {4, 8, 16, 32}
    };
    auto A = Matrix(grid);
    ASSERT_EQ(A * Matrix::identity_matrix(), A);
}

TEST(MatrixTest, MultiplicationTupleIdentity)
{
    auto a = Tuple(1, 2, 3, 4);
    ASSERT_EQ(Matrix::identity_matrix() * a, a);
}

TEST(MatrixTest, TranspositionMatrix)
{
    float gridA[][4] = {
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
        {0, 0, 5, 8}
    };
    auto A = Matrix(gridA);
    float gridB[][4] = {
        {0, 9, 1, 0},
        {9, 8, 8, 0},
        {3, 0, 5, 5},
        {0, 8, 3, 8}
    };
    ASSERT_EQ(A.transpose(), Matrix(gridB));
}

TEST(MatrixTest, TranspositionIdentity)
{
    auto A = Matrix::identity_matrix().transpose();
    ASSERT_EQ(A, Matrix::identity_matrix());
}

TEST(MatrixTest, Determinant2X2)
{
    float grid[][2] = {
        {1, 5},
        {-3, 2}
    };
    auto A = Matrix(grid);
    ASSERT_FLOAT_EQ(A.determinant(), 17);
}

TEST(MatrixTest, Submatrix3X3)
{
    float gridA[][3] = {
        {1, 5, 0},
        {-3, 2, 7},
        {0, 6, -3}
    };
    auto A = Matrix(gridA);
    float gridB[][2] = {
        {-3, 2},
        {0, 6}
    };
    ASSERT_EQ(A.submatrix(0, 2), Matrix(gridB));
}

TEST(MatrixTest, Submatrix4X4)
{
    float gridA[][4] = {
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1}
    };
    auto A = Matrix(gridA);
    float gridB[][3] = {
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1}
    };
    ASSERT_EQ(A.submatrix(2, 1), Matrix(gridB));
}

TEST(MatrixTest, Minor3X3)
{
    float grid[][3] = {
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    };
    auto A = Matrix(grid);
    auto B = A.submatrix(1, 0);
    ASSERT_FLOAT_EQ(B.determinant(), 25);
    ASSERT_FLOAT_EQ(A.minor(1, 0), 25);
}

TEST(MatrixTest, Cofactor3X3)
{
    float grid[][3] = {
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    };
    auto A = Matrix(grid);
    ASSERT_FLOAT_EQ(A.minor(0, 0), -12);
    ASSERT_FLOAT_EQ(A.cofactor(0, 0), -12);
    ASSERT_FLOAT_EQ(A.minor(1, 0), 25);
    ASSERT_FLOAT_EQ(A.cofactor(1, 0), -25);
}

TEST(MatrixTest, Determinant3X3)
{
    float grid[][3] = {
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4}
    };
    auto A = Matrix(grid);
    ASSERT_FLOAT_EQ(A.cofactor(0, 0), 56);
    ASSERT_FLOAT_EQ(A.cofactor(0, 1), 12);
    ASSERT_FLOAT_EQ(A.cofactor(0, 2), -46);
    ASSERT_FLOAT_EQ(A.determinant(), -196);
}

TEST(MatrixTest, Determinant4X4)
{
    float grid[][4] = {
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}
    };
    auto A = Matrix(grid);
    ASSERT_FLOAT_EQ(A.cofactor(0, 0), 690);
    ASSERT_FLOAT_EQ(A.cofactor(0, 1), 447);
    ASSERT_FLOAT_EQ(A.cofactor(0, 2), 210);
    ASSERT_FLOAT_EQ(A.cofactor(0, 3), 51);
    ASSERT_FLOAT_EQ(A.determinant(), -4071);
}

TEST(MatrixTest, InvertibleTest)
{
    float grid[][4] = {
        {6, 4, 4, 4},
        {5, 5, 7, 6},
        {4, -9, 3, -7},
        {9, 1, 7, -6}
    };
    auto A = Matrix(grid);
    ASSERT_FLOAT_EQ(A.determinant(), -2120);
    ASSERT_TRUE(A.is_invertible());
}

TEST(MatrixTest, NonInvertibleTest)
{
    float grid[][4]  {
        {-4, 2, -2, -3},
        {9, 6, 2, 6},
        {0, -5, 1, -5},
        {0, 0, 0, 0}
    };
    auto A = Matrix(grid);
    ASSERT_FLOAT_EQ(A.determinant(), 0);
    ASSERT_FALSE(A.is_invertible());
}

TEST(MatrixTest, InverseTest)
{
    float gridA[][4] = {
        {-5, 2, 6, -8},
        {1, -5, 1, 8},
        {7, 7, -6, -7},
        {1, -3, 7, 4}
    };
    auto A = Matrix(gridA);
    auto B = A.inverse();
    ASSERT_FLOAT_EQ(A.determinant(), 532);
    ASSERT_FLOAT_EQ(A.cofactor(2, 3), -160);
    ASSERT_FLOAT_EQ(B[3][2], -160.0 / 532.0);
    ASSERT_FLOAT_EQ(A.cofactor(3, 2), 105);
    ASSERT_FLOAT_EQ(B[2][3], 105.0 / 532.0);
    float gridB[][4] = {
        { 0.21805, 0.45113,  0.24060, -0.04511 },
        { -0.80827, -1.45677, -0.44361, 0.52068 },
        { -0.07895, -0.22368, -0.05263, 0.19737 },
        { -0.52256, -0.81391, -0.30075, 0.30639}
    };
    ASSERT_EQ(B, Matrix(gridB));
}

TEST(MatrixTest, InverseTest2)
{
    float gridA[][4] = {
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4}
    };
    auto A = Matrix(gridA);
    float gridB[][4] = {
        { -0.15385 , -0.15385 , -0.28205 , -0.53846 },
        { -0.07692 , 0.12308 , 0.02564 , 0.03077 },
        { 0.35897 , 0.35897 , 0.43590 , 0.92308 },
        { -0.69231 , -0.69231 , -0.76923 , -1.92308 }
    };
    ASSERT_EQ(A.inverse(), Matrix(gridB));
}

TEST(MatrixTest, InverseTest3)
{
    float gridA[][4] = {
        {9, 3, 0, 9},
        {-5, -2, -6, -3},
        {-4, 9, 6, 4},
        {-7, 6, 6, 2}
    };
    auto A = Matrix(gridA);
    float gridB[][4] = {
        { -0.04074 , -0.07778 , 0.14444, -0.22222 },
        { -0.07778 , 0.03333 , 0.36667 , -0.33333 },
        { -0.02901 , -0.14630 , -0.10926, 0.12963 },
        { 0.17778 , 0.06667 , -0.26667 , 0.33333}
    };
    ASSERT_EQ(A.inverse(), Matrix(gridB));
}

TEST(MatrixTest, MultiplyByInverse)
{
    float gridA[][4] = {
        {3, -9, 7, 3},
        {3, -8, 2, -9},
        {-4, 4, 4, 1},
        {-6, 5, -1, 1}
    };
    auto A = Matrix(gridA);
    float gridB[][4] = {
        {8, 2, 2, 2},
        {3, -1, 7, 0},
        {7, 0, 5, 4},
        {6, -2, 0, 5}
    };
    auto B = Matrix(gridB);
    auto C = A * B;
    ASSERT_EQ(C * B.inverse(), A);
}
