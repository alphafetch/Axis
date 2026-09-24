#ifndef AXIS_MATRIX4_HPP
#define AXIS_MATRIX4_HPP

#include <array>
#include <cstddef>
#include <stdexcept>

namespace axis {
    class Matrix4 {
    private:
        std::array<std::array<float, 4>, 4> matrix;
    public:
        float& operator()(size_t x, size_t y) {
            if (x <= 3 && x >= 0
                && y <= 3 && y >= 0) {
                return matrix[x][y];
            } else {
                throw std::out_of_range("AXIS: Matrix4 indices out of range.");
            }
        }
    };
}

#endif