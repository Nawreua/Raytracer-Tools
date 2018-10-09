#include "include.hh"

TEST(CameraTest, ConstructingCamera)
{
    size_t hsize = 160;
    size_t vsize = 120;
    float field_of_view = PI / 2;
    auto c = Camera(hsize, vsize, field_of_view);
    ASSERT_EQ(c.hsize_, 160);
    ASSERT_EQ(c.vsize_, 120);
    ASSERT_FLOAT_EQ(c.field_of_view_, PI / 2);
    ASSERT_EQ(c.transform_, Matrix::identity_matrix());
}

TEST(CameraTest, PixelSizeHorizontalCanvas)
{
    auto c = Camera(200, 125, PI / 2);
    ASSERT_FLOAT_EQ(c.pixel_size_, 0.01);
}

TEST(CameraTest, PixelSizeVerticalCanvas)
{
    auto c = Camera(125, 200, PI / 2);
    ASSERT_FLOAT_EQ(c.pixel_size_, 0.01);
}

TEST(CameraTest, RayThroughCenterCanvas)
{
    auto c = Camera(201, 101, PI / 2);
    auto r = c.ray_for_pixel(100, 50);
    ASSERT_EQ(r.origin_, point(0, 0, 0));
    ASSERT_EQ(r.direction_, vector(0, 0, -1));
}

TEST(CameraTest, RayThroughCornerCanvas)
{
    auto c = Camera(201, 101, PI / 2);
    auto r = c.ray_for_pixel(0, 0);
    ASSERT_EQ(r.origin_, point(0, 0, 0));
    ASSERT_EQ(r.direction_, vector(0.66519, 0.33259, -0.66851));
}

TEST(CameraTest, RayCameraTransformed)
{
    auto c = Camera(201, 101, PI / 2);
    c.transform_ = rotation_y(PI / 4) * translation(0, -2, 5);
    auto r = c.ray_for_pixel(100, 50);
    ASSERT_EQ(r.origin_, point(0, 2, -5));
    ASSERT_EQ(r.direction_, vector(sqrt(2) / 2, 0, -sqrt(2) / 2));
}

TEST(CameraTest, RenderingWorldWithCamera)
{
    auto w = World::default_world();
    auto c = Camera(11, 11, PI / 2);
    auto from = point(0, 0, -5);
    auto to = point(0, 0, 0);
    auto up = vector(0, 1, 0);
    c.transform_ = view_transform(from, to, up);
    auto image = c.render(w);
    ASSERT_EQ(image.pixel_at(5, 5), Color(0.38066, 0.47583, 0.2855));
}
