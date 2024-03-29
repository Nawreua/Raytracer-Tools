#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "intersection.hh"
#include "light.hh"
#include "shape.hh"

class World
{
public:
    using shared_shape = std::shared_ptr<Shape>;

    std::vector<Intersection> intersect_world(const Ray& ray);
    Color shade_hit(const Intersection& hit, int remaining = 5);
    Color color_at(const Ray& ray, int remaining = 5);
    Color reflected_color(const Intersection& hit, int remaining = 5);
    bool is_shadowed(const Tuple& point, const PointLight& light);

    static World default_world();

    std::vector<shared_shape> objects_;
    std::vector<PointLight> lights_;
};
