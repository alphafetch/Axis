/**
 * @file include/axis/Matrix4.hpp
 * @brief Matrix4 header for Axis math library
 * 
 * SPDX-License-Identifier: MIT
 */

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
        Matrix4() : matrix{{ {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} }} {}

        float& operator()(size_t x, size_t y) {
            if (x <= 3 && y <= 3) {
                return matrix[x][y];
            } else {
                throw std::out_of_range("AXIS: Matrix4 indices out of range.");
            }
        }

        const float& operator()(size_t x, size_t y) const {
            if (x <= 2 && y <= 2) {
                return matrix[x][y];
            } else {
                throw std::out_of_range("AXIS: Matrix3 indices out of range.");
            }
        }

        const Matrix4 operator*(const Matrix4& other) const {
            Matrix4 m;
            
            for (size_t i = 0; i < 4; i++) {
                for (size_t j = 0; j < 4; j++) {
                    float sum = 0.0f;
                    for (size_t k = 0; k < 4; k++) {
                        sum += (*this)(i, k) * other(k, j);
                    }
                    m(i, j) = sum;
                }
            }

            return m;
        }

        Matrix4 transposed() const {
            Matrix4 m;

            for (size_t i = 0; i < 4; i++) {
                for (size_t j = 0; j < 4; j++) {
                    m(i, j) = (*this)(j, i);
                }
            }

            return m;
        }

        void transpose() {
            *this = transposed();
        }

        static Matrix4 identity() {
            Matrix4 m;
            m(0, 0) = 1.0f;
            m(1, 1) = 1.0f;
            m(2, 2) = 1.0f;
            m(3, 3) = 1.0f;

            return m;
        }
    };
}

#endif