#include <fstream>

#include "canvas.hh"
#include "matrix.hh"

int main()
{
    auto canvas = Canvas(500, 500);
    auto origin = point(0, 0, 0);
    origin.x_ += canvas.width_ / 2;
    origin.z_ += canvas.height_ / 2;
    auto hour = point(0, 0, 1);
    auto r = rotation_y(PI / 6);
    float radius = 3.0 / 8.0 * canvas.width_;
    Color white{1, 1, 1};
    for (auto i = 1; i <= 12; i++)
    {
        hour = r * hour;
        canvas.write_pixel(hour.z_ * radius + origin.z_,
                hour.x_ * radius + origin.x_, white);
    }
    std::ofstream f("clock.ppm");
    if (f.is_open())
        f << canvas.canvas_to_ppm();
    return 0;
}
