#include "include.hh"

TEST(SphereTest, SphereIsShape)
{
    auto s = Sphere();
    ASSERT_NE(dynamic_cast<Shape*>(&s), nullptr);
}

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

TEST(SphereTest, NormalSphereAtPointX)
{
    auto s = Sphere();
    auto n = s.normal_at(point(1, 0, 0));
    ASSERT_EQ(n, vector(1, 0, 0));
}

TEST(SphereTest, NormalSphereAtPointY)
{
    auto s = Sphere();
    auto n = s.normal_at(point(0, 1, 0));
    ASSERT_EQ(n, vector(0, 1, 0));
}

TEST(SphereTest, NormalSphereAtPointZ)
{
    auto s = Sphere();
    auto n = s.normal_at(point(0, 0, 1));
    ASSERT_EQ(n, vector(0, 0, 1));
}

TEST(SphereTest, NormalSphereAtPointNonAxial)
{
    auto s = Sphere();
    auto n = s.normal_at(point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    ASSERT_EQ(n, vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
}

TEST(SphereTest, NormalIsNormalized)
{
    auto s = Sphere();
    auto n = s.normal_at(point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    ASSERT_EQ(n, n.normalize());
}

TEST(SphereTest, NormalOnTranslatedSphere)
{
    auto s = Sphere();
    s.set_transform(translation(0, 1, 0));
    auto n = s.normal_at(point(0, 1.70711, -0.70711));
    ASSERT_EQ(n, vector(0, 0.70711, -0.70711));
}

TEST(SphereTest, NormalOnScaledSphere)
{
    auto s = Sphere();
    s.set_transform(scaling(1, 0.5, 1));
    auto n = s.normal_at(point(0, sqrt(2) / 2, -sqrt(2) / 2));
    ASSERT_EQ(n, vector(0, 0.97014, -0.24254));
}

TEST(SphereTest, HelperForProducingSphereWithGlassyMaterial)
{
    auto s = Sphere::glass_sphere();
    ASSERT_EQ(s.transform_, Matrix::identity_matrix());
    ASSERT_FLOAT_EQ(s.material_.transparency_, 1.0);
    ASSERT_FLOAT_EQ(s.material_.refractive_index_, 1.5);
}
