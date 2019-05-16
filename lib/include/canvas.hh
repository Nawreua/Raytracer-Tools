#pragma once

#include <string>
#include <vector>

#include "color.hh"

class Canvas
{
public:
    Canvas(size_t width, size_t height);

    void write_pixel(size_t x, size_t y, const Color& color);
    Color pixel_at(size_t x, size_t y);

    std::string canvas_to_ppm();

    size_t width_;
    size_t height_;

private:
    std::vector<std::vector<Color>> grid_;
};
