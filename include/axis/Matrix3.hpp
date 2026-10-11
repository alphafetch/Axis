/**
 * @file include/axis/Matrix3.hpp
 * @brief Matrix3 header for Axis math library
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef AXIS_MATRIX3_HPP
#define AXIS_MATRIX3_HPP

#include <array>
#include <cstddef>
#include <stdexcept>

// Required for matrix * vector
#include "Vector3.hpp"

namespace axis {
    /// @brief 3x3 float matrix stored in row-major order (matrix[row][column])
    class Matrix3 {
    private:
        std::array<std::array<float, 3>, 3> matrix;
    public:
        /// @brief Initialize a Matrix3 as the identity matrix
        Matrix3() : matrix{{ {1,0,0}, {0,1,0}, {0,0,1} }} {}
        /// @brief Initialize a Matrix3 with set values
        Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i) : 
            matrix{{ {a,b,c}, {d,e,f}, {g,h,i} }} {}

        /// @brief Access a mutable element of the matrix
        /// @param x Row index (0-2)
        /// @param y Column index (0-2)
        /// @return Reference to the element at (row, column)
        /// @throws std::out_of_range If either index is greater than 2
        float& operator()(size_t x, size_t y) {
            if (x <= 2 && y <= 2) {
                return matrix[x][y];
            } else {
                throw std::out_of_range("AXIS: Matrix3 indices out of range.");
            }
        }

        /// @brief Access a read-only element of the matrix
        /// @param x Row index (0-2)
        /// @param y Column index (0-2)
        /// @return Const reference to the element at (row, column)
        /// @throws std::out_of_range If either index is greater than 2
        const float& operator()(size_t x, size_t y) const {
            if (x <= 2 && y <= 2) {
                return matrix[x][y];
            } else {
                throw std::out_of_range("AXIS: Matrix3 indices out of range.");
            }
        }

        /// @brief Add two matrices element-wise
        /// @param other Right-hand-side matrix
        /// @return Sum of the two matrices
        Matrix3 operator+(const Matrix3& other) const {
            Matrix3 m;

            for (size_t i = 0; i < 3; i++) {
                for (size_t j = 0; j < 3; j++) {
                    m(i, j) = (*this)(i, j) + other(i, j);
                }
            }

            return m;
        }

        /// @brief Subtract another matrix from this one element-wise
        /// @param other Right-hand-side matrix (subtracted from this matrix)
        /// @return Difference (this - other)
        Matrix3 operator-(const Matrix3& other) const {
            Matrix3 m;

            for (size_t i = 0; i < 3; i++) {
                for (size_t j = 0; j < 3; j++) {
                    m(i, j) = (*this)(i, j) - other(i, j);
                }
            }

            return m;
        }

        /// @brief Matrix product of this matrix and another (this * other); not commutative
        /// @param other Right-hand-side matrix
        /// @return The product matrix
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

        /// @brief Matrix * vector with 3 dimensions
        /// @param v The vector multiplying this matrix
        /// @return The product Vector3
        Vector3 operator*(const Vector3& v) const {
            return Vector3 {
                (*this)(0, 0) * v.x + (*this)(0, 1) * v.y + (*this)(0, 2) * v.z,
                (*this)(1, 0) * v.x + (*this)(1, 1) * v.y + (*this)(1, 2) * v.z,
                (*this)(2, 0) * v.x + (*this)(2, 1) * v.y + (*this)(2, 2) * v.z
            };
        }

        /// @brief Transpose this matrix in place (swap rows and columns)
        void transpose() {
            Matrix3 m = *this;

            for (size_t i = 0; i < 3; i++) {
                for (size_t j = 0; j < 3; j++) {
                    (*this)(i, j) = m(j, i);
                }
            }
        }

        /// @brief Get a transposed copy of this matrix (this matrix is unchanged)
        /// @return The transposed matrix
        Matrix3 transposed() const {
            Matrix3 m;

            for (size_t i = 0; i < 3; i++) {
                for (size_t j = 0; j < 3; j++) {
                    m(i, j) = (*this)(j, i);
                }
            }

            return m;
        }

        /// @brief Get the 3x3 identity matrix (1s on the diagonal, 0s elsewhere)
        /// @return The identity matrix
        static Matrix3 identity() {
            Matrix3 m;
            m(0, 0) = 1.0f;
            m(1, 1) = 1.0f;
            m(2, 2) = 1.0f;

            return m;
        }
    };
        
    /// @brief Get the 3x3 determinant of the given matrix
    /// @param m The given matrix to find the determinant of
    inline double determinant(Matrix3& m) {
        double a = m(0, 0), b = m(0, 1), c = m(0, 2);
        double d = m(1, 0), e = m(1, 1), f = m(1, 2);
        double g = m(2, 0), h = m(2, 1), i = m(2, 2);

        return a * (e * i - f * h) -
               b * (d * i - f * g) + 
               c * (d * h - e * g);
    }
}

#endif
