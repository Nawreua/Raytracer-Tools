#pragma once

#include <algorithm>
#include <vector>

#include "intersection.hh"
#include "light.hh"
#include "sphere.hh"

class World
{
    public:

        std::vector<Intersection> intersect_world(const Ray& ray);
        Color shade_hit(const Intersection& hit);
        Color color_at(const Ray& ray);

        static World default_world();

        std::vector<Sphere> objects_;
        std::vector<PointLight> lights_;
};
