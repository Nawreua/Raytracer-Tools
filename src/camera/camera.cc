#include "camera.hh"

#include <iostream>

Camera::Camera(size_t hsize, size_t vsize, float field_of_view)
    : hsize_(hsize)
    , vsize_(vsize)
    , field_of_view_(field_of_view)
    , transform_(Matrix::identity_matrix())
{
    float half_view = tan(field_of_view / 2);
    float aspect = (float)hsize / (float)vsize;
    if (aspect >= 1)
    {
        half_width_ = half_view;
        half_height_ = half_view / aspect;
    }
    else
    {
        half_width_ = half_view * aspect;
        half_height_ = half_view;
    }
    pixel_size_ = (half_width_ * 2) / hsize;
}

Ray Camera::ray_for_pixel(size_t px, size_t py)
{
    float xoffset = (px + 0.5) * pixel_size_;
    float yoffset = (py + 0.5) * pixel_size_;

    float world_x = half_width_ - xoffset;
    float world_y = half_height_ - yoffset;

    auto pixel = transform_.inverse() * point(world_x, world_y, -1);
    auto origin = transform_.inverse() * point(0, 0, 0);
    auto direction = (pixel - origin).normalize();

    return Ray(origin, direction);
}

Canvas Camera::render(World& world)
{
    auto image = Canvas(hsize_, vsize_);

    for (size_t y = 0; y < vsize_; y++)
        for (size_t x = 0; x < hsize_; x++)
        {
            auto ray = ray_for_pixel(x, y);
            auto color = world.color_at(ray);
            image.write_pixel(x, y, color);
        }

    return image;
}

Canvas Camera::render_and_report(World& world)
{
    auto image = Canvas(hsize_, vsize_);

    float count = 0;
    for (size_t y = 0; y < vsize_; y++)
        for (size_t x = 0; x < hsize_; x++)
        {
            auto ray = ray_for_pixel(x, y);
            auto color = world.color_at(ray);
            image.write_pixel(x, y, color);
            std::cout << ((count++) / static_cast<float>(vsize_ * hsize_)) * 100
                      << "%\r";
        }

    std::cout << "100%\n";
    return image;
}
