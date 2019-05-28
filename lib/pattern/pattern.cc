#include "pattern.hh"

#include "shape.hh"

Pattern::Pattern()
    : transform_(Matrix::identity_matrix())
{}

Color Pattern::pattern_at_shape(const Shape& object,
                                const Tuple& world_point) const
{
    auto object_point = object.transform_.inverse() * world_point;
    auto pattern_point = transform_.inverse() * object_point;
    return pattern_at(pattern_point);
}

void Pattern::set_pattern_transform(const Matrix& t)
{
    transform_ = t;
}

Color TestPattern::pattern_at(const Tuple& point) const
{
    return Color(point.x_, point.y_, point.z_);
}

StripePattern::StripePattern(const Color& a, const Color& b)
    : a_(a)
    , b_(b)
{}

Color StripePattern::pattern_at(const Tuple& point) const
{
    return static_cast<int>(floor(point.x_)) % 2 == 0 ? a_ : b_;
}

GradientPattern::GradientPattern(const Color& a, const Color& b)
    : a_(a)
    , b_(b)
{}

Color GradientPattern::pattern_at(const Tuple& point) const
{
    auto distance = b_ - a_;
    auto fraction = point.x_ - floor(point.x_);
    return a_ + distance * fraction;
}

RingPattern::RingPattern(const Color& a, const Color& b)
    : a_(a)
    , b_(b)
{}

Color RingPattern::pattern_at(const Tuple& point) const
{
    int val = floor(sqrt(point.x_ * point.x_ + point.z_ * point.z_));
    return val % 2 == 0 ? a_ : b_;
}

CheckersPattern::CheckersPattern(const Color& a, const Color& b)
    : a_(a)
    , b_(b)
{}

Color CheckersPattern::pattern_at(const Tuple& point) const
{
    int val = floor(point.x_) + floor(point.y_) + floor(point.z_);
    return val % 2 == 0 ? a_ : b_;
}

RadialGradientPattern::RadialGradientPattern(const Color& a, const Color& b)
    : a_(a)
    , b_(b)
{}

Color RadialGradientPattern::pattern_at(const Tuple& point) const
{
    auto distance = b_ - a_;
    // auto fraction = point.x_ - floor(point.x_);
    int val = floor(sqrt(point.x_ * point.x_ + point.z_ * point.z_));
    return a_ + distance * val;
}

SolidPattern::SolidPattern(const Color& color)
    : color_(color)
{}

Color SolidPattern::pattern_at(const Tuple&) const
{
    return color_;
}

/*
BlendedPattern::BlendedPattern(Pattern& a, Pattern& b)
    : a_(&a)
    , b_(&b)
{}

Color BlendedPattern::pattern_at(const Tuple& point) const
{
    auto color_a = a_->pattern_at(point);
    auto color_b = b_->pattern_at(point);
    return (color_a + color_b) / 2;
}
*/
