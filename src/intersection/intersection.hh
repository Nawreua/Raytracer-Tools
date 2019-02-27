#pragma once

#include <initializer_list>
#include <utility>
#include <vector>

#include "ray.hh"
#include "tuple.hh"

class Shape;

class Intersection
{
    public:
        Intersection() = default;
        Intersection(float t, Shape& object);

        void prepare_hit(const Ray& ray);

        float t_;
        Shape *object_;

        Tuple point_;
        Tuple over_point_;
        Tuple eyev_;
        Tuple normalv_;
        bool inside_;

};

bool operator<(const Intersection& lhs, const Intersection& rhs);
bool operator==(const Intersection& lhs, const Intersection& rhs);

std::vector<Intersection>
intersections(std::initializer_list<Intersection> list);

std::pair<bool, Intersection> hit(std::vector<Intersection> list);
