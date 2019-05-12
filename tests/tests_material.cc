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
    auto result = m.lighting(Sphere(), light, position, eyev, normalv, false);
    ASSERT_EQ(result, Color(1.9, 1.9, 1.9));
}

TEST(MaterialTest, LightingWithEyeBetweenLightAndSurfaceEyeOffset45)
{
    auto m = Material();
    auto position = point(0, 0, 0);
    auto eyev = vector(0, sqrt(2) / 2, -sqrt(2) / 2);
    auto normalv = vector(0, 0, -1);
    auto light = PointLight(point(0, 0, -10), Color(1, 1, 1));
    auto result = m.lighting(Sphere(), light, position, eyev, normalv, false);
    ASSERT_EQ(result, Color(1.0, 1.0, 1.0));
}

TEST(MaterialTest, LightingWithEyeOppositeSurfaceLightOffset45)
{
    auto m = Material();
    auto position = point(0, 0, 0);
    auto eyev = vector(0, 0, -1);
    auto normalv = vector(0, 0, -1);
    auto light = PointLight(point(0, 10, -10), Color(1, 1, 1));
    auto result = m.lighting(Sphere(), light, position, eyev, normalv, false);
    ASSERT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

TEST(MaterialTest, LightingWithEyeInPathReflectionVector)
{
    auto m = Material();
    auto position = point(0, 0, 0);
    auto eyev = vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
    auto normalv = vector(0, 0, -1);
    auto light = PointLight(point(0, 10, -10), Color(1, 1, 1));
    auto result = m.lighting(Sphere(), light, position, eyev, normalv, false);
    ASSERT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

TEST(MaterialTest, LightingWithLightBehindSurface)
{
    auto m = Material();
    auto position = point(0, 0, 0);
    auto eyev = vector(0, 0, -1);
    auto normalv = vector(0, 0, -1);
    auto light = PointLight(point(0, 0, 10), Color(1, 1, 1));
    auto result = m.lighting(Sphere(), light, position, eyev, normalv, false);
    ASSERT_EQ(result, Color(0.1, 0.1, 0.1));
}

TEST(MaterialTest, LightingWithSurfaceInShadow)
{
    auto m = Material();
    auto position = point(0, 0, 0);
    auto eyev = vector(0, 0, -1);
    auto normalv = vector(0, 0, -1);
    auto light = PointLight(point(0, 0, -10), Color(1, 1, 1));
    auto in_shadow = true;
    auto result = m.lighting(Sphere(), light, position, eyev, normalv,
            in_shadow);
    ASSERT_EQ(result, Color(0.1, 0.1, 0.1));
}

TEST(MaterialTest, LightingWithPatternApplied)
{
    auto m = Material();
    m.pattern_ =
        std::make_shared<StripePattern>(StripePattern(Color(1, 1, 1), Color(0, 0, 0)));
    m.ambient_ = 1;
    m.diffuse_ = 0;
    m.specular_ = 0;
    auto eyev = vector(0, 0, -1);
    auto normalv = vector(0, 0, -1);
    auto light = PointLight(point(0, 0, -10), Color(1, 1, 1));
    auto c1 = m.lighting(Sphere(), light, point(0.9, 0, 0), eyev, normalv,
            false);
    auto c2 = m.lighting(Sphere(), light, point(1.1, 0, 0), eyev, normalv,
            false);
    ASSERT_EQ(c1, Color(1, 1, 1));
    ASSERT_EQ(c2, Color(0, 0, 0));
}
