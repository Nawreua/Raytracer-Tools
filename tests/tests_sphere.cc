#include "include.hh"

TEST(SphereTest, RayIntersectSphere)
{
    auto r = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = Sphere();
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].t_, 4);
    ASSERT_FLOAT_EQ(xs[1].t_, 6);
}

TEST(SphereTest, RayIntersectSphereTangent)
{
    auto r = Ray(point(0, 1, -5), vector(0, 0, 1));
    auto s = Sphere();
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].t_, 5);
    ASSERT_FLOAT_EQ(xs[1].t_, 5);
}

TEST(SphereTest, RayMissesSphere)
{
    auto r = Ray(point(0, 2, -5), vector(0, 0, 1));
    auto s = Sphere();
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 0);
}

TEST(SphereTest, RayInsideSphere)
{
    auto r = Ray(point(0, 0, 0), vector(0, 0, 1));
    auto s = Sphere();
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].t_, -1);
    ASSERT_FLOAT_EQ(xs[1].t_, 1);
}

TEST(SphereTest, SphereBehindRay)
{
    auto r = Ray(point(0, 0, 5), vector(0, 0, 1));
    auto s = Sphere();
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].t_, -6);
    ASSERT_FLOAT_EQ(xs[1].t_, -4);
}

TEST(SphereTest, IntersectSetObjectOnIntersection)
{
    auto r = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = Sphere();
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].object_, &s);
    ASSERT_EQ(xs[1].object_, &s);
}

TEST(SphereTest, DefaultSphereTransformation)
{
    auto s = Sphere();
    ASSERT_EQ(*s.transform_, Matrix::identity_matrix());
}

TEST(SphereTest, ChangingSphereTransformation)
{
    auto s = Sphere();
    auto t = translation(2, 3, 4);
    s.set_transform(t);
    ASSERT_EQ(*s.transform_, t);
}

TEST(SphereTest, IntersectingScaledSphereWithRay)
{
    auto r = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = Sphere();
    s.set_transform(scaling(2, 2, 2));
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].t_, 3);
    ASSERT_FLOAT_EQ(xs[1].t_, 7);
}

TEST(SphereTest, IntersectingTranslatedSphereWithRay)
{
    auto r = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = Sphere();
    s.set_transform(translation(5, 0, 0));
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 0);
}
