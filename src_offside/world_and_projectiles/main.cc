#include <cassert>
#include <iostream>

#include "tuple.hh"

struct Projectile
{
    Projectile(const Tuple& position, const Tuple& velocity)
        : position_(position), velocity_(velocity)
    {
        assert(is_a_point(position));
        assert(is_a_vector(velocity));
    }

    Tuple position_;
    Tuple velocity_;
};

struct World
{
    World(const Tuple& gravity, const Tuple& wind)
        : gravity_(gravity), wind_(wind)
    {
        assert(is_a_vector(gravity));
        assert(is_a_vector(wind));
    }

    Tuple gravity_;
    Tuple wind_;
};

Projectile tick(const World& world, const Projectile& p)
{
    auto position = p.position_ + p.velocity_;
    auto velocity = p.velocity_ + world.gravity_ + world.wind_;
    return Projectile(position, velocity);
}

int main(void)
{
    auto initial_velocity = vector(1, 1, 0).normalize() * 2;
    auto p = Projectile(point(0, 1, 0), initial_velocity);
    auto w = World(vector(0, -0.1, 0), vector(-0.01, 0, 0));
    auto nb_ticks = 0;
    std::cout << "The projectile is at " << p.position_.x_ << " on x axis"
        << " and at " << p.position_.y_ << " on y axis." << std::endl;
    while(p.position_.y_ > 0)
    {
        p = tick(w, p);
        nb_ticks++;
        std::cout << "The projectile is at " << p.position_.x_ << " on x axis"
            << " and at " << p.position_.y_ << " on y axis." << std::endl;
    }
    std::cout << "Number of ticks required: " << nb_ticks << std::endl;
    return 0;
}
