#include "include.hh"

TEST(IntersectionTest, ImplementationTest)
{
    auto s = Sphere();
    auto i = Intersection(3.5, s);
    ASSERT_FLOAT_EQ(i.t_, 3.5);
    ASSERT_EQ(i.object_, &s);
}

TEST(IntersectionTest, AggregationTest)
{
    auto s = Sphere();
    auto i1 = Intersection(1, s);
    auto i2 = Intersection(2, s);
    auto xs = intersections({i1, i2});
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].t_, 1);
    ASSERT_FLOAT_EQ(xs[1].t_, 2);
}

TEST(IntersectionTest, IntersectionsAllPositive)
{
    auto s = Sphere();
    auto i1 = Intersection(1, s);
    auto i2 = Intersection(2, s);
    auto xs = intersections({i2, i1});
    auto h = hit(xs);
    ASSERT_EQ(h.second, i1);
}

TEST(IntersectionTest, IntersectionsSomeNegative)
{
    auto s = Sphere();
    auto i1 = Intersection(-1, s);
    auto i2 = Intersection(1, s);
    auto xs = intersections({i2, i1});
    auto h = hit(xs);
    ASSERT_EQ(h.second, i2);
}

TEST(IntersectionTest, IntersectionsAllNegative)
{
    auto s = Sphere();
    auto i1 = Intersection(-2, s);
    auto i2 = Intersection(-1, s);
    auto xs = intersections({i2, i1});
    auto h = hit(xs);
    ASSERT_FALSE(h.first);
}

TEST(IntersectionTest, HitAlwaysLowestNonNegative)
{
    auto s = Sphere();
    auto i1 = Intersection(5, s);
    auto i2 = Intersection(7, s);
    auto i3 = Intersection(-3, s);
    auto i4 = Intersection(2, s);
    auto xs = intersections({i2, i1, i3, i4});
    auto h = hit(xs);
    ASSERT_EQ(h.second, i4);
}

TEST(IntersectionTest, PrecomputingStateIntersection)
{
    auto ray = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto shape = Sphere();
    auto hit = Intersection(4, shape);
    hit.prepare_hit(ray);
    ASSERT_EQ(hit.point_, point(0, 0, -1));
    ASSERT_EQ(hit.eyev_, vector(0, 0, -1));
    ASSERT_EQ(hit.normalv_, vector(0, 0, -1));
}

TEST(IntersectionTest, IntersectionOccursOutside)
{
    auto ray = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto shape = Sphere();
    auto hit = Intersection(4, shape);
    hit.prepare_hit(ray);
    ASSERT_FALSE(hit.inside_);
}

TEST(IntersectionTest, IntersectionOccursInside)
{
    auto ray = Ray(point(0, 0, 0), vector(0, 0, 1));
    auto shape = Sphere();
    auto hit = Intersection(1, shape);
    hit.prepare_hit(ray);
    ASSERT_EQ(hit.point_, point(0, 0, 1));
    ASSERT_EQ(hit.eyev_, vector(0, 0, -1));
    ASSERT_TRUE(hit.inside_);
    ASSERT_EQ(hit.normalv_, vector(0, 0, -1));
}

TEST(IntersectionTest, HitShouldOffsetPoint)
{
    auto r = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto shape = Sphere();
    shape.transform_ = translation(0, 0, 1);
    auto i = Intersection(5, shape);
    i.prepare_hit(r);
    ASSERT_LT(i.over_point_.z_, -EPSILON / 2);
    ASSERT_GT(i.point_.z_, i.over_point_.z_);
}
