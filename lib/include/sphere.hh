#pragma once

#include "shape.hh"

class Sphere : public Shape
{
public:
    Sphere() = default;

    std::vector<Intersection> local_intersect(const Ray& ray) override;
    Tuple local_normal_at(const Tuple& p) override;

    static Sphere glass_sphere();
};

// bool operator==(const Sphere& lhs, const Sphere& rhs);
