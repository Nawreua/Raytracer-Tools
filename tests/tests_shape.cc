#include "include.hh"

TEST(ShapeTest, DefaultTransformation)
{
    auto s = TestShape();
    ASSERT_EQ(s.transform_, Matrix::identity_matrix());
}

TEST(ShapeTest, AssigningTransformation)
{
    auto s = TestShape();
    s.set_transform(translation(2, 3, 4));
    ASSERT_EQ(s.transform_, translation(2, 3, 4));
}

TEST(ShapeTest, DefaultMaterial)
{
    auto s = TestShape();
    auto m = s.material_;
    ASSERT_EQ(m, Material());
}

TEST(ShapeTest, AssigningMaterial)
{
    auto s = TestShape();
    auto m = Material();
    m.ambient_ = 1;
    s.material_ = m;
    ASSERT_EQ(s.material_, m);
}

TEST(ShapeTest, IntersectingScaledShapeWithRay)
{
    auto r = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = TestShape();
    s.set_transform(scaling(2, 2, 2));
    auto xs = s.intersect(r);
    ASSERT_EQ(s.saved_ray_.origin_, point(0, 0, -2.5));
    ASSERT_EQ(s.saved_ray_.direction_, vector(0, 0, 0.5));
}

TEST(ShapeTest, IntersectingTranslatedShapeWithRay)
{
    auto r = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = TestShape();
    s.set_transform(translation(5, 0, 0));
    auto xs = s.intersect(r);
    ASSERT_EQ(s.saved_ray_.origin_, point(-5, 0, -5));
    ASSERT_EQ(s.saved_ray_.direction_, vector(0, 0, 1));
}

TEST(ShapeTest, ComputingNormalOnTranslatedShape)
{
    auto s = TestShape();
    s.set_transform(translation(0, 1, 0));
    auto n = s.normal_at(point(0, 1.70711, -0.70711));
    ASSERT_EQ(n, vector(0, 0.70711, -0.707711));
}

TEST(ShapeTest, ComputingNormalOnTransformedShape)
{
    auto s = TestShape();
    s.set_transform(scaling(1, 0.5, 1) * rotation_z(PI / 5));
    auto n = s.normal_at(point(0, sqrt(2) / 2, -sqrt(2) / 2));
    ASSERT_EQ(n, vector(0, 0.97014, -0.24254));
}
