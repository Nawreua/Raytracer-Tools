#include "canvas.hh"

Canvas::Canvas(size_t width, size_t height)
    : width_(width), height_(height)
{
    grid_ = std::vector<std::vector<Color>>(width);
    for (size_t i = 0; i < width; i++)
    {
        grid_[i].resize(height);
        for (size_t j = 0; j < height; j++)
            grid_[i][j] = Color(0, 0, 0);
    }
}

void Canvas::write_pixel(size_t x, size_t y, const Color& color)
{
    grid_[x][y] = color;
}

Color Canvas::pixel_at(size_t x, size_t y)
{
    return grid_[x][y];
}

namespace
{
    int clamp(int color)
    {
        if (color > 255)
            return 255;
        if (color < 0)
            return 0;
        return color;
    }
}

std::string Canvas::canvas_to_ppm()
{
    std::string ppm = "P3\n" + std::to_string(width_)
        + " " + std::to_string(height_) + "\n255\n";
    for (size_t j = 0; j < height_; j++)
    {
        auto length = 0;
        for (size_t i = 0; i < width_; i++)
        {
            auto col = grid_[i][j];
            auto red_string = std::to_string(clamp(col.red_ * 256));
            if (length + red_string.length() >= 70)
            {
                if (*ppm.rbegin() == ' ')
                    ppm.pop_back();
                ppm.append("\n");
                length = 0;
            }
            ppm.append(red_string);
            ppm.append(" ");
            length += red_string.length() + 1;
            auto green_string = std::to_string(clamp(col.green_ * 256));
            if (length + green_string.length() >= 70)
            {
                if (*ppm.rbegin() == ' ')
                    ppm.pop_back();
                ppm.append("\n");
                length = 0;
            }
            ppm.append(green_string);
            ppm.append(" ");
            length += green_string.length() + 1;
            auto blue_string = std::to_string(clamp(col.blue_ * 256));
            if (length + blue_string.length() >= 70)
            {
                if (*ppm.rbegin() == ' ')
                    ppm.pop_back();
                ppm.append("\n");
                length = 0;
            }
            ppm.append(blue_string);
            ppm.append(" ");
            length += blue_string.length() + 1;
        }
        ppm.pop_back();
        ppm.append("\n");
    }
    return ppm;
}
