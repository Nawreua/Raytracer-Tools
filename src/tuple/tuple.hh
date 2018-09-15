#pragma once

#include <cmath>

#include "constants.hh"

class Tuple
{
    public:
        Tuple(float x, float y, float z, int w);

        Tuple& operator+=(const Tuple& rhs);

        Tuple& operator-=(const Tuple& rhs);

        float x_;
        float y_;
        float z_;
        int w_;
};

bool is_a_point(const Tuple& t);
bool is_a_vector(const Tuple& t);

bool operator==(const Tuple& lhs, const Tuple& rhs);

Tuple operator+(Tuple lhs, const Tuple& rhs);
Tuple operator-(Tuple lhs, const Tuple& rhs);
Tuple operator-(const Tuple& t);

Tuple point(float x, float y, float z);
Tuple vector(float x, float y, float z);
