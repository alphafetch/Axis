#ifndef TESTS_TEST_HELPERS_HPP
#define TESTS_TEST_HELPERS_HPP

#include <gtest/gtest.h>
#include <cmath>
#include <cstddef>
#include <axis/Matrix3.hpp>
#include <axis/Matrix4.hpp>

namespace axis_test {
    template <size_t N, typename Mat>
    ::testing::AssertionResult MatNear(const Mat& a, const Mat& b, float tol) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                if (std::fabs(a(i, j) - b(i, j)) > tol) {
                    return ::testing::AssertionFailure()
                        << "differs at (" << i << ", " << j << "): "
                        << a(i, j) << " vs " << b(i, j)
                        << " (tolerance " << tol << ")";
                }
            }
        }
        return ::testing::AssertionSuccess();
    }
}

inline ::testing::AssertionResult Mat3Near(const axis::Matrix3& a, const axis::Matrix3& b, float tol) {
    return axis_test::MatNear<3>(a, b, tol);
}

inline ::testing::AssertionResult Mat4Near(const axis::Matrix4& a, const axis::Matrix4& b, float tol) {
    return axis_test::MatNear<4>(a, b, tol);
}

#endif