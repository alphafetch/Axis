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

TEST(Vector3, NormalizeZeroVectorThrows) {
    EXPECT_THROW(Vector3().normalized(), std::runtime_error);
}