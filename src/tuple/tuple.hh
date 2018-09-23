#pragma once

#include <cmath>

#include "constants.hh"

class Tuple
{
    public:
        Tuple(float x, float y, float z, float w);

        float magnitude() const;
        Tuple normalize() const;

        Tuple reflect(const Tuple& normal) const;

        Tuple& operator+=(const Tuple& rhs);
        Tuple& operator-=(const Tuple& rhs);
        Tuple& operator*=(float rhs);
        Tuple& operator/=(float rhs);

        float x_;
        float y_;
        float z_;
        float w_;
};

bool is_a_point(const Tuple& t);
bool is_a_vector(const Tuple& t);

bool operator==(const Tuple& lhs, const Tuple& rhs);

Tuple operator+(Tuple lhs, const Tuple& rhs);
Tuple operator-(Tuple lhs, const Tuple& rhs);
Tuple operator*(Tuple lhs, float rhs);
Tuple operator/(Tuple lhs, float rhs);
Tuple operator-(const Tuple& t);

float dot(const Tuple& a, const Tuple& b);
Tuple cross(const Tuple& a, const Tuple& b);

Tuple point(float x, float y, float z);
Tuple vector(float x, float y, float z);
Tuple tuple(float x, float y, float z, float w);
