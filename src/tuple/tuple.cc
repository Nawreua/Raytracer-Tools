#include "tuple.hh"

namespace
{
    bool equal(float a, float b)
    {
        return abs(a - b) < EPSILON;
    }
}

Tuple::Tuple(float x, float y, float z, float w)
    : x_(x), y_(y), z_(z), w_(w)
{}

float Tuple::magnitude() const
{
    return sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
}

Tuple Tuple::normalize() const
{
    auto magn = magnitude();
    return Tuple(x_ / magn, y_ / magn, z_ / magn, w_ / magn);
}

Tuple Tuple::reflect(const Tuple& normal) const
{
    return *this - normal * 2 * dot(*this, normal);
}

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

Tuple& Tuple::operator*=(float rhs)
{
    x_ *= rhs;
    y_ *= rhs;
    z_ *= rhs;
    w_ *= rhs;
    return *this;
}

Tuple& Tuple::operator/=(float rhs)
{
    x_ /= rhs;
    y_ /= rhs;
    z_ /= rhs;
    w_ /= rhs;
    return *this;
}

float dot(const Tuple& a, const Tuple& b)
{
    return a.x_ * b.x_ + a.y_ * b.y_ + a.z_ * b.z_ + a.w_ * b.w_;
}

Tuple cross(const Tuple& a, const Tuple& b)
{
    return vector(a.y_ * b.z_ - a.z_ * b.y_,
            a.z_ * b.x_ - a.x_ * b.z_,
            a.x_ * b.y_ - a.y_ * b.x_);
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
        && equal(lhs.z_, rhs.z_) && equal(lhs.w_, rhs.w_);
}

Tuple operator+(Tuple lhs, const Tuple& rhs)
{
    return lhs += rhs;
}

Tuple operator-(Tuple lhs, const Tuple& rhs)
{
    return lhs -= rhs;
}

Tuple operator*(Tuple lhs, float rhs)
{
    return lhs *= rhs;
}

Tuple operator/(Tuple lhs, float rhs)
{
    return lhs /= rhs;
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

Tuple tuple(float x, float y, float z, float w)
{
    return Tuple(x, y, z, w);
}
