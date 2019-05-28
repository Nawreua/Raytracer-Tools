#include "intersection.hh"

#include <iostream>

#include "sphere.hh"

namespace
{
    constexpr inline bool equal(float a, float b)
    {
        return abs(a - b) < EPSILON;
    }
} // namespace

Intersection::Intersection(float t, Shape& object)
    : t_(t)
    , object_(&object)
{}

void Intersection::prepare_hit(const Ray& ray)
{
    point_ = ray.position(t_);
    eyev_ = -ray.direction_;
    normalv_ = object_->normal_at(point_);
    inside_ = false;
    if (dot(normalv_, eyev_) < 0)
    {
        inside_ = true;
        normalv_ = -normalv_;
    }
    over_point_ = point_ + normalv_ * EPSILON;
}

bool operator<(const Intersection& lhs, const Intersection& rhs)
{
    return lhs.t_ < rhs.t_;
}

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
    Intersection* res = nullptr;
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if (it->t_ >= 0)
        {
            if (!res)
                res = &(*it);
            else if (it->t_ < res->t_)
                res = &(*it);
        }
    }
    if (res)
        return std::make_pair(true, *res);
    return std::make_pair(false, Intersection());
}
