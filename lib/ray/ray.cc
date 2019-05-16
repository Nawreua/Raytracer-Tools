#include "ray.hh"

Ray::Ray(Tuple origin, Tuple direction)
    : origin_(origin)
    , direction_(direction)
{}

Tuple Ray::position(float t) const
{
    return origin_ + direction_ * t;
}

Ray Ray::transform(const Matrix& m) const
{
    return Ray(m * origin_, m * direction_);
}
