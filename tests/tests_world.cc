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
    ASSERT_EQ(*world.objects_[0], s1);
    ASSERT_EQ(*world.objects_[1], s2);
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
    auto hit = Intersection(4, *shape);
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
    auto hit = Intersection(0.5, *shape);
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
    outer->material_.ambient_ = 1;
    auto inner = world.objects_[1];
    inner->material_.ambient_ = 1;
    auto ray = Ray(point(0, 0, -0.75), vector(0, 0, 1));
    auto c = world.color_at(ray);
    ASSERT_EQ(c, inner->material_.color_);
}

TEST(WorldTest, NoShadowWhenNothingCollinearWithPointAndLight)
{
    auto world = World::default_world();
    auto p = point(0, 10, 0);
    ASSERT_FALSE(world.is_shadowed(p, world.lights_[0]));
}

TEST(WorldTest, ShadowWhenObjectBetweenPointAndLight)
{
    auto world = World::default_world();
    auto p = point(10, -10, 10);
    ASSERT_TRUE(world.is_shadowed(p, world.lights_[0]));
}

TEST(WorldTest, NoShadowWhenObjectBehindLight)
{
    auto world = World::default_world();
    auto p = point(-20, 20, -20);
    ASSERT_FALSE(world.is_shadowed(p, world.lights_[0]));
}

TEST(WorldTest, NoShadowWhenObjectBehindPoint)
{
    auto world = World::default_world();
    auto p = point(-2, 2, -2);
    ASSERT_FALSE(world.is_shadowed(p, world.lights_[0]));
}

TEST(WorldTest, ShadeHitGivenIntersectionShadow)
{
    auto w = World();
    w.lights_.push_back(PointLight(point(0, 0, -10), Color(1, 1, 1)));
    auto s1 = std::make_shared<Sphere>();
    w.objects_.push_back(s1);
    auto s2 = std::make_shared<Sphere>();
    s2->transform_ = translation(0, 0, 10);
    w.objects_.push_back(s2);
    auto r = Ray(point(0, 0, 5), vector(0, 0, 1));
    auto i = Intersection(4, *s2);
    i.prepare_hit(r);
    auto c = w.shade_hit(i);
    ASSERT_EQ(c, Color(0.1, 0.1, 0.1));
}

TEST(WorldTest, ReflectedColorForNonreflectiveMaterial)
{
    auto w = World::default_world();
    auto r = Ray(point(0, 0, 0), vector(0, 0, 1));
    w.objects_[1]->material_.ambient_ = 1;
    auto i = Intersection(1, *w.objects_[1]);
    i.prepare_hit(r);
    auto color = w.reflected_color(i);
    ASSERT_EQ(color, Color(0, 0, 0));
}

TEST(WorldTest, ReflectedColorForReflectiveMaterial)
{
    auto w = World::default_world();
    auto shape = std::make_shared<Plane>();
    shape->material_.reflective_ = 0.5;
    shape->transform_ = translation(0, -1, 0);
    w.objects_.push_back(shape);
    auto r = Ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    auto i = Intersection(sqrt(2), *shape);
    i.prepare_hit(r);
    auto color = w.reflected_color(i);
    ASSERT_EQ(color, Color(0.19032, 0.2379, 0.14274));
}

TEST(WorldTest, ShadeHitWithReflectiveMaterial)
{
    auto w = World::default_world();
    auto shape = std::make_shared<Plane>();
    shape->material_.reflective_ = 0.5;
    shape->transform_ = translation(0, -1, 0);
    w.objects_.push_back(shape);
    auto r = Ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    auto i = Intersection(sqrt(2), *shape);
    i.prepare_hit(r);
    auto color = w.shade_hit(i);
    ASSERT_EQ(color, Color(0.87677, 0.92436, 0.82918));
}

TEST(WorldTest, ColorAtWithMutuallyReflectiveSurfaces)
{
    auto w = World();
    w.lights_.push_back(PointLight(point(0, 0, 0), Color(1, 1, 1)));
    auto lower = std::make_shared<Plane>();
    lower->material_.reflective_ = 1;
    lower->set_transform(translation(0, -1, 0));
    w.objects_.push_back(lower);
    auto upper = std::make_shared<Plane>();
    upper->material_.reflective_ = 1;
    upper->transform_ = translation(0, 1, 0);
    w.objects_.push_back(upper);
    auto r = Ray(point(0, 0, 0), vector(0, 1, 0));
    w.color_at(r);
}

TEST(WorldTest, ReflectedColorAtMaximumRecursiveDepth)
{
    auto w = World::default_world();
    auto shape = std::make_shared<Plane>();
    shape->material_.reflective_ = 0.5;
    shape->transform_ = translation(0, -1, 0);
    w.objects_.push_back(shape);
    auto r = Ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    auto i = Intersection(sqrt(2), *shape);
    i.prepare_hit(r);
    auto color = w.reflected_color(i, 0);
    ASSERT_EQ(color, Color(0, 0, 0));
}
