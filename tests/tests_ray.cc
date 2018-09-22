#include "include.hh"

TEST(RayTest, ImplementationTest)
{
    auto origin = point(1, 2, 3);
    auto direction = vector(4, 5, 6);
    auto r = Ray(origin, direction);
    ASSERT_EQ(r.origin_, origin);
    ASSERT_EQ(r.direction_, direction);
}

TEST(RayTest, PointFromDistance)
{
    auto r = Ray(point(2, 3, 4), vector(1, 0, 0));
    ASSERT_EQ(r.position(0), point(2, 3, 4));
    ASSERT_EQ(r.position(1), point(3, 3, 4));
    ASSERT_EQ(r.position(-1), point(1, 3, 4));
    ASSERT_EQ(r.position(2.5), point(4.5, 3, 4));
}

TEST(RayTest, TranslatingRay)
{
    auto r = Ray(point(1, 2, 3), vector(0, 1, 0));
    auto m = translation(3, 4, 5);
    auto r2 = r.transform(m);
    ASSERT_EQ(r2.origin_, point(4, 6, 8));
    ASSERT_EQ(r2.direction_, vector(0, 1, 0));
}

TEST(RayTest, ScalingRay)
{
    auto r = Ray(point(1, 2, 3), vector(0, 1, 0));
    auto m = scaling(2, 3, 4);
    auto r2 = r.transform(m);
    ASSERT_EQ(r2.origin_, point(2, 6, 12));
    ASSERT_EQ(r2.direction_, vector(0, 3, 0));
}
