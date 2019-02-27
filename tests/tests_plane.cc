#include "include.hh"

TEST(PlaneTest, NormalOfPlaneConstantEverywhere)
{
    auto p = Plane();
    auto n1 = p.local_normal_at(point(0, 0, 0));
    auto n2 = p.local_normal_at(point(10, 0, -10));
    auto n3 = p.local_normal_at(point(-5, 0, 150));
    ASSERT_EQ(n1, vector(0, 1, 0));
    ASSERT_EQ(n2, vector(0, 1, 0));
    ASSERT_EQ(n3, vector(0, 1, 0));
}

TEST(PlaneTest, IntersectWithRayParallelToPlane)
{
    auto p = Plane();
    auto r = Ray(point(0, 10, 0), vector(0, 0, 1));
    auto xs = p.local_intersect(r);
    ASSERT_EQ(xs.size(), 0);
}

TEST(PlaneTest, IntersectWithCoplanarRay)
{
    auto p = Plane();
    auto r = Ray(point(0, 0, 0), vector(0, 0, 1));
    auto xs = p.local_intersect(r);
    ASSERT_EQ(xs.size(), 0);
}

TEST(PlaneTest, RayIntersectingPlaneFromAbove)
{
    auto p = Plane();
    auto r = Ray(point(0, 1, 0), vector(0, -1, 0));
    auto xs = p.local_intersect(r);
    ASSERT_EQ(xs.size(), 1);
    ASSERT_EQ(xs[0].t_, 1);
    ASSERT_EQ(&*xs[0].object_, &p);
}

TEST(PlaneTest, RayIntersectingPlaneFromBelow)
{
    auto p = Plane();
    auto r = Ray(point(0, -1, 0), vector(0, 1, 0));
    auto xs = p.local_intersect(r);
    ASSERT_EQ(xs.size(), 1);
    ASSERT_EQ(xs[0].t_, 1);
    ASSERT_EQ(&*xs[0].object_, &p);
}
