#include "include.hh"

TEST(WorldTest, CreatingAWorld)
{
    auto w = World();
    ASSERT_EQ(w.objects_.size(), 0);
    ASSERT_EQ(w.lights_.size(), 0);
}

TEST(WorldTest, DefaultWorld)
{
    auto light = PointLight(point(-10, 10, -10), Color(1, 1, 1));
    auto s1 = Sphere();
    s1.material_.color_ = Color(0.8, 1.0, 0.6);
    s1.material_.diffuse_ = 0.7;
    s1.material_.specular_ = 0.2;
    auto s2 = Sphere();
    s2.set_transform(scaling(0.5, 0.5, 0.5));
    auto world = World::default_world();
    ASSERT_EQ(world.lights_[0], light);
    ASSERT_EQ(world.objects_[0], s1);
    ASSERT_EQ(world.objects_[1], s2);
}

TEST(WorldTest, IntersectWorldWithRay)
{
    auto world = World::default_world();
    auto ray = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto xs = world.intersect_world(ray);
    ASSERT_EQ(xs.size(), 4);
    ASSERT_FLOAT_EQ(xs[0].t_, 4);
    ASSERT_FLOAT_EQ(xs[1].t_, 4.5);
    ASSERT_FLOAT_EQ(xs[2].t_, 5.5);
    ASSERT_FLOAT_EQ(xs[3].t_, 6);
}

TEST(WorldTest, ShadingIntersection)
{
    auto world = World::default_world();
    auto ray = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto shape = world.objects_[0];
    auto hit = Intersection(4, shape);
    hit.prepare_hit(ray);
    auto c = world.shade_hit(hit);
    ASSERT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ShadingIntersectionInside)
{
    auto world = World::default_world();
    world.lights_[0] = PointLight(point(0, 0.25, 0), Color(1, 1, 1));
    auto ray = Ray(point(0, 0, 0), vector(0, 0, 1));
    auto shape = world.objects_[1];
    auto hit = Intersection(0.5, shape);
    hit.prepare_hit(ray);
    auto c = world.shade_hit(hit);
    ASSERT_EQ(c, Color(0.90498, 0.90498, 0.90498));
}

TEST(WorldTest, ColorWhenRayMisses)
{
    auto world = World::default_world();
    auto ray = Ray(point(0, 0, -5), vector(0, 1, 0));
    auto c = world.color_at(ray);
    ASSERT_EQ(c, Color(0, 0, 0));
}

TEST(WorldTest, ColorWhenRayHits)
{
    auto world = World::default_world();
    auto ray = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto c = world.color_at(ray);
    ASSERT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ColorIntersectionBehindRay)
{
    auto world = World::default_world();
    auto outer = world.objects_[0];
    outer.material_.ambient_ = 1;
    auto inner = world.objects_[1];
    inner.material_.ambient_ = 1;
    auto ray = Ray(point(0, 0, -0.75), vector(0, 0, 1));
    auto c = world.color_at(ray);
    ASSERT_EQ(c, inner.material_.color_);
}