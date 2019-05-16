#pragma once

#include "canvas.hh"
#include "matrix.hh"
#include "ray.hh"
#include "world.hh"

class Camera
{
public:
    Camera(size_t hsize, size_t vsize, float field_of_view);

    Ray ray_for_pixel(size_t px, size_t py);
    Canvas render(World& world);
    Canvas render_and_report(World& world);

    size_t hsize_;
    size_t vsize_;
    float field_of_view_;
    Matrix transform_;
    float pixel_size_;
    float half_width_;
    float half_height_;
};
