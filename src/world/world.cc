#include "world.hh"

#include "sphere.hh"

std::vector<Intersection> World::intersect_world(const Ray& ray)
{
    std::vector<Intersection> res;
    for (auto object : objects_)
    {
        auto xs = object->intersect(ray);
        for (auto x : xs)
            res.push_back(x);
    }
    std::sort(res.begin(), res.end());
    return res;
}

Color World::shade_hit(const Intersection& hit)
{
    Color res{0.0, 0.0, 0.0};
    std::for_each(lights_.begin(), lights_.end(), [&](const PointLight& light) {
        res += hit.object_->material_.lighting(
            *hit.object_, light, hit.point_, hit.eyev_, hit.normalv_,
            is_shadowed(hit.over_point_, light));
    });
    return res;
}

Color World::color_at(const Ray& ray)
{
    auto xs = intersect_world(ray);
    auto h = hit(xs);
    if (!h.first)
        return Color(0.0, 0.0, 0.0);
    h.second.prepare_hit(ray);
    return shade_hit(h.second);
}

bool World::is_shadowed(const Tuple& point, const PointLight& light)
{
    auto v = light.position_ - point;
    auto distance = v.magnitude();
    auto direction = v.normalize();

    auto r = Ray(point, direction);
    auto intersections = intersect_world(r);

    auto h = hit(intersections);
    return h.first && h.second.t_ < distance;
}

World World::default_world()
{
    World world;
    world.lights_.push_back(PointLight(point(-10, 10, -10), Color(1, 1, 1)));
    auto s1 = std::make_shared<Sphere>();
    auto s2 = std::make_shared<Sphere>();
    s1->material_.color_ = Color(0.8, 1.0, 0.6);
    s1->material_.diffuse_ = 0.7;
    s1->material_.specular_ = 0.2;
    s2->set_transform(scaling(0.5, 0.5, 0.5));
    world.objects_.push_back(s1);
    world.objects_.push_back(s2);
    return world;
}
