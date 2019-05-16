#pragma once

#include "color.hh"
#include "tuple.hh"

class PointLight
{
public:
    PointLight(const Tuple& position, const Color& intensity);

    Tuple position_;
    Color intensity_;
};

bool operator==(const PointLight& lhs, const PointLight& rhs);
