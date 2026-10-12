/**
 * @file include/axis/Vector2.hpp
 * @brief Vector2 header for Axis math library
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef AXIS_VECTOR2_HPP
#define AXIS_VECTOR2_HPP

#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace axis {
    /// @brief 2D vector of floats with components (x, y)
    class Vector2 {
    public:
        float x, y;

        /// @brief Initialize a Vector2 with specified values
        /// @param x X value to initialize
        /// @param y Y value to initialize
        Vector2(float x, float y) : x(x), y(y) {}
        /// @brief Initialize a Vector2 with X=0 Y=0
        Vector2() : x(0), y(0) {}

        /// @brief Add two vectors component-wise
        /// @param other Right-hand-side vector
        /// @return Sum of the two vectors
        Vector2 operator+(const Vector2& other) const {
            Vector2 v(this->x + other.x, this->y + other.y);
            return v;
        }

        /// @brief Subtract another vector from this one component-wise
        /// @param other Right-hand-side vector (subtracted from this vector)
        /// @return Difference (this - other)
        Vector2 operator-(const Vector2& other) const {
            Vector2 v(this->x - other.x, this->y - other.y);
            return v;
        }

        /// @brief Multiply this vector by a scalar (vector * scalar)
        /// @param scalar Float to scale by
        /// @return Scaled vector
        Vector2 operator*(float scalar) const {
            Vector2 v(this->x * scalar, this->y * scalar);
            return v;
        }
        /// @brief Multiply a vector by a scalar with the scalar on the left (scalar * vector)
        /// @param scalar Float to scale by
        /// @param v Vector to scale
        /// @return Scaled vector
        friend Vector2 operator*(float scalar, const Vector2& v) {
            Vector2 vs(v.x * scalar, v.y * scalar);
            return vs;
        }

        /// @brief Get the length (magnitude) of the vector
        /// @return Euclidean length, sqrt(x^2 + y^2)
        float len() const { return std::sqrt((this->x*this->x) + (this->y*this->y)); }
        /// @brief Get the squared length of the vector (avoids the square root)
        /// @return x^2 + y^2
        float lensq() const { return (this->x*this->x) + (this->y*this->y); }
        /// @brief Get a unit-length copy of this vector (this vector is unchanged)
        /// @return The normalized vector
        /// @throws std::runtime_error If the vector has zero length
        Vector2 normalized() const {
            Vector2 v = *this;
            float len = v.len();
            
            if (len == 0) throw std::runtime_error("Failed to divide by zero.");
                
            v.x /= len;
            v.y /= len;

            return v;
        }

        /// @brief Normalize this vector in place to unit length
        /// @throws std::runtime_error If the vector has zero length
        void normalize() {
            float len = this->len();

            if (len == 0) throw std::runtime_error("Failed to divide by zero.");

            this->x /= len;
            this->y /= len;
        }
    };

    /// @brief Dot product of two vectors
    /// @param a First vector in the product
    /// @param b Second vector in the product
    /// @return Dot product of the two inputted vectors
    inline float dot(const Vector2& a, const Vector2& b) { return a.x*b.x + a.y*b.y; }
    /// @brief Euclidean distance between two points
    /// @param a First point
    /// @param b Second point
    /// @return Distance between the two points
    inline float distance(const Vector2& a, const Vector2& b) { 
        return std::sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
    }
    /// @brief Reflect a vector off of a surface normal
    /// @param velocity The incoming vector to reflect
    /// @param normal The surface normal to reflect across (must be unit length for a correct result)
    /// @return The reflected vector
    inline Vector2 reflect(const Vector2& velocity, const Vector2& normal) {
        float dt = dot(velocity, normal);
        return velocity - (normal * 2.0f * dt);
    }
    /// @brief Project one vector onto another
    /// @param v The vector being projected
    /// @param u The vector being projected onto
    /// @return The projection of v onto u (parallel to u)
    /// @throws std::runtime_error If u has zero length
    inline Vector2 project(const Vector2& v, const Vector2& u) {
        float dt = dot(u, u);

        if (dt == 0.0f) throw std::runtime_error("Failed to divide by zero.");

        float scalar = dot(u, v) / dt;
        return Vector2{scalar * u.x, scalar * u.y};
    }
    /// @brief Get the component of one vector perpendicular to another
    /// @param a The vector being rejected
    /// @param b The vector being rejected from
    /// @return The component of a perpendicular to b (a minus the projection of a onto b)
    /// @throws std::runtime_error If b has zero length
    inline Vector2 reject(const Vector2& a, const Vector2& b) {
        float dtAB = dot(a, b);
        float dtBB = dot(b, b);

        if (dtBB == 0.0f) throw std::runtime_error("Failed to divide by zero.");

        float scalarFactor = dtAB / dtBB;

        Vector2 rejection;
        rejection.x = a.x - (scalarFactor * b.x);
        rejection.y = a.y - (scalarFactor * b.y);

        return rejection;
    }
    /// @brief Linearly interpolate between two vectors
    /// @param a The start vector (returned when t = 0)
    /// @param b The end vector (returned when t = 1)
    /// @param t Interpolation factor; not clamped, so values outside [0, 1] extrapolate
    /// @return The interpolated vector
    inline Vector2 lerp(const Vector2& a, const Vector2& b, float t) { return a + (b - a) * t; }
    /// @brief Component-wise minimum of two vectors
    /// @param a First vector
    /// @param b Second vector
    /// @return A vector containing the smaller of each component pair
    inline Vector2 min(const Vector2& a, const Vector2& b) { return Vector2{std::min(a.x, b.x), std::min(a.y, b.y)}; }
    /// @brief Component-wise maximum of two vectors
    /// @param a First vector
    /// @param b Second vector
    /// @return A vector containing the larger of each component pair
    inline Vector2 max(const Vector2& a, const Vector2& b) { return Vector2{std::max(a.x, b.x), std::max(a.y, b.y)}; }
    /// @brief Clamp each component of a vector between the matching components of two bounds
    /// @param v The vector to clamp
    /// @param l The lower bound (each component must be <= the matching component of h)
    /// @param h The upper bound
    /// @return The clamped vector
    inline Vector2 clamp(const Vector2& v, const Vector2& l, const Vector2& h) {
        return Vector2{std::clamp(v.x, l.x, h.x), std::clamp(v.y, l.y, h.y)};
    }
}

#endif
