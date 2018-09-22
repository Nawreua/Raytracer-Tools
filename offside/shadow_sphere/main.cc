#include <fstream>

#include "canvas.hh"
#include "intersection.hh"
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
    sphere.set_transform(shearing(1, 0, 0, 0, 0, 0) * scaling(0.5, 1, 1));

    auto ray_origin = point(0, 0, -5);
    float wall_z = 10;
    float wall_size = 7.0;

    float canvas_pixels = 100;
    float pixel_size = wall_size / canvas_pixels;
    float half = wall_size / 2;

    auto canvas = Canvas(canvas_pixels, canvas_pixels);
    auto color = Color(1, 0, 0);

    for (auto y = 0; y < canvas_pixels; y++)
    {
        float world_y = half - pixel_size * y;
        for (auto x = 0; x < canvas_pixels; x++)
        {
            float world_x = -half + pixel_size * x;
            auto position = point(world_x, world_y, wall_z);
            auto r = Ray(ray_origin, (position - ray_origin).normalize());

            auto xs = sphere.intersect(r);

            if (hit(xs).first)
                canvas.write_pixel(x, y, color);
        }
    }

    std::ofstream f("sphere.ppm");
    if (f.is_open())
        f << canvas.canvas_to_ppm();
    return 0;
}
