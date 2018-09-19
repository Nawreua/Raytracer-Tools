#pragma once

#include <cmath>

#include "constants.hh"
#include "tuple.hh"

class Matrix
{
    public:
        Matrix();
        Matrix(size_t height, size_t width);
        explicit Matrix(float grid[2][2]);
        explicit Matrix(float grid[3][3]);
        explicit Matrix(float grid[4][4]);

        ~Matrix();

        Matrix transpose() const;
        float determinant() const;
        Matrix submatrix(size_t row, size_t col) const;
        float minor(size_t row, size_t col) const;
        float cofactor(size_t row, size_t col) const;
        
        bool is_invertible() const;
        Matrix inverse() const;

        // BEWARE: Only 4*4 identity matrix
        static const Matrix identity_matrix();

        float *operator[](size_t i);
        float *operator[](size_t i) const;

        size_t height_;
        size_t width_;

    private:
        float **grid_;
};

bool operator==(const Matrix& A, const Matrix& B);

// BEWARE: Only for 4 * 4 matrices
Matrix operator*(const Matrix& A, const Matrix& B);

Tuple operator*(const Matrix& A, const Tuple& b);
