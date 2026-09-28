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
        Matrix3() : matrix{{ {1,0,0}, {0,1,0}, {0,0,1} }} {}

        float& operator()(size_t x, size_t y) {
            if (x <= 2 && y <= 2) {
                return matrix[x][y];
            } else {
                throw std::out_of_range("AXIS: Matrix3 indices out of range.");
            }
        }

        const float& operator()(size_t x, size_t y) const {
            if (x <= 2 && y <= 2) {
                return matrix[x][y];
            } else {
                throw std::out_of_range("AXIS: Matrix3 indices out of range.");
            }
        }

        const Matrix3 operator*(const Matrix3& other) const {
            Matrix3 m;
            
            for (size_t i = 0; i < 3; i++) {
                for (size_t j = 0; j < 3; j++) {
                    float sum = 0.0f;
                    for (size_t k = 0; k < 3; k++) {
                        sum += (*this)(i, k) * other(k, j);
                    }
                    m(i, j) = sum;
                }
            }

            return m;
        }

        static Matrix3 identity() {
            Matrix3 m;
            m(0, 0) = 1.0f;
            m(1, 1) = 1.0f;
            m(2, 2) = 1.0f;

            return m;
        }
    };
}

#endif