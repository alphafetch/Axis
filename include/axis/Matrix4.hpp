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

// Required for matrix * vector
#include "Vector4.hpp"

namespace axis {
    /// @brief 4x4 float matrix stored in row-major order (matrix[row][column])
    class Matrix4 {
    private:
        std::array<std::array<float, 4>, 4> matrix;
    public:
        /// @brief Initialize a Matrix4 as the identity matrix
        Matrix4() : matrix{{ {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} }} {}
        /// @brief Initialize a Matrix4 with set values
        Matrix4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p) : 
            matrix{{ {a,b,c,d}, {e,f,g,h}, {i,j,k,l}, {m,n,o,p} }} {}

        /// @brief Access a mutable element of the matrix
        /// @param x Row index (0-3)
        /// @param y Column index (0-3)
        /// @return Reference to the element at (row, column)
        /// @throws std::out_of_range If either index is greater than 3
        float& operator()(size_t x, size_t y) {
            if (x <= 3 && y <= 3) {
                return matrix[x][y];
            } else {
                throw std::out_of_range("AXIS: Matrix4 indices out of range.");
            }
        }

        /// @brief Access a read-only element of the matrix
        /// @param x Row index (0-3)
        /// @param y Column index (0-3)
        /// @return Const reference to the element at (row, column)
        /// @throws std::out_of_range If either index is greater than 3
        const float& operator()(size_t x, size_t y) const {
            if (x <= 3 && y <= 3) {
                return matrix[x][y];
            } else {
                throw std::out_of_range("AXIS: Matrix4 indices out of range.");
            }
        }

        /// @brief Add two matrices element-wise
        /// @param other Right-hand-side matrix
        /// @return Sum of the two matrices
        Matrix4 operator+(const Matrix4& other) const {
            Matrix4 m;

            for (size_t i = 0; i < 4; i++) {
                for (size_t j = 0; j < 4; j++) {
                    m(i, j) = (*this)(i, j) + other(i, j);
                }
            }

            return m;
        }

        /// @brief Subtract another matrix from this one element-wise
        /// @param other Right-hand-side matrix (subtracted from this matrix)
        /// @return Difference (this - other)
        Matrix4 operator-(const Matrix4& other) const {
            Matrix4 m;

            for (size_t i = 0; i < 4; i++) {
                for (size_t j = 0; j < 4; j++) {
                    m(i, j) = (*this)(i, j) - other(i, j);
                }
            }

            return m;
        }

        /// @brief Matrix product of this matrix and another (this * other); not commutative
        /// @param other Right-hand-side matrix
        /// @return The product matrix
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

        /// @brief Matrix * vector with 4 dimensions
        /// @param v The vector multiplying this matrix
        /// @return The product Vector4
        Vector4 operator*(const Vector4& v) const {
            return Vector4 {
                (*this)(0, 0) * v.x + (*this)(0, 1) * v.y + (*this)(0, 2) * v.z + (*this)(0, 3) * v.w,
                (*this)(1, 0) * v.x + (*this)(1, 1) * v.y + (*this)(1, 2) * v.z + (*this)(1, 3) * v.w,
                (*this)(2, 0) * v.x + (*this)(2, 1) * v.y + (*this)(2, 2) * v.z + (*this)(2, 3) * v.w,
                (*this)(3, 0) * v.x + (*this)(3, 1) * v.y + (*this)(3, 2) * v.z + (*this)(3, 3) * v.w
            };
        }

        /// @brief Get a transposed copy of this matrix (this matrix is unchanged)
        /// @return The transposed matrix
        Matrix4 transposed() const {
            Matrix4 m;

            for (size_t i = 0; i < 4; i++) {
                for (size_t j = 0; j < 4; j++) {
                    m(i, j) = (*this)(j, i);
                }
            }

            return m;
        }

        /// @brief Transpose this matrix in place (swap rows and columns)
        void transpose() {
            *this = transposed();
        }

        /// @brief Get the 4x4 identity matrix (1s on the diagonal, 0s elsewhere)
        /// @return The identity matrix
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
