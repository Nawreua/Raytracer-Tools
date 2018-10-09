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
    grid_ = std::vector<std::vector<float>>(4);
    for (size_t i = 0; i < 4; i++)
    {
        grid_[i].resize(4);
        for (size_t j = 0; j < 4; j++)
            grid_[i][j] = 0;
    }
}

Matrix::Matrix(const Matrix& m)
    : height_(m.height_), width_(m.width_)
{
    grid_ = std::vector<std::vector<float>>(m.height_);
    for (size_t i = 0; i < m.height_; i++)
    {
        grid_[i].resize(m.width_);
        for (size_t j = 0; j < m.width_; j++)
            grid_[i][j] = m.grid_[i][j];
    }
}

Matrix::Matrix(Matrix& m)
    : height_(m.height_), width_(m.width_)
{
    grid_ = std::vector<std::vector<float>>(m.height_);
    for (size_t i = 0; i < m.height_; i++)
    {
        grid_[i].resize(m.width_);
        for (size_t j = 0; j < m.width_; j++)
            grid_[i][j] = m.grid_[i][j];
    }
}

Matrix::Matrix(size_t height, size_t width)
    : height_(height), width_(width)
{
    grid_ = std::vector<std::vector<float>>(height);
    for (size_t i = 0; i < height; i++)
    {
        grid_[i].resize(width);
        for (size_t j = 0; j < width; j++)
            grid_[i][j] = 0;
    }
}

Matrix::Matrix(float grid[2][2])
    : height_(2), width_(2)
{
    grid_ = std::vector<std::vector<float>>(2);
    for (size_t i = 0; i < 2; i++)
    {
        grid_[i].resize(2);
        for (size_t j = 0; j < 2; j++)
            grid_[i][j] = grid[i][j];
    }
}

Matrix::Matrix(float grid[3][3])
    : height_(3), width_(3)
{
    grid_ = std::vector<std::vector<float>>(3);
    for (size_t i = 0; i < 3; i++)
    {
        grid_[i].resize(3);
        for (size_t j = 0; j < 3; j++)
            grid_[i][j] = grid[i][j];
    }
}

Matrix::Matrix(float grid[4][4])
    : height_(4), width_(4)
{
    grid_ = std::vector<std::vector<float>>(4);
    for (size_t i = 0; i < 4; i++)
    {
        grid_[i].resize(4);
        for (size_t j = 0; j < 4; j++)
            grid_[i][j] = grid[i][j];
    }
}

Matrix Matrix::identity_matrix()
{
    float grid[][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return Matrix(grid);
}

Matrix Matrix::transpose() const
{
    Matrix transposed{width_, height_};
    for (size_t i = 0; i < width_; i++)
        for (size_t j = 0; j < height_; j++)
            transposed[i][j] = grid_[j][i];
    return transposed;
}

float Matrix::determinant() const
{
    if (width_ == 2 && height_ == 2)
        return grid_[0][0] * grid_[1][1] - grid_[0][1] * grid_[1][0];
    float res = 0;
    for (size_t i = 0; i < width_; i++)
        res += grid_[0][i] * cofactor(0, i);
    return res;
}

Matrix Matrix::submatrix(size_t row, size_t col) const
{
    Matrix sub{height_ - 1, width_ - 1};
    size_t i_sub = 0;
    for (size_t i = 0; i < height_; i++)
    {
        if (i == row)
            continue;
        size_t j_sub = 0;
        for (size_t j = 0; j < width_; j++)
        {
            if (j == col)
                continue;
            sub[i_sub][j_sub] = grid_[i][j];
            j_sub++;
        }
        i_sub++;
    }
    return sub;
}

float Matrix::minor(size_t row, size_t col) const
{
    return submatrix(row, col).determinant();
}

float Matrix::cofactor(size_t row, size_t col) const
{
    if ((row + col) % 2 == 0)
        return minor(row, col);
    return -minor(row, col);
}

bool Matrix::is_invertible() const
{
    return determinant() != 0;
}

Matrix Matrix::inverse() const
{
    Matrix cofact{height_, width_};
    for (size_t i = 0; i < height_; i++)
        for (size_t j = 0; j < width_; j++)
            cofact[i][j] = cofactor(i, j);
    Matrix transposed_cofact = cofact.transpose();
    auto det = determinant();
    for (size_t i = 0; i < height_; i++)
        for (size_t j = 0; j < width_; j++)
            transposed_cofact[i][j] /= det;
    return transposed_cofact;
}

std::vector<float>& Matrix::operator[](size_t i)
{
    return grid_[i];
}

const std::vector<float>& Matrix::operator[](size_t i) const
{
    return grid_[i];
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

Matrix translation(float x, float y, float z)
{
    float grid[][4] = {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    };
    return Matrix(grid);
}

Matrix scaling(float x, float y, float z)
{
    float grid[][4] = {
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}
    };
    return Matrix(grid);
}

Matrix rotation_x(float r)
{
    float cos_r = cos(r);
    float sin_r = sin(r);
    float grid[][4] = {
        {1, 0, 0, 0},
        {0, cos_r, -sin_r, 0},
        {0, sin_r, cos_r, 0},
        {0, 0, 0, 1}
    };
    return Matrix(grid);
}

Matrix rotation_y(float r)
{
    float cos_r = cos(r);
    float sin_r = sin(r);
    float grid[][4] = {
        {cos_r, 0, sin_r, 0},
        {0, 1, 0, 0},
        {-sin_r, 0, cos_r, 0},
        {0, 0, 0, 1}
    };
    return Matrix(grid);
}

Matrix rotation_z(float r)
{
    float cos_r = cos(r);
    float sin_r = sin(r);
    float grid[][4] = {
        {cos_r, -sin_r, 0, 0},
        {sin_r, cos_r, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return Matrix(grid);
}

Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
    float grid[][4] = {
        {1, xy, xz, 0},
        {yx, 1, yz, 0},
        {zx, zy, 1, 0},
        {0, 0, 0, 1}
    };
    return Matrix(grid);
}

Matrix view_transform(const Tuple& from, const Tuple& to, const Tuple& up)
{
    auto forward = (to - from).normalize();
    auto upn = up.normalize();
    auto left = cross(forward, upn);
    auto true_up = cross(left, forward);
    float grid[][4] = {
        {left.x_, left.y_, left.z_, 0},
        {true_up.x_, true_up.y_, true_up.z_, 0},
        {-forward.x_, -forward.y_, -forward.z_, 0},
        {0, 0, 0, 1}
    };
    return Matrix(grid) * translation(-from.x_, -from.y_, -from.z_);
}

std::ostream& operator<<(std::ostream& o, const Matrix& m)
{
    o << std::endl;
    for (size_t i = 0; i < m.height_; i++)
    {
        o << "|";
        for (size_t j = 0; j < m.width_; j++)
            o << m[i][j] << "|";
        if (i != m.height_ - 1)
            o << std::endl;
    }
    return o;
}
