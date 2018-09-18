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
