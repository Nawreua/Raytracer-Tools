#include "matrix.hh"

namespace
{
    bool equal(float a, float b)
    {
        return abs(a - b) < EPSILON;
    }
}

Matrix::Matrix()
    : height_(4), width_(4)
{
    grid_ = new float* [4];
    for (size_t i = 0; i < 4; i++)
    {
        grid_[i] = new float[4];
        for (size_t j = 0; j < 4; j++)
            grid_[i][j] = 0;
    }
}

Matrix::Matrix(size_t height, size_t width)
    : height_(height), width_(width)
{
    grid_ = new float* [height];
    for (size_t i = 0; i < height; i++)
    {
        grid_[i] = new float[width];
        for (size_t j = 0; j < width; j++)
            grid_[i][j] = 0;
    }
}

Matrix::Matrix(float grid[2][2])
    : height_(2), width_(2)
{
    grid_ = new float* [2];
    for (size_t i = 0; i < 2; i++)
    {
        grid_[i] = new float[2];
        for (size_t j = 0; j < 2; j++)
            grid_[i][j] = grid[i][j];
    }
}

Matrix::Matrix(float grid[3][3])
    : height_(3), width_(3)
{
    grid_ = new float* [3];
    for (size_t i = 0; i < 3; i++)
    {
        grid_[i] = new float[3];
        for (size_t j = 0; j < 3; j++)
            grid_[i][j] = grid[i][j];
    }
}

Matrix::Matrix(float grid[4][4])
    : height_(4), width_(4)
{
    grid_ = new float* [4];
    for (size_t i = 0; i < 4; i++)
    {
        grid_[i] = new float[4];
        for (size_t j = 0; j < 4; j++)
            grid_[i][j] = grid[i][j];
    }
}

float *Matrix::operator[](size_t i)
{
    return grid_[i];
}

float *Matrix::operator[](size_t i) const
{
    return grid_[i];
}

Matrix::~Matrix()
{
    for (size_t i = 0; i < height_; i++)
        delete[] grid_[i];
    delete[] grid_;
}

bool operator==(const Matrix& A, const Matrix& B)
{
    if (A.width_ != B.width_ || A.height_ != B.height_)
        return false;
    for (size_t i = 0; i < A.height_; i++)
        for (size_t j = 0; j < A.width_; j++)
            if (!equal(A[i][j], B[i][j]))
                return false;
    return true;
}

Matrix operator*(const Matrix& A, const Matrix& B)
{
    //Maybe add assert
    Matrix M;
    for (size_t row = 0; row < 4; row++)
    {
        for (size_t col = 0; col < 4; col++)
        {
            M[row][col] = A[row][0] * B[0][col] +
                          A[row][1] * B[1][col] +
                          A[row][2] * B[2][col] +
                          A[row][3] * B[3][col];
        }
    }
    return M;
}

Tuple operator*(const Matrix& A, const Tuple& b)
{
    float x = A[0][0] * b.x_ + A[0][1] * b.y_ + A[0][2] * b.z_ + A[0][3] * b.w_;
    float y = A[1][0] * b.x_ + A[1][1] * b.y_ + A[1][2] * b.z_ + A[1][3] * b.w_;
    float z = A[2][0] * b.x_ + A[2][1] * b.y_ + A[2][2] * b.z_ + A[2][3] * b.w_;
    float w = A[3][0] * b.x_ + A[3][1] * b.y_ + A[3][2] * b.z_ + A[3][3] * b.w_;
    return Tuple(x, y, z, w);
}
