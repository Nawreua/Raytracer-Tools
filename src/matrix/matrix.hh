#pragma once

#include <cmath>
#include <memory>
#include <ostream>
#include <vector>

#include "constants.hh"
#include "tuple.hh"

class Matrix
{
    public:
        Matrix();
        Matrix(const Matrix& m);
        Matrix(Matrix& m);
        Matrix(size_t height, size_t width);
        explicit Matrix(float grid[2][2]);
        explicit Matrix(float grid[3][3]);
        explicit Matrix(float grid[4][4]);

        Matrix transpose() const;
        float determinant() const;
        Matrix submatrix(size_t row, size_t col) const;
        float minor(size_t row, size_t col) const;
        float cofactor(size_t row, size_t col) const;
        
        bool is_invertible() const;
        Matrix inverse() const;

        // BEWARE: Only 4*4 identity matrix
        static Matrix identity_matrix();

        std::vector<float>& operator[](size_t i);
        const std::vector<float>& operator[](size_t i) const;

        size_t height_;
        size_t width_;

    private:
        std::vector<std::vector<float>> grid_;
};

bool operator==(const Matrix& A, const Matrix& B);

// BEWARE: Only for 4 * 4 matrices
Matrix operator*(const Matrix& A, const Matrix& B);

Tuple operator*(const Matrix& A, const Tuple& b);

Matrix translation(float x, float y, float z);
Matrix scaling(float x, float y, float z);
Matrix rotation_x(float r);
Matrix rotation_y(float r);
Matrix rotation_z(float r);
Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy);

std::ostream& operator<<(std::ostream& o, const Matrix& m);
