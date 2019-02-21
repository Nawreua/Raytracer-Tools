#pragma once

#include "constants.hh"
#include "color.hh"
#include "light.hh"

class Material
{
    public:
        Material();

        Color lighting(const PointLight& light, const Tuple& point,
                const Tuple& eyev, const Tuple& normalv, bool in_shadow);

        Color color_;
        float ambient_;
        float diffuse_;
        float specular_;
        float shininess_;
};

bool operator==(const Material& lhs, const Material& rhs);
