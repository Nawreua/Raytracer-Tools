#pragma once

#include <vector>

#include "intersection.hh"
#include "material.hh"
#include "matrix.hh"
#include "ray.hh"

class Shape
{
public:
    Shape();

    std::vector<Intersection> intersect(const Ray& ray);
    Tuple normal_at(const Tuple& p);

    virtual std::vector<Intersection> local_intersect(const Ray& ray) = 0;
    virtual Tuple local_normal_at(const Tuple& p) = 0;

    void set_transform(const Matrix& t);

    Material material_;
    Matrix transform_;
};

bool operator==(const Shape& lhs, const Shape& rhs);

class TestShape : public Shape
{
public:
    TestShape() = default;

    std::vector<Intersection> local_intersect(const Ray& ray) override;
    Tuple local_normal_at(const Tuple& p) override;

    Ray saved_ray_;
};
