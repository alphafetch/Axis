#include <gtest/gtest.h>
#include <axis/Matrix3.hpp>

using axis::Matrix3;

TEST(Matrix3, DeterminantOfSingularMatrixIsZero) {
    axis::Matrix3 m(1, 2, 3,
                    4, 5, 6,
                    7, 8, 9);
    EXPECT_NEAR(axis::determinant(m), 0.0f, 1e-5f);
}

TEST(Matrix3, DeterminantKnownValue) {
    axis::Matrix3 m(2, 1, 3,
                    0, 4, 1,
                    5, 2, 6);
    EXPECT_NEAR(axis::determinant(m), -11.0f, 1e-4f);
}