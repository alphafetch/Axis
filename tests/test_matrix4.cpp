#include <gtest/gtest.h>
#include <axis/Matrix4.hpp>

using axis::Matrix4;

TEST(Matrix4, DeterminantOfIdentityIsOne) {
    EXPECT_NEAR(axis::determinant(Matrix4()), 1.0f, 1e-5f);
}

TEST(Matrix4, DeterminantOfDiagonalIsProductOfDiagonal) {
    Matrix4 m(2, 0, 0, 0,
              0, 3, 0, 0,
              0, 0, 4, 0,
              0, 0, 0, 5);
    EXPECT_NEAR(axis::determinant(m), 120.0f, 1e-3f);
}

TEST(Matrix4, DeterminantOfSingularMatrixIsZero) {
    // Rows 0 and 1 are identical, so the determinant must be 0
    Matrix4 m(1, 2, 3, 4,
              1, 2, 3, 4,
              5, 6, 7, 8,
              2, 0, 1, 3);
    EXPECT_NEAR(axis::determinant(m), 0.0f, 1e-4f);
}

TEST(Matrix4, DeterminantKnownValue) {
    // Value checked against numpy.linalg.det
    Matrix4 m(1, 2, 0, 1,
              0, 1, 3, 2,
              4, 0, 1, 1,
              2, 1, 0, 3);
    EXPECT_NEAR(axis::determinant(m), 58.0f, 1e-3f);
}
