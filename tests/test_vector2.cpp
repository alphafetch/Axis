#include <gtest/gtest.h>
#include <axis/Vector2.hpp>

using axis::Vector2;

TEST(Vector2, NormalizeZeroVectorThrows) {
    EXPECT_THROW(Vector2().normalized(), std::runtime_error);
}