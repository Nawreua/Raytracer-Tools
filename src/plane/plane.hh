#pragma once

#include "shape.hh"

class Plane: public Shape
{
    public:
        Plane() = default;

        std::vector<Intersection> local_intersect(const Ray& ray) override;
        Tuple local_normal_at(const Tuple& p) override;
};
