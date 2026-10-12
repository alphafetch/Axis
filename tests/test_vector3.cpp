#include <gtest/gtest.h>
#include <axis/Vector3.hpp>

using axis::Vector3;

TEST(Vector3, LengthOf345Triangle) {
    EXPECT_FLOAT_EQ(Vector3(3, 4, 0).len(), 5.0f);
}

TEST(Vector3, CrossOfXAndYIsZ) {
    Vector3 c = axis::cross(Vector3(1, 0, 0), Vector3(0, 1, 0));
    EXPECT_FLOAT_EQ(c.x, 0.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
    EXPECT_FLOAT_EQ(c.z, 1.0f);
}

TEST(Vector3, CrossOfYAndZIsX) {
    Vector3 c = axis::cross(Vector3(0, 1, 0), Vector3(0, 0, 1));
    EXPECT_FLOAT_EQ(c.x, 1.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
    EXPECT_FLOAT_EQ(c.z, 0.0f);
}

TEST(Vector3, CrossOfZAndXIsY) {
    Vector3 c = axis::cross(Vector3(0, 0, 1), Vector3(1, 0, 0));
    EXPECT_FLOAT_EQ(c.x, 0.0f);
    EXPECT_FLOAT_EQ(c.y, 1.0f);
    EXPECT_FLOAT_EQ(c.z, 0.0f);
}

TEST(Vector3, NormalizeZeroVectorThrows) {
    EXPECT_THROW(Vector3().normalized(), std::runtime_error);
}

TEST(Vector3, DefaultConstructorGivesZeros) {
    Vector3 c;
    EXPECT_FLOAT_EQ(c.x, 0.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
    EXPECT_FLOAT_EQ(c.z, 0.0f);
}

TEST(Vector3, ThreeArgumentConstructorGivesXYZ) {
    Vector3 c(8.257f, 9.23f, 8.0f);
    EXPECT_FLOAT_EQ(c.x, 8.257f);
    EXPECT_FLOAT_EQ(c.y, 9.23f);
    EXPECT_FLOAT_EQ(c.z, 8.0f);
}

TEST(Vector3, VectorAdditionCorrect) {
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(4.0f, 5.0f, 6.0f);
    Vector3 c = a + b;
    EXPECT_FLOAT_EQ(c.x, 5.0f);
    EXPECT_FLOAT_EQ(c.y, 7.0f);
    EXPECT_FLOAT_EQ(c.z, 9.0f);
}

TEST(Vector3, VectorAdditionCommutative) {
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(4.0f, 5.0f, 6.0f);
    Vector3 c = a + b;
    Vector3 d = b + a;
    EXPECT_FLOAT_EQ(d.x, 5.0f);
    EXPECT_FLOAT_EQ(d.y, 7.0f);
    EXPECT_FLOAT_EQ(d.z, 9.0f);
    EXPECT_TRUE(c.x == d.x);
    EXPECT_TRUE(c.y == d.y);
    EXPECT_TRUE(c.z == d.z);
}

TEST(Vector3, VectorSubtractionCorrect) {
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(4.0f, 5.0f, 6.0f);
    Vector3 c = b - a;
    EXPECT_FLOAT_EQ(c.x, 3.0f);
    EXPECT_FLOAT_EQ(c.y, 3.0f);
    EXPECT_FLOAT_EQ(c.z, 3.0f);
}

TEST(Vector3, VectorMinusSelfZeroVector) {
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b = a - a;
    EXPECT_FLOAT_EQ(b.x, 0.0f);
    EXPECT_FLOAT_EQ(b.y, 0.0f);
    EXPECT_FLOAT_EQ(b.z, 0.0f);
}

TEST(Vector3, VectorTimesTwo) {
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b = a * 2;
    EXPECT_FLOAT_EQ(b.x, 2.0f);
    EXPECT_FLOAT_EQ(b.y, 4.0f);
    EXPECT_FLOAT_EQ(b.z, 6.0f);
}

TEST(Vector3, VectorMultiplicationCommutative) {
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b = a * 2;
    Vector3 c = 2 * a;
    EXPECT_FLOAT_EQ(b.x, 2.0f);
    EXPECT_FLOAT_EQ(b.y, 4.0f);
    EXPECT_FLOAT_EQ(b.z, 6.0f);
    EXPECT_TRUE(c.x == b.x);
    EXPECT_TRUE(c.y == b.y);
    EXPECT_TRUE(c.z == b.z);
}

TEST(Vector3, LensqOfVector) {
    Vector3 a(3, 4, 0);
    EXPECT_NEAR(a.lensq(), 25.0f, 1e-4f);
}

TEST(Vector3, TestNormalization) {
    Vector3 a(0, 3, 4);
    Vector3 b = a.normalized();
    EXPECT_FLOAT_EQ(b.x, 0);
    EXPECT_FLOAT_EQ(b.y, 0.6f);
    EXPECT_FLOAT_EQ(b.z, 0.8f);
    EXPECT_FLOAT_EQ(b.len(), 1.0f);

    // Ensure that the original is unchanged
    EXPECT_FLOAT_EQ(a.x, 0.0f);
    EXPECT_FLOAT_EQ(a.y, 3.0f);
    EXPECT_FLOAT_EQ(a.z, 4.0f);
}

TEST(Vector3, TestNormalizationInPlace) {
    Vector3 a(0, 3, 4);
    a.normalize();
    EXPECT_FLOAT_EQ(a.x, 0);
    EXPECT_FLOAT_EQ(a.y, 0.6f);
    EXPECT_FLOAT_EQ(a.z, 0.8f);
    EXPECT_FLOAT_EQ(a.len(), 1.0f);
}

TEST(Vector3, NormalizeInPlaceOnZeroVectorThrows) {
    EXPECT_THROW(Vector3().normalize(), std::runtime_error);
}

TEST(Vector3, DotProductOfTwoVectors) {
    EXPECT_FLOAT_EQ(axis::dot(Vector3{1, 2, 3}, Vector3{4, 5, 6}), 32.0f);
}

TEST(Vector3, DotProductOfTwoVectorsEqualsZero) {
    EXPECT_FLOAT_EQ(axis::dot(Vector3{1, 0, 0}, Vector3{0, 1, 0}), 0.0f);
}

TEST(Vector3, DotProductOfEqualVectorsEqualsLensq) {
    Vector3 c(1, 2, 3);
    EXPECT_FLOAT_EQ(axis::dot(c, c), c.lensq());
}

TEST(Vector3, CrossProductOfVectors) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    Vector3 c = axis::cross(a, b);
    EXPECT_FLOAT_EQ(c.x, -3.0f);
    EXPECT_FLOAT_EQ(c.y, 6.0f);
    EXPECT_FLOAT_EQ(c.z, -3.0f);
}

TEST(Vector3, CrossIsEqualToNegativeReverseCross) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    Vector3 c = axis::cross(a, b);
    Vector3 d = axis::cross(b, a);
    // Negate
    d.x = -d.x;
    d.y = -d.y;
    d.z = -d.z;
    EXPECT_TRUE(c.x == d.x);
    EXPECT_TRUE(c.y == d.y);
    EXPECT_TRUE(c.z == d.z);
}

TEST(Vector3, SelfCrossEqualsZero) {
    Vector3 a(1, 2, 3);
    Vector3 b = axis::cross(a, a);
    EXPECT_FLOAT_EQ(b.x, 0.0f);
    EXPECT_FLOAT_EQ(b.y, 0.0f);
    EXPECT_FLOAT_EQ(b.z, 0.0f);
}

TEST(Vector3, CrossHasDotProductZeroWithOriginalTwo) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    Vector3 c = axis::cross(a, b);
    EXPECT_FLOAT_EQ(axis::dot(c, a), 0.0f);
    EXPECT_FLOAT_EQ(axis::dot(c, b), 0.0f);
}

TEST(Vector3, DistanceBetweenTwoVectorsCorrect) {
    EXPECT_FLOAT_EQ(axis::distance(Vector3{1, 2, 3}, Vector3{4, 6, 3}), 5.0f);
}

TEST(Vector3, DistanceIsCommutative) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 6, 3);
    EXPECT_TRUE(axis::distance(a, b) == axis::distance(b, a));
}

TEST(Vector3, DistanceToSelfIsZero) {
    Vector3 c(1, 2, 3);
    EXPECT_FLOAT_EQ(axis::distance(c, c), 0.0f);
}

TEST(Vector3, ReflectGivesCorrectReflection) {
    Vector3 a(1, -1, 0);
    Vector3 b(0, 1, 0);
    Vector3 c = axis::reflect(a, b);
    EXPECT_FLOAT_EQ(c.x, 1.0f);
    EXPECT_FLOAT_EQ(c.y, 1.0f);
    EXPECT_FLOAT_EQ(c.z, 0.0f);
}

TEST(Vector3, ProjectOntoOtherVector) {
    Vector3 a(3, 4, 0);
    Vector3 b(1, 0, 0);
    Vector3 c = axis::project(a, b);
    EXPECT_FLOAT_EQ(c.x, 3.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
    EXPECT_FLOAT_EQ(c.z, 0.0f);
}

TEST(Vector3, ProjectOntoNonUnitVectorWorks) {
    Vector3 a(2, 2, 0);
    Vector3 b(3, 0, 0);
    Vector3 c = axis::project(a, b);
    EXPECT_FLOAT_EQ(c.x, 2.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
    EXPECT_FLOAT_EQ(c.z, 0.0f);
}

TEST(Vector3, ProjectOntoZeroVectorThrows) {
    EXPECT_THROW(axis::project(Vector3{1, 2, 3}, Vector3()), std::runtime_error);
}

TEST(Vector3, RejectVectorFromOtherVector) {
    Vector3 a(3, 4, 0);
    Vector3 b(1, 0, 0);
    Vector3 c = axis::reject(a, b);
    EXPECT_FLOAT_EQ(c.x, 0.0f);
    EXPECT_FLOAT_EQ(c.y, 4.0f);
    EXPECT_FLOAT_EQ(c.z, 0.0f);
} 

TEST(Vector3, ProjectionEqualToRejectionOfSameVectors) {
    Vector3 a(3, 4, 0);
    Vector3 b(1, 0, 0);
    Vector3 c = axis::project(a, b);
    Vector3 d = axis::reject(a, b);
    EXPECT_TRUE(c.x + d.x == a.x);
    EXPECT_TRUE(c.y + d.y == a.y);
    EXPECT_TRUE(c.z + d.z == a.z);
}

TEST(Vector3, DotProductOfRejectionAndFromParamZero) {
    Vector3 a(3, 4, 0);
    Vector3 b(1, 0, 0);
    Vector3 c = axis::reject(a, b);
    EXPECT_NEAR(dot(c, b), 0.0f, 1e-4f);
}

TEST(Vector3, RejectFromAZeroVectorThrows) {
    EXPECT_THROW(axis::reject(Vector3{1, 2, 3}, Vector3()), std::runtime_error);
}

TEST(Vector3, TestLerpEqualityBasedOnT) {
    Vector3 a;
    Vector3 b(10, 20, 30);
    Vector3 c = axis::lerp(a, b, 0);
    Vector3 d = axis::lerp(a, b, 1);
    Vector3 e = axis::lerp(a, b, 0.5f);
    Vector3 f = axis::lerp(a, b, 2.0f);
    Vector3 g = axis::lerp(a, b, -1.0f);

    EXPECT_FLOAT_EQ(c.x, a.x);
    EXPECT_FLOAT_EQ(c.y, a.y);
    EXPECT_FLOAT_EQ(c.z, a.z);
    EXPECT_FLOAT_EQ(d.x, b.x);
    EXPECT_FLOAT_EQ(d.y, b.y);
    EXPECT_FLOAT_EQ(d.z, b.z);
    EXPECT_FLOAT_EQ(e.x, 5.0f);
    EXPECT_FLOAT_EQ(e.y, 10.0f);
    EXPECT_FLOAT_EQ(e.z, 15.0f);
    EXPECT_FLOAT_EQ(f.x, 20.0f);
    EXPECT_FLOAT_EQ(f.y, 40.0f);
    EXPECT_FLOAT_EQ(f.z, 60.0f);
    EXPECT_FLOAT_EQ(g.x, -10.0f);
    EXPECT_FLOAT_EQ(g.y, -20.0f);
    EXPECT_FLOAT_EQ(g.z, -30.0f);
}

TEST(Vector3, MinGivesCorrectVectors) {
    Vector3 a(1, 5, 3);
    Vector3 b(4, 2, 6);
    Vector3 c = axis::min(a, b);
    EXPECT_FLOAT_EQ(c.x, 1.0f);
    EXPECT_FLOAT_EQ(c.y, 2.0f);
    EXPECT_FLOAT_EQ(c.z, 3.0f);
}

TEST(Vector3, MaxGivesCorrectVectors) {
    Vector3 a(1, 5, 3);
    Vector3 b(4, 2, 6);
    Vector3 c = axis::max(a, b);
    EXPECT_FLOAT_EQ(c.x, 4.0f);
    EXPECT_FLOAT_EQ(c.y, 5.0f);
    EXPECT_FLOAT_EQ(c.z, 6.0f);
}

TEST(Vector3, CheckClampingOnVector) {
    Vector3 a(-5.0f, 5.0f, 15.0f);
    Vector3 b = axis::clamp(a, Vector3(), Vector3{10, 10, 10});
    EXPECT_FLOAT_EQ(b.x, 0.0f);
    EXPECT_FLOAT_EQ(b.y, 5.0f);
    EXPECT_FLOAT_EQ(b.z, 10.0f);
}