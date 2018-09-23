#include "include.hh"

TEST(LightTest, ImplementationTest)
{
    auto intensity = Color(1, 1, 1);
    auto position = point(0, 0, 0);
    auto light = PointLight(position, intensity);
    ASSERT_EQ(light.position_, position);
    ASSERT_EQ(light.intensity_, intensity);
}
