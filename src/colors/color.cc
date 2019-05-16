#include "color.hh"

namespace
{
    bool equal(float a, float b)
    {
        return abs(a - b) < EPSILON;
    }
} // namespace

Color::Color(float red, float green, float blue)
    : red_(red)
    , green_(green)
    , blue_(blue)
{}

Color& Color::operator+=(const Color& rhs)
{
    red_ += rhs.red_;
    green_ += rhs.green_;
    blue_ += rhs.blue_;
    return *this;
}

Color& Color::operator-=(const Color& rhs)
{
    red_ -= rhs.red_;
    green_ -= rhs.green_;
    blue_ -= rhs.blue_;
    return *this;
}

Color& Color::operator*=(float rhs)
{
    red_ *= rhs;
    green_ *= rhs;
    blue_ *= rhs;
    return *this;
}

Color& Color::operator*=(const Color& rhs)
{
    red_ *= rhs.red_;
    green_ *= rhs.green_;
    blue_ *= rhs.blue_;
    return *this;
}

Color& Color::operator/=(int rhs)
{
    red_ /= rhs;
    green_ /= rhs;
    blue_ /= rhs;
    return *this;
}

Color Color::black()
{
    return Color(0, 0, 0);
}

bool operator==(const Color& lhs, const Color& rhs)
{
    return equal(lhs.red_, rhs.red_) && equal(lhs.green_, rhs.green_)
        && equal(lhs.blue_, rhs.blue_);
}

Color operator+(Color lhs, const Color& rhs)
{
    return lhs += rhs;
}

Color operator-(Color lhs, const Color& rhs)
{
    return lhs -= rhs;
}

Color operator*(Color lhs, float rhs)
{
    return lhs *= rhs;
}

Color operator*(Color lhs, const Color& rhs)
{
    return lhs *= rhs;
}

Color operator/(Color lhs, int rhs)
{
    return lhs /= rhs;
}

Color color(float red, float green, float blue)
{
    return Color(red, green, blue);
}
