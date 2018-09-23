#include "include.hh"

TEST(MaterialTest, DefaultMaterial)
{
    auto m = Material();
    ASSERT_EQ(m.color_, Color(1, 1, 1));
    ASSERT_FLOAT_EQ(m.ambient_, 0.1);
    ASSERT_FLOAT_EQ(m.diffuse_, 0.9);
    ASSERT_FLOAT_EQ(m.specular_, 0.9);
    ASSERT_FLOAT_EQ(m.shininess_, 200);
}


TEST(MaterialTest, LightingWithEyeBetweenLightAndSurface)
{
    auto m = Material();
    auto position = point(0, 0, 0);
    auto eyev = vector(0, 0, -1);
    auto normalv = vector(0, 0, -1);
    auto light = PointLight(point(0, 0, -10), Color(1, 1, 1));
    auto result = m.lighting(light, position, eyev, normalv);
    ASSERT_EQ(result, Color(1.9, 1.9, 1.9));
}

TEST(MaterialTest, LightingWithEyeBetweenLightAndSurfaceEyeOffset45)
{
    auto m = Material();
    auto position = point(0, 0, 0);
    auto eyev = vector(0, sqrt(2) / 2, -sqrt(2) / 2);
    auto normalv = vector(0, 0, -1);
    auto light = PointLight(point(0, 0, -10), Color(1, 1, 1));
    auto result = m.lighting(light, position, eyev, normalv);
    ASSERT_EQ(result, Color(1.0, 1.0, 1.0));
}

TEST(MaterialTest, LightingWithEyeOppositeSurfaceLightOffset45)
{
    auto m = Material();
    auto position = point(0, 0, 0);
    auto eyev = vector(0, 0, -1);
    auto normalv = vector(0, 0, -1);
    auto light = PointLight(point(0, 10, -10), Color(1, 1, 1));
    auto result = m.lighting(light, position, eyev, normalv);
    ASSERT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

TEST(MaterialTest, LightingWithEyeInPathReflectionVector)
{
    auto m = Material();
    auto position = point(0, 0, 0);
    auto eyev = vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
    auto normalv = vector(0, 0, -1);
    auto light = PointLight(point(0, 10, -10), Color(1, 1, 1));
    auto result = m.lighting(light, position, eyev, normalv);
    ASSERT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

TEST(MaterialTest, LightingWithLightBehindSurface)
{
    auto m = Material();
    auto position = point(0, 0, 0);
    auto eyev = vector(0, 0, -1);
    auto normalv = vector(0, 0, -1);
    auto light = PointLight(point(0, 0, 10), Color(1, 1, 1));
    auto result = m.lighting(light, position, eyev, normalv);
    ASSERT_EQ(result, Color(0.1, 0.1, 0.1));
}
