#pragma once

#include <optional>

#include "color.hh"
#include "constants.hh"
#include "light.hh"
#include "pattern.hh"

class Shape;

class Material
{
public:
    Material();

    Color lighting(const Shape& object, const PointLight& light,
                   const Tuple& point, const Tuple& eyev, const Tuple& normalv,
                   bool in_shadow);

    Color color_;
    float ambient_;
    float diffuse_;
    float specular_;
    float shininess_;
    std::shared_ptr<Pattern> pattern_;
};

bool operator==(const Material& lhs, const Material& rhs);
