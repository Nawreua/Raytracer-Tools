#include <fstream>

#include "canvas.hh"
#include "intersection.hh"
#include "light.hh"
#include "material.hh"
#include "matrix.hh"
#include "ray.hh"
#include "sphere.hh"
#include "tuple.hh"

int main()
{
    auto sphere = Sphere();
    //sphere.set_transform(scaling(1, 0.5, 1));
    //sphere.set_transform(scaling(0.5, 1, 1));
    //sphere.set_transform(rotation_z(PI / 4) * scaling(0.5, 1, 1));
    //sphere.set_transform(shearing(1, 0, 0, 0, 0, 0) * scaling(0.5, 1, 1));

    sphere.material_ = Material();
    sphere.material_.color_ = Color(0.7, 0.7, 0.7);
    
    sphere.material_.ambient_ = 0;
    //sphere.material_.diffuse_ = 0.4;
    sphere.material_.specular_ = 0;

    auto light_position = point(-20, 0, -10);
    auto light_color = Color(1, 1, 1);

    auto light = PointLight(light_position, light_color);

    auto ray_origin = point(0, 0, -5);
    float wall_z = 10;
    float wall_size = 7.0;

    float canvas_pixels = 100;
    float pixel_size = wall_size / canvas_pixels;
    float half = wall_size / 2;

    auto canvas = Canvas(canvas_pixels, canvas_pixels);

    for (auto y = 0; y < canvas_pixels; y++)
    {
        float world_y = half - pixel_size * y;
        for (auto x = 0; x < canvas_pixels; x++)
        {
            float world_x = -half + pixel_size * x;
            auto position = point(world_x, world_y, wall_z);
            auto ray = Ray(ray_origin, (position - ray_origin).normalize());

            auto xs = sphere.intersect(ray);
            auto h = hit(xs);

            if (h.first)
            {
                auto point = ray.position(h.second.t_);
                auto normal = h.second.object_->normal_at(point);
                auto eye = -ray.direction_;
                auto color =
                    h.second.object_->material_.lighting(light,
                            point, eye, normal);
                canvas.write_pixel(x, y, color);
            }
        }
    }

    std::ofstream f("3DSphere.ppm");
    if (f.is_open())
        f << canvas.canvas_to_ppm();
    return 0;
}
