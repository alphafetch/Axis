#ifndef AXIS_MATRIX3_HPP
#define AXIS_MATRIX3_HPP

#include <array>
#include <cstddef>
#include <stdexcept>

namespace axis {
    class Matrix3 {
    private:
        std::array<std::array<float, 3>, 3> matrix;
    public:
        float& operator()(size_t x, size_t y) {
            if (x <= 2 && x >= 0
                && y <= 2 && y >= 0) {
                return matrix[x][y];
            } else {
                throw std::out_of_range("AXIS: Matrix3 indices out of range.");
            }
        }
    };
}

#endif