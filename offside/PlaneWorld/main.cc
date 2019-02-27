#include <fstream>

#include "camera.hh"
#include "canvas.hh"
#include "intersection.hh"
#include "light.hh"
#include "material.hh"
#include "matrix.hh"
#include "plane.hh"
#include "ray.hh"
#include "shape.hh"
#include "sphere.hh"
#include "tuple.hh"

int main()
{
    auto world = World();
    world.lights_.push_back(PointLight(point(-10, 10, -10), Color(1, 1, 1)));

    auto floor = std::make_shared<Plane>();
    floor->set_transform(scaling(10, 0.01, 10));
    floor->material_ = Material();
    floor->material_.color_ = Color(1, 0.9, 0.9);
    floor->material_.specular_ = 0;

    world.objects_.push_back(floor);

    auto middle = std::make_shared<Sphere>();
    middle->set_transform(translation(-0.5, 1, 0.5));
    middle->material_ = Material();
    middle->material_.color_ = Color(0.1, 1, 0.5);
    middle->material_.diffuse_ = 0.7;
    middle->material_.specular_ = 0.3;

    world.objects_.push_back(middle);

    auto right = std::make_shared<Sphere>();
    right->set_transform(translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5));
    right->material_ = Material();
    right->material_.color_ = Color(0.5, 1, 0.1);
    right->material_.diffuse_ = 0.7;
    right->material_.specular_ = 0.3;

    world.objects_.push_back(right);

    auto left = std::make_shared<Sphere>();
    left->set_transform(translation(-1.5, 0.33, -0.75)
            * scaling(0.33, 0.33, 0.33));
    left->material_ = Material();
    left->material_.color_ = Color(1, 0.8, 0.1);
    left->material_.diffuse_ = 0.7;
    left->material_.specular_ = 0.3;

    world.objects_.push_back(left);

    auto camera = Camera(341, 192, PI / 2);
    camera.transform_ = view_transform(point(0, 1.5, -3), point(0, 1, 0),
            vector(0, 1, 0));

    auto canvas = camera.render(world);

    std::ofstream f("PlaneWorld.ppm");
    if (f.is_open())
        f << canvas.canvas_to_ppm();
    return 0;
}
