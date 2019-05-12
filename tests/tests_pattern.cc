#include "include.hh"

class PatternTest: public ::testing::Test
{
    protected:
        void SetUp() override
        {
            black = Color(0, 0, 1);
            white = Color(1, 1, 1);
        }

        Color black;
        Color white;
};

TEST_F(PatternTest, CreatingStripePattern)
{
    auto pattern = StripePattern(white, black);
    ASSERT_EQ(pattern.a_, white);
    ASSERT_EQ(pattern.b_, black);
}

TEST_F(PatternTest, StripePatternConstantInY)
{
    auto pattern = StripePattern(white, black);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 0)), white);
    ASSERT_EQ(pattern.pattern_at(point(0, 1, 0)), white);
    ASSERT_EQ(pattern.pattern_at(point(0, 2, 0)), white);
}

TEST_F(PatternTest, StripePatternConstantInZ)
{
    auto pattern = StripePattern(white, black);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 0)), white);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 1)), white);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 2)), white);
}

TEST_F(PatternTest, StripePatternConstantInX)
{
    auto pattern = StripePattern(white, black);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 0)), white);
    ASSERT_EQ(pattern.pattern_at(point(0.9, 0, 0)), white);
    ASSERT_EQ(pattern.pattern_at(point(1, 0, 0)), black);
    ASSERT_EQ(pattern.pattern_at(point(-0.1, 0, 0)), black);
    ASSERT_EQ(pattern.pattern_at(point(-1, 0, 0)), black);
    ASSERT_EQ(pattern.pattern_at(point(-1.1, 0, 0)), white);
}

TEST_F(PatternTest, DefaultPatternTransformation)
{
    auto pattern = TestPattern();
    ASSERT_EQ(pattern.transform_, Matrix::identity_matrix());
}

TEST_F(PatternTest, AssigningATransformation)
{
    auto pattern = TestPattern();
    pattern.set_pattern_transform(translation(1, 2, 3));
    ASSERT_EQ(pattern.transform_, translation(1, 2, 3));
}

TEST_F(PatternTest, PatternWithObjectTransformation)
{
    auto object = Sphere();
    object.set_transform(scaling(2, 2, 2));
    auto pattern = TestPattern();
    auto c = pattern.pattern_at_shape(object, point(2, 3, 4));
    ASSERT_EQ(c, Color(1, 1.5, 2));
}

TEST_F(PatternTest, PatternWithPatternTransformation)
{
    auto object = Sphere();
    auto pattern = TestPattern();
    pattern.set_pattern_transform(scaling(2, 2, 2));
    auto c = pattern.pattern_at_shape(object, point(2, 3, 4));
    ASSERT_EQ(c, Color(1, 1.5, 2));
}

TEST_F(PatternTest, PatternWithObjectAndPatternTransformation)
{
    auto object = Sphere();
    object.set_transform(scaling(2, 2, 2));
    auto pattern = TestPattern();
    pattern.set_pattern_transform(translation(0.5, 1, 1.5));
    auto c = pattern.pattern_at_shape(object, point(2.5, 3, 3.5));
    ASSERT_EQ(c, Color(0.75, 0.5, 0.25));
}
TEST_F(PatternTest, StripesWithObjectTransformation)
{
    auto object = Sphere();
    object.set_transform(scaling(2, 2, 2));
    auto pattern = StripePattern(white, black);
    auto c = pattern.pattern_at_shape(object, point(1.5, 0, 0));
    ASSERT_EQ(c, white);
}

TEST_F(PatternTest, StripesWithPatternTransformation)
{
    auto object = Sphere();
    auto pattern = StripePattern(white, black);
    pattern.set_pattern_transform(scaling(2, 2, 2));
    auto c = pattern.pattern_at_shape(object, point(1.5, 0, 0));
    ASSERT_EQ(c, white);
}

TEST_F(PatternTest, StripesWithObjectAndPatternTransformation)
{
    auto object = Sphere();
    object.set_transform(scaling(2, 2, 2));
    auto pattern = StripePattern(white, black);
    pattern.set_pattern_transform(scaling(0.5, 0, 0));
    auto c = pattern.pattern_at_shape(object, point(2.5, 0, 0));
    ASSERT_EQ(c, white);
}

TEST_F(PatternTest, GradientLinearlyInterpolatesBetweenColors)
{
    auto pattern = GradientPattern(white, black);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 0)), white);
    ASSERT_EQ(pattern.pattern_at(point(0.25, 0, 0)), Color(0.75, 0.75, 0.75));
    ASSERT_EQ(pattern.pattern_at(point(0.5, 0, 0)), Color(0.5, 0.5, 0.5));
    ASSERT_EQ(pattern.pattern_at(point(0.75, 0, 0)), Color(0.25, 0.25, 0.25));
}

TEST_F(PatternTest, RingShouldExtendInBothXAndZ)
{
    auto pattern = RingPattern(white, black);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 0)), white);
    ASSERT_EQ(pattern.pattern_at(point(1, 0, 0)), black);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 1)), black);
    ASSERT_EQ(pattern.pattern_at(point(0.708, 0, 0.708)), black);
}

TEST_F(PatternTest, CheckersShouldRepeatInX)
{
    auto pattern = CheckersPattern(white, black);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 0)), white);
    ASSERT_EQ(pattern.pattern_at(point(0.99, 0, 0)), white);
    ASSERT_EQ(pattern.pattern_at(point(1.01, 0, 0)), black);
}

TEST_F(PatternTest, CheckersShouldRepeatInY)
{
    auto pattern = CheckersPattern(white, black);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 0)), white);
    ASSERT_EQ(pattern.pattern_at(point(0, 0.99, 0)), white);
    ASSERT_EQ(pattern.pattern_at(point(0, 1.01, 0)), black);
}

TEST_F(PatternTest, CheckersShouldRepeatInZ)
{
    auto pattern = CheckersPattern(white, black);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 0)), white);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 0.99)), white);
    ASSERT_EQ(pattern.pattern_at(point(0, 0, 1.01)), black);
}
