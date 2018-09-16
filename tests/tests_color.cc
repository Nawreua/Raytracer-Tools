#include "include.hh"

TEST(ColorTest, Implementation)
{
    auto c = Color(-0.5, 0.4, 1.7);
    ASSERT_FLOAT_EQ(c.red_, -0.5);
    ASSERT_FLOAT_EQ(c.green_, 0.4);
    ASSERT_FLOAT_EQ(c.blue_, 1.7);
}

TEST(ColorTest, AddingColors)
{
    auto c1 = color(0.9, 0.6, 0.75);
    auto c2 = Color(0.7, 0.1, 0.25);
    ASSERT_EQ(c1 + c2, Color(1.6, 0.7, 1.0));
}

TEST(ColorTest, SubstractingColors)
{
    auto c1 = color(0.9, 0.6, 0.75);
    auto c2 = Color(0.7, 0.1, 0.25);
    ASSERT_EQ(c1 - c2, Color(0.2, 0.5, 0.5));
}

TEST(ColorTest, MultiplicationScalar)
{
    auto c = color(0.2, 0.3, 0.4);
    ASSERT_EQ(c * 2, Color(0.4, 0.6, 0.8));
}

TEST(ColorTest, MultiplicationColors)
{
    auto c1 = Color(1, 0.2, 0.4);
    auto c2 = Color(0.9, 1, 0.1);
    ASSERT_EQ(c1 * c2, Color(0.9, 0.2, 0.04));
}
