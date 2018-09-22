#pragma once

#include <initializer_list>
#include <utility>
#include <vector>

class Sphere;

class Intersection
{
    public:
        Intersection() = default;
        Intersection(float t, Sphere& object);

        float t_;
        Sphere *object_;

};

bool operator==(const Intersection& lhs, const Intersection& rhs);

std::vector<Intersection>
intersections(std::initializer_list<Intersection> list);

std::pair<bool, Intersection> hit(std::vector<Intersection> list);
