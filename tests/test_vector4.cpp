#include <gtest/gtest.h>
#include <axis/Vector4.hpp>

using axis::Vector4;

TEST(Vector4, NormalizeZeroVectorThrows) {
    EXPECT_THROW(Vector4().normalized(), std::runtime_error);
}