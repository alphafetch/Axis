// These tests mainly check that everything COMPILES when called on const objects.
// If an operator or method is missing its `const` qualifier, this file will fail
// to build. The EXPECTs make sure the results are also correct.
//
// For each result, the first and last components are checked.

#include <gtest/gtest.h>
#include <axis/Vector2.hpp>
#include <axis/Vector3.hpp>
#include <axis/Vector4.hpp>
#include <axis/Matrix3.hpp>
#include <axis/Matrix4.hpp>

TEST(ConstCorrectness, Vector2OperationsWorkOnConstObjects) {
    const axis::Vector2 a(3, 4);
    const axis::Vector2 b(1, 0);
    const axis::Vector2 zero;
    const axis::Vector2 normal(0, 1);

    const axis::Vector2 sum = a + b;
    const axis::Vector2 diff = a - b;
    const axis::Vector2 scaled = a * 2.0f;
    const axis::Vector2 scaledLeft = 2.0f * a;
    const axis::Vector2 unit = a.normalized();
    const axis::Vector2 reflected = axis::reflect(a, normal);
    const axis::Vector2 projected = axis::project(a, b);
    const axis::Vector2 rejected = axis::reject(a, b);
    const axis::Vector2 mid = axis::lerp(a, b, 0.5f);
    const axis::Vector2 lo = axis::min(a, b);
    const axis::Vector2 hi = axis::max(a, b);
    const axis::Vector2 clamped = axis::clamp(a, zero, axis::Vector2(2, 2));

    EXPECT_FLOAT_EQ(sum.x, 4.0f);        EXPECT_FLOAT_EQ(sum.y, 4.0f);
    EXPECT_FLOAT_EQ(diff.x, 2.0f);       EXPECT_FLOAT_EQ(diff.y, 4.0f);
    EXPECT_FLOAT_EQ(scaled.x, 6.0f);     EXPECT_FLOAT_EQ(scaled.y, 8.0f);
    EXPECT_FLOAT_EQ(scaledLeft.x, 6.0f); EXPECT_FLOAT_EQ(scaledLeft.y, 8.0f);
    EXPECT_FLOAT_EQ(unit.x, 0.6f);       EXPECT_FLOAT_EQ(unit.y, 0.8f);
    EXPECT_FLOAT_EQ(reflected.x, 3.0f);  EXPECT_FLOAT_EQ(reflected.y, -4.0f);
    EXPECT_FLOAT_EQ(projected.x, 3.0f);  EXPECT_FLOAT_EQ(projected.y, 0.0f);
    EXPECT_FLOAT_EQ(rejected.x, 0.0f);   EXPECT_FLOAT_EQ(rejected.y, 4.0f);
    EXPECT_FLOAT_EQ(mid.x, 2.0f);        EXPECT_FLOAT_EQ(mid.y, 2.0f);
    EXPECT_FLOAT_EQ(lo.x, 1.0f);         EXPECT_FLOAT_EQ(lo.y, 0.0f);
    EXPECT_FLOAT_EQ(hi.x, 3.0f);         EXPECT_FLOAT_EQ(hi.y, 4.0f);
    EXPECT_FLOAT_EQ(clamped.x, 2.0f);    EXPECT_FLOAT_EQ(clamped.y, 2.0f);

    EXPECT_FLOAT_EQ(a.len(), 5.0f);
    EXPECT_FLOAT_EQ(a.lensq(), 25.0f);
    EXPECT_FLOAT_EQ(axis::dot(a, b), 3.0f);
    EXPECT_FLOAT_EQ(axis::distance(a, zero), 5.0f);
}

TEST(ConstCorrectness, Vector3OperationsWorkOnConstObjects) {
    const axis::Vector3 a(1, 2, 2);
    const axis::Vector3 b(1, 0, 0);
    const axis::Vector3 zero;
    const axis::Vector3 normal(0, 1, 0);

    const axis::Vector3 sum = a + b;
    const axis::Vector3 diff = a - b;
    const axis::Vector3 scaled = a * 2.0f;
    const axis::Vector3 scaledLeft = 2.0f * a;
    const axis::Vector3 unit = a.normalized();
    const axis::Vector3 crossed = axis::cross(a, b);
    const axis::Vector3 reflected = axis::reflect(a, normal);
    const axis::Vector3 projected = axis::project(a, b);
    const axis::Vector3 rejected = axis::reject(a, b);
    const axis::Vector3 mid = axis::lerp(a, b, 0.5f);
    const axis::Vector3 lo = axis::min(a, b);
    const axis::Vector3 hi = axis::max(a, b);
    const axis::Vector3 clamped = axis::clamp(a, zero, axis::Vector3(1, 1, 1));

    EXPECT_FLOAT_EQ(sum.x, 2.0f);        EXPECT_FLOAT_EQ(sum.z, 2.0f);
    EXPECT_FLOAT_EQ(diff.x, 0.0f);       EXPECT_FLOAT_EQ(diff.z, 2.0f);
    EXPECT_FLOAT_EQ(scaled.x, 2.0f);     EXPECT_FLOAT_EQ(scaled.z, 4.0f);
    EXPECT_FLOAT_EQ(scaledLeft.x, 2.0f); EXPECT_FLOAT_EQ(scaledLeft.z, 4.0f);
    EXPECT_FLOAT_EQ(unit.x, 1.0f / 3.0f); EXPECT_FLOAT_EQ(unit.z, 2.0f / 3.0f);
    EXPECT_FLOAT_EQ(crossed.x, 0.0f);    EXPECT_FLOAT_EQ(crossed.z, -2.0f);
    EXPECT_FLOAT_EQ(reflected.x, 1.0f);  EXPECT_FLOAT_EQ(reflected.z, 2.0f);
    EXPECT_FLOAT_EQ(projected.x, 1.0f);  EXPECT_FLOAT_EQ(projected.z, 0.0f);
    EXPECT_FLOAT_EQ(rejected.x, 0.0f);   EXPECT_FLOAT_EQ(rejected.z, 2.0f);
    EXPECT_FLOAT_EQ(mid.x, 1.0f);        EXPECT_FLOAT_EQ(mid.z, 1.0f);
    EXPECT_FLOAT_EQ(lo.x, 1.0f);         EXPECT_FLOAT_EQ(lo.z, 0.0f);
    EXPECT_FLOAT_EQ(hi.x, 1.0f);         EXPECT_FLOAT_EQ(hi.z, 2.0f);
    EXPECT_FLOAT_EQ(clamped.x, 1.0f);    EXPECT_FLOAT_EQ(clamped.z, 1.0f);

    EXPECT_FLOAT_EQ(a.len(), 3.0f);
    EXPECT_FLOAT_EQ(a.lensq(), 9.0f);
    EXPECT_FLOAT_EQ(axis::dot(a, b), 1.0f);
    EXPECT_FLOAT_EQ(axis::distance(a, zero), 3.0f);
}

TEST(ConstCorrectness, Vector4OperationsWorkOnConstObjects) {
    const axis::Vector4 a(1, 2, 2, 4);
    const axis::Vector4 b(1, 0, 0, 0);
    const axis::Vector4 zero;
    const axis::Vector4 normal(0, 1, 0, 0);

    const axis::Vector4 sum = a + b;
    const axis::Vector4 diff = a - b;
    const axis::Vector4 scaled = a * 2.0f;
    const axis::Vector4 scaledLeft = 2.0f * a;
    const axis::Vector4 unit = a.normalized();
    const axis::Vector4 reflected = axis::reflect(a, normal);
    const axis::Vector4 projected = axis::project(a, b);
    const axis::Vector4 rejected = axis::reject(a, b);
    const axis::Vector4 mid = axis::lerp(a, b, 0.5f);
    const axis::Vector4 lo = axis::min(a, b);
    const axis::Vector4 hi = axis::max(a, b);
    const axis::Vector4 clamped = axis::clamp(a, zero, axis::Vector4(1, 1, 1, 1));

    EXPECT_FLOAT_EQ(sum.x, 2.0f);        EXPECT_FLOAT_EQ(sum.w, 4.0f);
    EXPECT_FLOAT_EQ(diff.x, 0.0f);       EXPECT_FLOAT_EQ(diff.w, 4.0f);
    EXPECT_FLOAT_EQ(scaled.x, 2.0f);     EXPECT_FLOAT_EQ(scaled.w, 8.0f);
    EXPECT_FLOAT_EQ(scaledLeft.x, 2.0f); EXPECT_FLOAT_EQ(scaledLeft.w, 8.0f);
    EXPECT_FLOAT_EQ(unit.x, 0.2f);       EXPECT_FLOAT_EQ(unit.w, 0.8f);
    EXPECT_FLOAT_EQ(reflected.x, 1.0f);  EXPECT_FLOAT_EQ(reflected.w, 4.0f);
    EXPECT_FLOAT_EQ(projected.x, 1.0f);  EXPECT_FLOAT_EQ(projected.w, 0.0f);
    EXPECT_FLOAT_EQ(rejected.x, 0.0f);   EXPECT_FLOAT_EQ(rejected.w, 4.0f);
    EXPECT_FLOAT_EQ(mid.x, 1.0f);        EXPECT_FLOAT_EQ(mid.w, 2.0f);
    EXPECT_FLOAT_EQ(lo.x, 1.0f);         EXPECT_FLOAT_EQ(lo.w, 0.0f);
    EXPECT_FLOAT_EQ(hi.x, 1.0f);         EXPECT_FLOAT_EQ(hi.w, 4.0f);
    EXPECT_FLOAT_EQ(clamped.x, 1.0f);    EXPECT_FLOAT_EQ(clamped.w, 1.0f);

    EXPECT_FLOAT_EQ(a.len(), 5.0f);
    EXPECT_FLOAT_EQ(a.lensq(), 25.0f);
    EXPECT_FLOAT_EQ(axis::dot(a, b), 1.0f);
    EXPECT_FLOAT_EQ(axis::distance(a, zero), 5.0f);
}

TEST(ConstCorrectness, Matrix3OperationsWorkOnConstObjects) {
    const axis::Matrix3 a(1, 2, 3,
                          4, 5, 6,
                          7, 8, 10);
    const axis::Matrix3 identity;
    const axis::Vector3 unitX(1, 0, 0);

    const axis::Matrix3 sum = a + identity;
    const axis::Matrix3 diff = a - identity;
    const axis::Matrix3 product = a * identity;
    const axis::Vector3 firstColumn = a * unitX;
    const axis::Matrix3 transposed = a.transposed();

    EXPECT_FLOAT_EQ(sum(0, 0), 2.0f);
    EXPECT_FLOAT_EQ(sum(2, 2), 11.0f);
    EXPECT_FLOAT_EQ(diff(0, 0), 0.0f);
    EXPECT_FLOAT_EQ(diff(2, 2), 9.0f);
    EXPECT_FLOAT_EQ(product(2, 2), 10.0f);
    EXPECT_FLOAT_EQ(firstColumn.x, 1.0f);
    EXPECT_FLOAT_EQ(firstColumn.y, 4.0f);
    EXPECT_FLOAT_EQ(firstColumn.z, 7.0f);
    EXPECT_FLOAT_EQ(transposed(0, 2), 7.0f);
    EXPECT_NEAR(axis::determinant(a), -3.0f, 1e-4f);
}

TEST(ConstCorrectness, Matrix4OperationsWorkOnConstObjects) {
    const axis::Matrix4 m(1,  2,  3,  4,
                          5,  6,  7,  8,
                          9,  10, 11, 12,
                          13, 14, 15, 16);
    const axis::Matrix4 identity;
    const axis::Vector4 unitW(0, 0, 0, 1);

    const axis::Matrix4 sum = m + identity;
    const axis::Matrix4 diff = m - identity;
    const axis::Matrix4 product = m * identity;
    const axis::Vector4 lastColumn = m * unitW;
    const axis::Matrix4 transposed = m.transposed();

    EXPECT_FLOAT_EQ(sum(0, 0), 2.0f);
    EXPECT_FLOAT_EQ(sum(3, 3), 17.0f);
    EXPECT_FLOAT_EQ(diff(0, 0), 0.0f);
    EXPECT_FLOAT_EQ(diff(3, 3), 15.0f);
    EXPECT_FLOAT_EQ(product(3, 3), 16.0f);
    EXPECT_FLOAT_EQ(lastColumn.x, 4.0f);
    EXPECT_FLOAT_EQ(lastColumn.y, 8.0f);
    EXPECT_FLOAT_EQ(lastColumn.z, 12.0f);
    EXPECT_FLOAT_EQ(lastColumn.w, 16.0f);
    EXPECT_FLOAT_EQ(transposed(0, 3), 13.0f);
    EXPECT_FLOAT_EQ(transposed(3, 0), 4.0f);
    EXPECT_NEAR(axis::determinant(m), 0.0f, 1e-4f);
}
