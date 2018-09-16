#include <gtest/gtest.h>
#include "tuple.hh"

TEST(TupleTest, ImplementationPoint)
{
    auto a = Tuple(4.3, -4.2, 3.1, 1.0);
    ASSERT_FLOAT_EQ(a.x_, 4.3);
    ASSERT_FLOAT_EQ(a.y_, -4.2);
    ASSERT_FLOAT_EQ(a.z_, 3.1);
    ASSERT_EQ(a.w_, 1.0);
    ASSERT_TRUE(is_a_point(a));
    ASSERT_FALSE(is_a_vector(a));
}

TEST(TupleTest, ImplementationVector)
{
    auto a = Tuple(4.3, -4.2, 3.1, 0.0);
    ASSERT_FLOAT_EQ(a.x_, 4.3);
    ASSERT_FLOAT_EQ(a.y_, -4.2);
    ASSERT_FLOAT_EQ(a.z_, 3.1);
    ASSERT_EQ(a.w_, 0.0);
    ASSERT_FALSE(is_a_point(a));
    ASSERT_TRUE(is_a_vector(a));
}

TEST(TupleTest, FactoryPoint)
{
    auto p = point(4, -4, 3);
    ASSERT_EQ(p, Tuple(4, -4, 3, 1));
}

TEST(TupleTest, FactoryVector)
{
    auto v = vector(4, -4, 3);
    ASSERT_EQ(v, Tuple(4, -4, 3, 0));
}

TEST(TupleTest, AdditionTuple)
{
    auto a1 = Tuple(3, -2, 5, 1);
    auto a2 = Tuple(-2, 3, 1, 0);
    ASSERT_EQ(a1 + a2, Tuple(1, 1, 6, 1));
}

TEST(TupleTest, SubstractionTupleTwoPoints)
{
    auto p1 = point(3, 2, 1);
    auto p2 = point(5, 6, 7);
    ASSERT_EQ(p1 - p2, vector(-2, -4, -6));
}

TEST(TupleTest, SubstractionTupleVectorFromPoint)
{
    auto p = point(3, 2, 1);
    auto v = vector(5, 6, 7);
    ASSERT_EQ(p - v, point(-2, -4, -6));
}

TEST(TupleTest, SubstractionTupleTwoVectors)
{
    auto v1 = vector(3, 2, 1);
    auto v2 = vector(5, 6, 7);
    ASSERT_EQ(v1 - v2, vector(-2, -4, -6));
}

TEST(TupleTest, SubstractionVectorFromZeroVector)
{
    auto zero = vector(0, 0, 0);
    auto v = vector(1, -2, 3);
    ASSERT_EQ(zero - v, vector(-1, 2, -3));
}

TEST(TupleTest, NegateTuple)
{
    auto a = Tuple(1, -2, 3, -4);
    ASSERT_EQ(-a, Tuple(-1, 2, -3, 4));
}

TEST(TupleTest, MultiplicationScalar)
{
    auto a = Tuple(1, -2, 3, -4);
    ASSERT_EQ(a * 3.5, Tuple(3.5, -7, 10.5, -14));
}

TEST(TupleTest, MultiplicationFraction)
{
    auto a = Tuple(1, -2, 3, -4);
    ASSERT_EQ(a * 0.5, Tuple(0.5, -1, 1.5, -2));
}

TEST(TupleTest, DivisionScalar)
{
    auto a = Tuple(1, -2, 3, -4);
    ASSERT_EQ(a / 2, Tuple(0.5, -1, 1.5, -2));
}

TEST(TupleTest, MagnitudeTest1)
{
    auto v = vector(1, 0, 0);
    ASSERT_FLOAT_EQ(v.magnitude(), 1);
}

TEST(TupleTest, MagnitudeTest2)
{
    auto v = vector(0, 1, 0);
    ASSERT_FLOAT_EQ(v.magnitude(), 1);
}

TEST(TupleTest, MagnitudeTest3)
{
    auto v = vector(0, 0, 1);
    ASSERT_FLOAT_EQ(v.magnitude(), 1);
}

TEST(TupleTest, MagnitudeTest4)
{
    auto v = vector(1, 2, 3);
    ASSERT_FLOAT_EQ(v.magnitude(), sqrt(14));
}

TEST(TupleTest, MagnitudeTest5)
{
    auto v = vector(-1, -2, -3);
    ASSERT_FLOAT_EQ(v.magnitude(), sqrt(14));
}

TEST(TupleTest, NormalizingVectorUnidirectional)
{
    auto v = vector(4, 0, 0);
    ASSERT_EQ(v.normalize(), vector(1, 0, 0));
}

TEST(TupleTest, NormalizingVector)
{
    auto v = vector(1, 2, 3);
    ASSERT_EQ(v.normalize(), vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)));
}

TEST(TupleTest, NormalizedMagnitude)
{
    auto v = vector(1, 2, 3);
    auto norm = v.normalize();
    ASSERT_FLOAT_EQ(norm.magnitude(), 1);
}

TEST(TupleTest, DotProduct)
{
    auto a = vector(1, 2, 3);
    auto b = vector(2, 3, 4);
    ASSERT_FLOAT_EQ(dot(a, b), 20);
}

TEST(TupleTest, CrossProduct)
{
    auto a = vector(1, 2, 3);
    auto b = vector(2, 3, 4);
    ASSERT_EQ(cross(a, b), vector(-1, 2, -1));
    ASSERT_EQ(cross(b, a), vector(1, -2, 1));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
