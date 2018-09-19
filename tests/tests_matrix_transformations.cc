#include "include.hh"

TEST(MatrixTransformationTest, MultiplicationTranslationMatrix)
{
    auto transform = translation(5, -3, 2);
    auto p = point(-3, 4, 5);
    ASSERT_EQ(transform * p, point(2, 1, 7));
}

TEST(MatrixTransformationTest, MultiplicationInverseTranslationMatrix)
{
    auto transform = translation(5, -3, 2);
    auto inv = transform.inverse();
    auto p = point(-3, 4, 5);
    ASSERT_EQ(inv * p, point(-8, 7, 3));
}

TEST(MatrixTransformationTest, TranslationOnVector)
{
    auto transform = translation(5, -3, 2);
    auto v = vector(-3, 4, 5);
    ASSERT_EQ(transform * v, v);
}

TEST(MatrixTransformationTest, ScalingOnPoint)
{
    auto transform = scaling(2, 3, 4);
    auto p = point(-4, 6, 8);
    ASSERT_EQ(transform * p, point(-8, 18, 32));
}

TEST(MatrixTransformationTest, ScalingOnVector)
{
    auto transform = scaling(2, 3, 4);
    auto v = vector(-4, 6, 8);
    ASSERT_EQ(transform * v, vector(-8, 18, 32));
}

TEST(MatrixTransformationTest, InverseScalingOnVector)
{
    auto transform = scaling(2, 3, 4);
    auto inv = transform.inverse();
    auto v = vector(-4, 6, 8);
    ASSERT_EQ(inv * v, vector(-2, 2, 2));
}

TEST(MatrixTransformationTest, ReflectionIsScalingByNegative)
{
    auto transform = scaling(-1, 1, 1);
    auto p = point(2, 3, 4);
    ASSERT_EQ(transform * p, point(-2, 3, 4));
}

TEST(MatrixTransformationTest, RotationX)
{
    auto p = point(0, 1, 0);
    auto half_quarter = rotation_x(PI / 4);
    auto full_quarter = rotation_x(PI / 2);
    ASSERT_EQ(half_quarter * p, point(0, sqrt(2) / 2, sqrt(2) / 2));
    ASSERT_EQ(full_quarter * p, point(0, 0, 1));
}

TEST(MatrixTransformationTest, InverseRotationX)
{
    auto v = point(0, 1, 0);
    auto half_quarter = rotation_x(PI / 4);
    auto inv = half_quarter.inverse();
    ASSERT_EQ(inv * v, point(0, sqrt(2) / 2, -(sqrt(2) / 2)));
}

TEST(MatrixTransformationTest, RotationY)
{
    auto p = point(0, 0, 1);
    auto half_quarter = rotation_y(PI / 4);
    auto full_quarter = rotation_y(PI / 2);
    ASSERT_EQ(half_quarter * p, point(sqrt(2) / 2, 0, sqrt(2) / 2));
    ASSERT_EQ(full_quarter * p, point(1, 0, 0));
}

TEST(MatrixTransformationTest, RotationZ)
{
    auto p = point(0, 1, 0);
    auto half_quarter = rotation_z(PI / 4);
    auto full_quarter = rotation_z(PI / 2);
    ASSERT_EQ(half_quarter * p, point(-sqrt(2) / 2, sqrt(2) / 2, 0));
    ASSERT_EQ(full_quarter * p, point(-1, 0, 0));
}

TEST(MatrixTransformationTest, ShearingTestXToY)
{
    auto transform = shearing(1, 0, 0, 0, 0, 0);
    auto p = point(2, 3, 4);
    ASSERT_EQ(transform * p, point(5, 3, 4));
}

TEST(MatrixTransformationTest, ShearingTestXToZ)
{
    auto transform = shearing(0, 1, 0, 0, 0, 0);
    auto p = point(2, 3, 4);
    ASSERT_EQ(transform * p, point(6, 3, 4));
}

TEST(MatrixTransformationTest, ShearingTestYToY)
{
    auto transform = shearing(0, 0, 1, 0, 0, 0);
    auto p = point(2, 3, 4);
    ASSERT_EQ(transform * p, point(2, 5, 4));
}

TEST(MatrixTransformationTest, ShearingTestYToZ)
{
    auto transform = shearing(0, 0, 0, 1, 0, 0);
    auto p = point(2, 3, 4);
    ASSERT_EQ(transform * p, point(2, 7, 4));
}

TEST(MatrixTransformationTest, ShearingTestZToX)
{
    auto transform = shearing(0, 0, 0, 0, 1, 0);
    auto p = point(2, 3, 4);
    ASSERT_EQ(transform * p, point(2, 3, 6));
}

TEST(MatrixTransformationTest, ShearingTestZToY)
{
    auto transform = shearing(0, 0, 0, 0, 0, 1);
    auto p = point(2, 3, 4);
    ASSERT_EQ(transform * p, point(2, 3, 7));
}

TEST(MatrixTransformationTest, SequentialTransformations)
{
    auto p = point(1, 0, 1);
    auto A = rotation_x(PI / 2);
    auto B = scaling(5, 5, 5);
    auto C = translation(10, 5, 7);
    auto p2 = A * p;
    ASSERT_EQ(p2, point(1, -1, 0));
    auto p3 = B * p2;
    ASSERT_EQ(p3, point(5, -5, 0));
    auto p4 = C * p3;
    ASSERT_EQ(p4, point(15, 0, 7));
}

TEST(MatrixTransformationTest, ChainedTransformations)
{
    auto p = point(1, 0, 1);
    auto A = rotation_x(PI / 2);
    auto B = scaling(5, 5, 5);
    auto C = translation(10, 5, 7);
    auto T = C * B * A;
    ASSERT_EQ(T * p, point(15, 0, 7));
}
