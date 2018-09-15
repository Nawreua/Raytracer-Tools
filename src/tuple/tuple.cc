#include "tuple.hh"

namespace
{
    bool equal(float a, float b)
    {
        return abs(a - b) < EPSILON;
    }
}

Tuple::Tuple(float x, float y, float z, int w)
    : x_(x), y_(y), z_(z), w_(w)
{}

Tuple& Tuple::operator+=(const Tuple& rhs)
{
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    w_ += rhs.w_;
    return *this;
}

Tuple& Tuple::operator-=(const Tuple& rhs)
{
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
    w_ -= rhs.w_;
    return *this;
}

bool is_a_point(const Tuple& t)
{
    return t.w_ == 1;
}

bool is_a_vector(const Tuple& t)
{
    return t.w_ == 0;
}

bool operator==(const Tuple& lhs, const Tuple& rhs)
{
    return equal(lhs.x_, rhs.x_) && equal(lhs.y_, rhs.y_)
        && equal(lhs.z_, rhs.z_) && lhs.w_ == rhs.w_;
}

Tuple operator+(Tuple lhs, const Tuple& rhs)
{
    return lhs += rhs;
}

Tuple operator-(Tuple lhs, const Tuple& rhs)
{
    return lhs -= rhs;
}

Tuple operator-(const Tuple& t)
{
    return Tuple(-t.x_, -t.y_, -t.z_, -t.w_);
}

Tuple point(float x, float y, float z)
{
    return Tuple(x, y, z, 1);
}

Tuple vector(float x, float y, float z)
{
    return Tuple(x, y, z, 0);
}
