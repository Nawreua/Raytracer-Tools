#pragma once

#include <vector>

#include "intersection.hh"
#include "matrix.hh"
#include "ray.hh"

class Sphere
{
    public:
        Sphere();

        std::vector<Intersection> intersect(const Ray& ray);

        void set_transform(const Matrix& t);

        std::shared_ptr<Matrix> transform_;
};
