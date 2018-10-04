#pragma once

#include "matrix.hh"
#include "tuple.hh"

class Ray
{
    public:
        Ray(Tuple origin, Tuple direction);

        Tuple position(float t) const;

        Ray transform(const Matrix& m) const;

        Tuple origin_;
        Tuple direction_;
};
