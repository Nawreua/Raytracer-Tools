#include "light.hh"

PointLight::PointLight(const Tuple& position, const Color& intensity)
    : position_(position), intensity_(intensity)
{}
