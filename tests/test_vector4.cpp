#include <gtest/gtest.h>
#include <axis/Vector4.hpp>

using axis::Vector4;

TEST(Vector4, LengthOf345Triangle) {
    EXPECT_FLOAT_EQ(Vector4(3, 0, 0, 4).len(), 5.0f);
}

TEST(Vector4, NormalizeZeroVectorThrows) {
    EXPECT_THROW(Vector4().normalized(), std::runtime_error);
}

TEST(Vector4, DefaultConstructorGivesZeros) {
    Vector4 c;
    EXPECT_FLOAT_EQ(c.x, 0.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
    EXPECT_FLOAT_EQ(c.z, 0.0f);
    EXPECT_FLOAT_EQ(c.w, 0.0f);
}

TEST(Vector4, FourArgumentConstructorGivesXYZW) {
    Vector4 c(8.257f, 9.23f, 8.0f, 7.5f);
    EXPECT_FLOAT_EQ(c.x, 8.257f);
    EXPECT_FLOAT_EQ(c.y, 9.23f);
    EXPECT_FLOAT_EQ(c.z, 8.0f);
    EXPECT_FLOAT_EQ(c.w, 7.5f);
}

TEST(Vector4, VectorAdditionCorrect) {
    Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b(4.0f, 5.0f, 6.0f, 7.0f);
    Vector4 c = a + b;
    EXPECT_FLOAT_EQ(c.x, 5.0f);
    EXPECT_FLOAT_EQ(c.y, 7.0f);
    EXPECT_FLOAT_EQ(c.z, 9.0f);
    EXPECT_FLOAT_EQ(c.w, 11.0f);
}

TEST(Vector4, VectorAdditionCommutative) {
    Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b(4.0f, 5.0f, 6.0f, 7.0f);
    Vector4 c = a + b;
    Vector4 d = b + a;
    EXPECT_FLOAT_EQ(d.x, 5.0f);
    EXPECT_FLOAT_EQ(d.y, 7.0f);
    EXPECT_FLOAT_EQ(d.z, 9.0f);
    EXPECT_FLOAT_EQ(d.w, 11.0f);
    EXPECT_TRUE(c.x == d.x);
    EXPECT_TRUE(c.y == d.y);
    EXPECT_TRUE(c.z == d.z);
    EXPECT_TRUE(c.w == d.w);
}

TEST(Vector4, VectorSubtractionCorrect) {
    Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b(4.0f, 5.0f, 6.0f, 7.0f);
    Vector4 c = b - a;
    EXPECT_FLOAT_EQ(c.x, 3.0f);
    EXPECT_FLOAT_EQ(c.y, 3.0f);
    EXPECT_FLOAT_EQ(c.z, 3.0f);
    EXPECT_FLOAT_EQ(c.w, 3.0f);
}

TEST(Vector4, VectorMinusSelfZeroVector) {
    Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b = a - a;
    EXPECT_FLOAT_EQ(b.x, 0.0f);
    EXPECT_FLOAT_EQ(b.y, 0.0f);
    EXPECT_FLOAT_EQ(b.z, 0.0f);
    EXPECT_FLOAT_EQ(b.w, 0.0f);
}

TEST(Vector4, VectorTimesTwo) {
    Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b = a * 2;
    EXPECT_FLOAT_EQ(b.x, 2.0f);
    EXPECT_FLOAT_EQ(b.y, 4.0f);
    EXPECT_FLOAT_EQ(b.z, 6.0f);
    EXPECT_FLOAT_EQ(b.w, 8.0f);
}

TEST(Vector4, VectorMultiplicationCommutative) {
    Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b = a * 2;
    Vector4 c = 2 * a;
    EXPECT_FLOAT_EQ(b.x, 2.0f);
    EXPECT_FLOAT_EQ(b.y, 4.0f);
    EXPECT_FLOAT_EQ(b.z, 6.0f);
    EXPECT_FLOAT_EQ(b.w, 8.0f);
    EXPECT_TRUE(c.x == b.x);
    EXPECT_TRUE(c.y == b.y);
    EXPECT_TRUE(c.z == b.z);
    EXPECT_TRUE(c.w == b.w);
}

TEST(Vector4, LensqOfVector) {
    Vector4 a(3, 0, 0, 4);
    EXPECT_NEAR(a.lensq(), 25.0f, 1e-4f);
}

TEST(Vector4, TestNormalization) {
    Vector4 a(0, 3, 0, 4);
    Vector4 b = a.normalized();
    EXPECT_FLOAT_EQ(b.x, 0);
    EXPECT_FLOAT_EQ(b.y, 0.6f);
    EXPECT_FLOAT_EQ(b.z, 0);
    EXPECT_FLOAT_EQ(b.w, 0.8f);
    EXPECT_FLOAT_EQ(b.len(), 1.0f);

    // Ensure that the original is unchanged
    EXPECT_FLOAT_EQ(a.x, 0.0f);
    EXPECT_FLOAT_EQ(a.y, 3.0f);
    EXPECT_FLOAT_EQ(a.z, 0.0f);
    EXPECT_FLOAT_EQ(a.w, 4.0f);
}

TEST(Vector4, TestNormalizationInPlace) {
    Vector4 a(0, 3, 0, 4);
    a.normalize();
    EXPECT_FLOAT_EQ(a.x, 0);
    EXPECT_FLOAT_EQ(a.y, 0.6f);
    EXPECT_FLOAT_EQ(a.z, 0);
    EXPECT_FLOAT_EQ(a.w, 0.8f);
    EXPECT_FLOAT_EQ(a.len(), 1.0f);
}

TEST(Vector4, NormalizeInPlaceOnZeroVectorThrows) {
    EXPECT_THROW(Vector4().normalize(), std::runtime_error);
}

TEST(Vector4, DotProductOfTwoVectors) {
    EXPECT_FLOAT_EQ(axis::dot(Vector4{1, 2, 3, 4}, Vector4{4, 5, 6, 7}), 60.0f);
}

TEST(Vector4, DotProductOfTwoVectorsEqualsZero) {
    EXPECT_FLOAT_EQ(axis::dot(Vector4{1, 0, 0, 0}, Vector4{0, 0, 0, 1}), 0.0f);
}

TEST(Vector4, DotProductOfEqualVectorsEqualsLensq) {
    Vector4 c(1, 2, 3, 4);
    EXPECT_FLOAT_EQ(axis::dot(c, c), c.lensq());
}

TEST(Vector4, DistanceBetweenTwoVectorsCorrect) {
    EXPECT_FLOAT_EQ(axis::distance(Vector4{1, 2, 3, 4}, Vector4{4, 2, 3, 8}), 5.0f);
}

TEST(Vector4, DistanceIsCommutative) {
    Vector4 a(1, 2, 3, 4);
    Vector4 b(4, 2, 3, 8);
    EXPECT_TRUE(axis::distance(a, b) == axis::distance(b, a));
}

TEST(Vector4, DistanceToSelfIsZero) {
    Vector4 c(1, 2, 3, 4);
    EXPECT_FLOAT_EQ(axis::distance(c, c), 0.0f);
}

TEST(Vector4, ReflectGivesCorrectReflection) {
    Vector4 a(1, -1, 0, 2);
    Vector4 b(0, 1, 0, 0);
    Vector4 c = axis::reflect(a, b);
    EXPECT_FLOAT_EQ(c.x, 1.0f);
    EXPECT_FLOAT_EQ(c.y, 1.0f);
    EXPECT_FLOAT_EQ(c.z, 0.0f);
    EXPECT_FLOAT_EQ(c.w, 2.0f);
}

TEST(Vector4, ProjectOntoOtherVector) {
    Vector4 a(3, 4, 0, 5);
    Vector4 b(1, 0, 0, 0);
    Vector4 c = axis::project(a, b);
    EXPECT_FLOAT_EQ(c.x, 3.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
    EXPECT_FLOAT_EQ(c.z, 0.0f);
    EXPECT_FLOAT_EQ(c.w, 0.0f);
}

TEST(Vector4, ProjectOntoNonUnitVectorWorks) {
    Vector4 a(2, 2, 0, 2);
    Vector4 b(0, 0, 0, 3);
    Vector4 c = axis::project(a, b);
    EXPECT_FLOAT_EQ(c.x, 0.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
    EXPECT_FLOAT_EQ(c.z, 0.0f);
    EXPECT_FLOAT_EQ(c.w, 2.0f);
}

TEST(Vector4, ProjectOntoZeroVectorThrows) {
    EXPECT_THROW(axis::project(Vector4{1, 2, 3, 4}, Vector4()), std::runtime_error);
}

TEST(Vector4, RejectVectorFromOtherVector) {
    Vector4 a(3, 4, 0, 5);
    Vector4 b(1, 0, 0, 0);
    Vector4 c = axis::reject(a, b);
    EXPECT_FLOAT_EQ(c.x, 0.0f);
    EXPECT_FLOAT_EQ(c.y, 4.0f);
    EXPECT_FLOAT_EQ(c.z, 0.0f);
    EXPECT_FLOAT_EQ(c.w, 5.0f);
}

TEST(Vector4, ProjectionEqualToRejectionOfSameVectors) {
    Vector4 a(3, 4, 0, 5);
    Vector4 b(1, 0, 0, 0);
    Vector4 c = axis::project(a, b);
    Vector4 d = axis::reject(a, b);
    EXPECT_TRUE(c.x + d.x == a.x);
    EXPECT_TRUE(c.y + d.y == a.y);
    EXPECT_TRUE(c.z + d.z == a.z);
    EXPECT_TRUE(c.w + d.w == a.w);
}

TEST(Vector4, DotProductOfRejectionAndFromParamZero) {
    Vector4 a(3, 4, 0, 5);
    Vector4 b(1, 0, 0, 0);
    Vector4 c = axis::reject(a, b);
    EXPECT_NEAR(dot(c, b), 0.0f, 1e-4f);
}

TEST(Vector4, RejectFromAZeroVectorThrows) {
    EXPECT_THROW(axis::reject(Vector4{1, 2, 3, 4}, Vector4()), std::runtime_error);
}

TEST(Vector4, TestLerpEqualityBasedOnT) {
    Vector4 a;
    Vector4 b(10, 20, 30, 40);
    Vector4 c = axis::lerp(a, b, 0);
    Vector4 d = axis::lerp(a, b, 1);
    Vector4 e = axis::lerp(a, b, 0.5f);
    Vector4 f = axis::lerp(a, b, 2.0f);
    Vector4 g = axis::lerp(a, b, -1.0f);

    EXPECT_FLOAT_EQ(c.x, a.x);
    EXPECT_FLOAT_EQ(c.y, a.y);
    EXPECT_FLOAT_EQ(c.z, a.z);
    EXPECT_FLOAT_EQ(c.w, a.w);
    EXPECT_FLOAT_EQ(d.x, b.x);
    EXPECT_FLOAT_EQ(d.y, b.y);
    EXPECT_FLOAT_EQ(d.z, b.z);
    EXPECT_FLOAT_EQ(d.w, b.w);
    EXPECT_FLOAT_EQ(e.x, 5.0f);
    EXPECT_FLOAT_EQ(e.y, 10.0f);
    EXPECT_FLOAT_EQ(e.z, 15.0f);
    EXPECT_FLOAT_EQ(e.w, 20.0f);
    EXPECT_FLOAT_EQ(f.x, 20.0f);
    EXPECT_FLOAT_EQ(f.y, 40.0f);
    EXPECT_FLOAT_EQ(f.z, 60.0f);
    EXPECT_FLOAT_EQ(f.w, 80.0f);
    EXPECT_FLOAT_EQ(g.x, -10.0f);
    EXPECT_FLOAT_EQ(g.y, -20.0f);
    EXPECT_FLOAT_EQ(g.z, -30.0f);
    EXPECT_FLOAT_EQ(g.w, -40.0f);
}

TEST(Vector4, MinGivesCorrectVectors) {
    Vector4 a(1, 5, 3, 8);
    Vector4 b(4, 2, 6, 7);
    Vector4 c = axis::min(a, b);
    EXPECT_FLOAT_EQ(c.x, 1.0f);
    EXPECT_FLOAT_EQ(c.y, 2.0f);
    EXPECT_FLOAT_EQ(c.z, 3.0f);
    EXPECT_FLOAT_EQ(c.w, 7.0f);
}

TEST(Vector4, MaxGivesCorrectVectors) {
    Vector4 a(1, 5, 3, 8);
    Vector4 b(4, 2, 6, 7);
    Vector4 c = axis::max(a, b);
    EXPECT_FLOAT_EQ(c.x, 4.0f);
    EXPECT_FLOAT_EQ(c.y, 5.0f);
    EXPECT_FLOAT_EQ(c.z, 6.0f);
    EXPECT_FLOAT_EQ(c.w, 8.0f);
}

TEST(Vector4, CheckClampingOnVector) {
    Vector4 a(-5.0f, 5.0f, 15.0f, -1.0f);
    Vector4 b = axis::clamp(a, Vector4(), Vector4{10, 10, 10, 10});
    EXPECT_FLOAT_EQ(b.x, 0.0f);
    EXPECT_FLOAT_EQ(b.y, 5.0f);
    EXPECT_FLOAT_EQ(b.z, 10.0f);
    EXPECT_FLOAT_EQ(b.w, 0.0f);
}

TEST(Vector4, ReflectPreservesLength) {
    Vector4 v(1, -1, 0, 0);
    Vector4 n(0, 1, 0, 0);
    Vector4 r = axis::reflect(v, n);
    EXPECT_FLOAT_EQ(r.len(), v.len());
}

TEST(Vector4, ReflectingTwiceReturnsOriginal) {
    Vector4 c(1, 2, 3, 0);
    Vector4 n(1, 0, 0, 0);
    Vector4 r = axis::reflect(axis::reflect(c, n), n);
    EXPECT_FLOAT_EQ(c.x, r.x);
    EXPECT_FLOAT_EQ(c.y, r.y);
    EXPECT_FLOAT_EQ(c.z, r.z);
    EXPECT_FLOAT_EQ(c.w, r.w);
}