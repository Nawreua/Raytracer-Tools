#pragma once

#include "color.hh"
#include "matrix.hh"
#include "tuple.hh"

class Shape;

class Pattern
{
public:
    Pattern();

    virtual Color pattern_at(const Tuple& point) = 0;
    Color pattern_at_shape(const Shape& object, const Tuple& world_point);
    void set_pattern_transform(const Matrix& t);

    Matrix transform_;
};

class TestPattern : public Pattern
{
public:
    Color pattern_at(const Tuple& point) override;
};

class StripePattern : public Pattern
{
public:
    StripePattern(const Color& a, const Color& b);

    Color pattern_at(const Tuple& point) override;

    Color a_;
    Color b_;
};

class GradientPattern : public Pattern
{
public:
    GradientPattern(const Color& a, const Color& b);

    Color pattern_at(const Tuple& point) override;

    Color a_;
    Color b_;
};

class RingPattern : public Pattern
{
public:
    RingPattern(const Color& a, const Color& b);

    Color pattern_at(const Tuple& point) override;

    Color a_;
    Color b_;
};

class CheckersPattern : public Pattern
{
public:
    CheckersPattern(const Color& a, const Color& b);

    Color pattern_at(const Tuple& point) override;

    Color a_;
    Color b_;
};

class RadialGradientPattern : public Pattern
{
public:
    RadialGradientPattern(const Color& a, const Color& b);

    Color pattern_at(const Tuple& point) override;

    Color a_;
    Color b_;
};
