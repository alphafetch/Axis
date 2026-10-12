#include <gtest/gtest.h>
#include <axis/Vector2.hpp>

using axis::Vector2;

TEST(Vector2, LengthOf345Triangle) {
    EXPECT_FLOAT_EQ(Vector2(3, 4).len(), 5.0f);
}

TEST(Vector2, NormalizeZeroVectorThrows) {
    EXPECT_THROW(Vector2().normalized(), std::runtime_error);
}

TEST(Vector2, DefaultConstructorGivesZeros) {
    Vector2 c;
    EXPECT_FLOAT_EQ(c.x, 0.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
}

TEST(Vector2, TwoArgumentConstructorGivesXY) {
    Vector2 c(8.257f, 9.23f);
    EXPECT_FLOAT_EQ(c.x, 8.257f);
    EXPECT_FLOAT_EQ(c.y, 9.23f);
}

TEST(Vector2, VectorAdditionCorrect) {
    Vector2 a(1.0f, 2.0f);
    Vector2 b(4.0f, 5.0f);
    Vector2 c = a + b;
    EXPECT_FLOAT_EQ(c.x, 5.0f);
    EXPECT_FLOAT_EQ(c.y, 7.0f);
}

TEST(Vector2, VectorAdditionCommutative) {
    Vector2 a(1.0f, 2.0f);
    Vector2 b(4.0f, 5.0f);
    Vector2 c = a + b;
    Vector2 d = b + a;
    EXPECT_FLOAT_EQ(d.x, 5.0f);
    EXPECT_FLOAT_EQ(d.y, 7.0f);
    EXPECT_TRUE(c.x == d.x);
    EXPECT_TRUE(c.y == d.y);
}

TEST(Vector2, VectorSubtractionCorrect) {
    Vector2 a(1.0f, 2.0f);
    Vector2 b(4.0f, 5.0f);
    Vector2 c = b - a;
    EXPECT_FLOAT_EQ(c.x, 3.0f);
    EXPECT_FLOAT_EQ(c.y, 3.0f);
}

TEST(Vector2, VectorMinusSelfZeroVector) {
    Vector2 a(1.0f, 2.0f);
    Vector2 b = a - a;
    EXPECT_FLOAT_EQ(b.x, 0.0f);
    EXPECT_FLOAT_EQ(b.y, 0.0f);
}

TEST(Vector2, VectorTimesTwo) {
    Vector2 a(1.0f, 2.0f);
    Vector2 b = a * 2;
    EXPECT_FLOAT_EQ(b.x, 2.0f);
    EXPECT_FLOAT_EQ(b.y, 4.0f);
}

TEST(Vector2, VectorMultiplicationCommutative) {
    Vector2 a(1.0f, 2.0f);
    Vector2 b = a * 2;
    Vector2 c = 2 * a;
    EXPECT_FLOAT_EQ(b.x, 2.0f);
    EXPECT_FLOAT_EQ(b.y, 4.0f);
    EXPECT_TRUE(c.x == b.x);
    EXPECT_TRUE(c.y == b.y);
}

TEST(Vector2, LensqOfVector) {
    Vector2 a(3, 4);
    EXPECT_NEAR(a.lensq(), 25.0f, 1e-4f);
}

TEST(Vector2, TestNormalization) {
    Vector2 a(3, 4);
    Vector2 b = a.normalized();
    EXPECT_FLOAT_EQ(b.x, 0.6f);
    EXPECT_FLOAT_EQ(b.y, 0.8f);
    EXPECT_FLOAT_EQ(b.len(), 1.0f);

    // Ensure that the original is unchanged
    EXPECT_FLOAT_EQ(a.x, 3.0f);
    EXPECT_FLOAT_EQ(a.y, 4.0f);
}

TEST(Vector2, TestNormalizationInPlace) {
    Vector2 a(3, 4);
    a.normalize();
    EXPECT_FLOAT_EQ(a.x, 0.6f);
    EXPECT_FLOAT_EQ(a.y, 0.8f);
    EXPECT_FLOAT_EQ(a.len(), 1.0f);
}

TEST(Vector2, NormalizeInPlaceOnZeroVectorThrows) {
    EXPECT_THROW(Vector2().normalize(), std::runtime_error);
}

TEST(Vector2, DotProductOfTwoVectors) {
    EXPECT_FLOAT_EQ(axis::dot(Vector2{1, 2}, Vector2{4, 5}), 14.0f);
}

TEST(Vector2, DotProductOfTwoVectorsEqualsZero) {
    EXPECT_FLOAT_EQ(axis::dot(Vector2{1, 0}, Vector2{0, 1}), 0.0f);
}

TEST(Vector2, DotProductOfEqualVectorsEqualsLensq) {
    Vector2 c(1, 2);
    EXPECT_FLOAT_EQ(axis::dot(c, c), c.lensq());
}

TEST(Vector2, DistanceBetweenTwoVectorsCorrect) {
    EXPECT_FLOAT_EQ(axis::distance(Vector2{1, 2}, Vector2{4, 6}), 5.0f);
}

TEST(Vector2, DistanceIsCommutative) {
    Vector2 a(1, 2);
    Vector2 b(4, 6);
    EXPECT_TRUE(axis::distance(a, b) == axis::distance(b, a));
}

TEST(Vector2, DistanceToSelfIsZero) {
    Vector2 c(1, 2);
    EXPECT_FLOAT_EQ(axis::distance(c, c), 0.0f);
}

TEST(Vector2, ReflectGivesCorrectReflection) {
    Vector2 a(1, -1);
    Vector2 b(0, 1);
    Vector2 c = axis::reflect(a, b);
    EXPECT_FLOAT_EQ(c.x, 1.0f);
    EXPECT_FLOAT_EQ(c.y, 1.0f);
}

TEST(Vector2, ProjectOntoOtherVector) {
    Vector2 a(3, 4);
    Vector2 b(1, 0);
    Vector2 c = axis::project(a, b);
    EXPECT_FLOAT_EQ(c.x, 3.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
}

TEST(Vector2, ProjectOntoNonUnitVectorWorks) {
    Vector2 a(2, 2);
    Vector2 b(3, 0);
    Vector2 c = axis::project(a, b);
    EXPECT_FLOAT_EQ(c.x, 2.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
}

TEST(Vector2, ProjectOntoZeroVectorThrows) {
    EXPECT_THROW(axis::project(Vector2{1, 2}, Vector2()), std::runtime_error);
}

TEST(Vector2, RejectVectorFromOtherVector) {
    Vector2 a(3, 4);
    Vector2 b(1, 0);
    Vector2 c = axis::reject(a, b);
    EXPECT_FLOAT_EQ(c.x, 0.0f);
    EXPECT_FLOAT_EQ(c.y, 4.0f);
}

TEST(Vector2, ProjectionEqualToRejectionOfSameVectors) {
    Vector2 a(3, 4);
    Vector2 b(1, 0);
    Vector2 c = axis::project(a, b);
    Vector2 d = axis::reject(a, b);
    EXPECT_TRUE(c.x + d.x == a.x);
    EXPECT_TRUE(c.y + d.y == a.y);
}

TEST(Vector2, DotProductOfRejectionAndFromParamZero) {
    Vector2 a(3, 4);
    Vector2 b(1, 0);
    Vector2 c = axis::reject(a, b);
    EXPECT_NEAR(dot(c, b), 0.0f, 1e-4f);
}

TEST(Vector2, RejectFromAZeroVectorThrows) {
    EXPECT_THROW(axis::reject(Vector2{1, 2}, Vector2()), std::runtime_error);
}

TEST(Vector2, TestLerpEqualityBasedOnT) {
    Vector2 a;
    Vector2 b(10, 20);
    Vector2 c = axis::lerp(a, b, 0);
    Vector2 d = axis::lerp(a, b, 1);
    Vector2 e = axis::lerp(a, b, 0.5f);
    Vector2 f = axis::lerp(a, b, 2.0f);
    Vector2 g = axis::lerp(a, b, -1.0f);

    EXPECT_FLOAT_EQ(c.x, a.x);
    EXPECT_FLOAT_EQ(c.y, a.y);
    EXPECT_FLOAT_EQ(d.x, b.x);
    EXPECT_FLOAT_EQ(d.y, b.y);
    EXPECT_FLOAT_EQ(e.x, 5.0f);
    EXPECT_FLOAT_EQ(e.y, 10.0f);
    EXPECT_FLOAT_EQ(f.x, 20.0f);
    EXPECT_FLOAT_EQ(f.y, 40.0f);
    EXPECT_FLOAT_EQ(g.x, -10.0f);
    EXPECT_FLOAT_EQ(g.y, -20.0f);
}

TEST(Vector2, MinGivesCorrectVectors) {
    Vector2 a(1, 5);
    Vector2 b(4, 2);
    Vector2 c = axis::min(a, b);
    EXPECT_FLOAT_EQ(c.x, 1.0f);
    EXPECT_FLOAT_EQ(c.y, 2.0f);
}

TEST(Vector2, MaxGivesCorrectVectors) {
    Vector2 a(1, 5);
    Vector2 b(4, 2);
    Vector2 c = axis::max(a, b);
    EXPECT_FLOAT_EQ(c.x, 4.0f);
    EXPECT_FLOAT_EQ(c.y, 5.0f);
}

TEST(Vector2, CheckClampingOnVector) {
    Vector2 a(-5.0f, 5.0f);
    Vector2 b = axis::clamp(a, Vector2(), Vector2{10, 10});
    EXPECT_FLOAT_EQ(b.x, 0.0f);
    EXPECT_FLOAT_EQ(b.y, 5.0f);
}
