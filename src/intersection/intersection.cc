#include "intersection.hh"
#include "sphere.hh"

#include <iostream>

namespace
{
    bool equal(float a, float b)
    {
        return abs(a - b) < EPSILON;
    }
}

Intersection::Intersection(float t, Sphere& object)
    : t_(t), object_(&object)
{}

bool operator==(const Intersection& lhs, const Intersection& rhs)
{
    return equal(lhs.t_, rhs.t_) && lhs.object_ == rhs.object_;
}

std::vector<Intersection>
intersections(std::initializer_list<Intersection> list)
{
    std::vector<Intersection> res;
    for (auto elem : list)
        res.push_back(elem);
    return res;
}

std::pair<bool, Intersection> hit(std::vector<Intersection> list)
{
    Intersection *res = nullptr;
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if (it->t_ >= 0)
        {
            if (!res)
                res = &(*it);
            else
                if (it->t_ < res->t_)
                    res = &(*it);
        }
    }
    if (res)
        return std::make_pair(true, *res);
    return std::make_pair(false, Intersection());
}