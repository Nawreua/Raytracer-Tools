#include "light.hh"

PointLight::PointLight(const Tuple& position, const Color& intensity)
    : position_(position), intensity_(intensity)
{}

bool operator==(const PointLight& lhs, const PointLight& rhs)
{
    return lhs.position_ == rhs.position_
        && lhs.intensity_ == rhs.intensity_;
}
