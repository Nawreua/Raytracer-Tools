#include <cassert>
#include <fstream>
#include <iostream>

#include "canvas.hh"
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

void write_in_canvas(const Projectile& p, Canvas& c)
{
    auto canvas_y = c.height_ - round(p.position_.y_);
    auto x = std::round(p.position_.x_);
    if (canvas_y < c.height_ && canvas_y >= 0 && x >= 0 && x < c.width_)
        c.write_pixel(p.position_.x_, canvas_y, color(1, 0, 0));
}

int main(void)
{
    auto canvas = Canvas(1366, 768);
    auto initial_velocity = vector(1, 1.8, 0).normalize() * 14;
    auto p = Projectile(point(0, 1, 0), initial_velocity);
    auto w = World(vector(0, -0.1, 0), vector(-0.01, 0, 0));
    auto nb_ticks = 0;
    std::cout << "The projectile is at " << p.position_.x_ << " on x axis"
        << " and at " << p.position_.y_ << " on y axis." << std::endl;
    write_in_canvas(p, canvas);
    while(p.position_.y_ > 0)
    {
        p = tick(w, p);
        write_in_canvas(p, canvas);
        nb_ticks++;
        std::cout << "The projectile is at " << p.position_.x_ << " on x axis"
            << " and at " << p.position_.y_ << " on y axis." << std::endl;
    }
    std::cout << "Number of ticks required: " << nb_ticks << std::endl;
    std::ofstream f("cannon.ppm");
    if (f.is_open())
        f << canvas.canvas_to_ppm();
    return 0;
}
