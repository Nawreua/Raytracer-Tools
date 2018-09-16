#include "include.hh"

TEST(CanvasTest, CanvasCreation)
{
    auto c = Canvas(10, 20);
    ASSERT_EQ(c.width_, 10);
    ASSERT_EQ(c.height_, 20);
    for (size_t i = 0; i < c.width_; i++)
        for (size_t j = 0; j < c.height_; j++)
            ASSERT_EQ(c.pixel_at(i, j), color(0, 0, 0));
}

TEST(CanvasTest, CanvasWriting)
{
    auto c = Canvas(10, 20);
    auto red = Color(1, 0, 0);
    c.write_pixel(2, 3, red);
    ASSERT_EQ(c.pixel_at(2, 3), red);
}

TEST(CanvasTest, PPMHeader)
{
    auto c = Canvas(5, 3);
    auto ppm = c.canvas_to_ppm();
    auto header = "P3\n5 3\n255\n";
    ASSERT_NE(ppm.find(header), std::string::npos);
}

TEST(CanvasTest, PPMPixelData)
{
    auto c = Canvas(5, 3);
    auto c1 = color(1.5, 0, 0);
    auto c2 = color(0, 0.5, 0);
    auto c3 = color(-0.5, 0, 1);
    c.write_pixel(0, 0, c1);
    c.write_pixel(2, 1, c2);
    c.write_pixel(4, 2, c3);
    auto ppm = c.canvas_to_ppm();
    auto pixel_data = "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
    ASSERT_NE(ppm.find(pixel_data), std::string::npos);
}

TEST(CanvasTest, PPMLongLines)
{
    auto c = Canvas(10, 2);
    for (size_t i = 0; i < c.width_; i++)
        for (size_t j = 0; j < c.height_; j++)
            c.write_pixel(i, j, Color(1, 0.8, 0.6));
    auto ppm = c.canvas_to_ppm();
    auto long_lines =
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
    ASSERT_NE(ppm.find(long_lines), std::string::npos);
}

TEST(CanvasTest, PPMNewlineTerminated)
{
    auto c = Canvas(5, 3);
    auto ppm = c.canvas_to_ppm();
    ASSERT_EQ(*(ppm.rbegin()), '\n');
}
