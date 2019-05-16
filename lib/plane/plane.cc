#include "plane.hh"

std::vector<Intersection> Plane::local_intersect(const Ray& ray)
{
    if (abs(ray.direction_.y_) < EPSILON)
        return std::vector<Intersection>();
    auto t = -ray.origin_.y_ / ray.direction_.y_;
    return std::vector<Intersection>{Intersection(t, *this)}; // FIXME
}

Tuple Plane::local_normal_at(const Tuple&)
{
    return vector(0, 1, 0);
}
