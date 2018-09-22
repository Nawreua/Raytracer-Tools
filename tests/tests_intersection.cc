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
