#pragma once

#include "color.hh"
#include "matrix.hh"
#include "tuple.hh"

class Shape;

class Pattern
{
public:
    Pattern();

    virtual Color pattern_at(const Tuple& point) const = 0;
    Color pattern_at_shape(const Shape& object, const Tuple& world_point) const;
    void set_pattern_transform(const Matrix& t);

    Matrix transform_;
};

class TestPattern : public Pattern
{
public:
    Color pattern_at(const Tuple& point) const override;
};

class StripePattern : public Pattern
{
public:
    StripePattern(const Color& a, const Color& b);

    Color pattern_at(const Tuple& point) const override;

    Color a_;
    Color b_;
};

class GradientPattern : public Pattern
{
public:
    GradientPattern(const Color& a, const Color& b);

    Color pattern_at(const Tuple& point) const override;

    Color a_;
    Color b_;
};

class RingPattern : public Pattern
{
public:
    RingPattern(const Color& a, const Color& b);

    Color pattern_at(const Tuple& point) const override;

    Color a_;
    Color b_;
};

class CheckersPattern : public Pattern
{
public:
    CheckersPattern(const Color& a, const Color& b);

    Color pattern_at(const Tuple& point) const override;

    Color a_;
    Color b_;
};

class RadialGradientPattern : public Pattern
{
public:
    RadialGradientPattern(const Color& a, const Color& b);

    Color pattern_at(const Tuple& point) const override;

    Color a_;
    Color b_;
};

class SolidPattern : public Pattern
{
public:
    SolidPattern(const Color& color);

    Color pattern_at(const Tuple&) const override;

    Color color_;
};

class BlendedPattern : public Pattern
{
public:
    BlendedPattern(Pattern& a, Pattern& b);

    Color pattern_at(const Tuple& point) const override;

    Pattern* a_;
    Pattern* b_;
};
