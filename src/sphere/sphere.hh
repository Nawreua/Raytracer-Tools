#pragma once

#include <vector>

#include "intersection.hh"
#include "material.hh"
#include "matrix.hh"
#include "ray.hh"

class Sphere
{
    public:
        Sphere();

        std::vector<Intersection> intersect(const Ray& ray);
        Tuple normal_at(const Tuple& p);

        void set_transform(const Matrix& t);

        Material material_;

        std::shared_ptr<Matrix> transform_;
};

bool operator==(const Sphere& lhs, const Sphere& rhs);
