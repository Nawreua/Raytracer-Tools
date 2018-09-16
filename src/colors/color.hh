#pragma once

#include <cmath>

#include "constants.hh"

struct Color
{
    Color() = default;
    Color(float red, float green, float blue);

    Color& operator+=(const Color& rhs);
    Color& operator-=(const Color& rhs);
    Color& operator*=(float rhs);
    Color& operator*=(const Color& rhs);

    float red_;
    float green_;
    float blue_;
};

bool operator==(const Color& lhs, const Color& rhs);

Color operator+(Color lhs, const Color& rhs);
Color operator-(Color lhs, const Color& rhs);
Color operator*(Color lhs, float rhs);
Color operator*(Color lhs, const Color& rhs);

Color color(float red, float green, float blue);
