/**
 * @file include/axis/Vector3.hpp
 * @brief Vector3 header for Axis math library
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef AXIS_VECTOR3_HPP
#define AXIS_VECTOR3_HPP

#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace axis {
    /// @brief 3D vector of floats with components (x, y, z)
    class Vector3 {
    public:
        float x, y, z; 
        
        /// @brief Move constructor for Vector3
        /// @param other Vector3 to move from
        Vector3(Vector3&& other) noexcept : x(other.x), y(other.y), z(other.z) {}
        /// @brief Copy constructor for Vector3
        /// @param other Vector3 to copy from
        Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}
        /// @brief Initialize a Vector3 with specified values
        /// @param x X value to initialize
        /// @param y Y value to initialize
        /// @param z Z value to initialize
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
        /// @brief Initialize a Vector3 with X=0 Y=0 Z=0
        Vector3() : x(0), y(0), z(0) {}

        /// @brief Add two vectors component-wise
        /// @param other Right-hand-side vector
        /// @return Sum of the two vectors
        Vector3 operator+(const Vector3& other) const {
            Vector3 v(this->x + other.x, this->y + other.y, this->z + other.z);
            return v;
        }

        /// @brief Subtract another vector from this one component-wise
        /// @param other Right-hand-side vector (subtracted from this vector)
        /// @return Difference (this - other)
        Vector3 operator-(const Vector3& other) const {
            Vector3 v(this->x - other.x, this->y - other.y, this->z - other.z);
            return v;
        }

        /// @brief Multiply this vector by a scalar (vector * scalar)
        /// @param scalar Float to scale by
        /// @return Scaled vector
        Vector3 operator*(float scalar) const {
            Vector3 v(this->x * scalar, this->y * scalar, this->z * scalar);
            return v;
        }
        /// @brief Multiply a vector by a scalar with the scalar on the left (scalar * vector)
        /// @param scalar Float to scale by
        /// @param v Vector to scale
        /// @return Scaled vector
        friend Vector3 operator*(float scalar, const Vector3& v) {
            Vector3 vs(v.x * scalar, v.y * scalar, v.z * scalar);
            return vs;
        }

        /// @brief Get the length (magnitude) of the vector
        /// @return Euclidean length, sqrt(x^2 + y^2 + z^2)
        float len() const { return std::sqrt((this->x*this->x) + (this->y*this->y) + (this->z*this->z)); }
        /// @brief Get the squared length of the vector (avoids the square root)
        /// @return x^2 + y^2 + z^2
        float lensq() const { return (this->x*this->x) + (this->y*this->y) + (this->z*this->z); }
        /// @brief Get a unit-length copy of this vector (this vector is unchanged)
        /// @return The normalized vector
        /// @throws std::runtime_error If the vector has zero length
        Vector3 normalized() const {
            Vector3 v = *this;
            float len = v.len();

            if (len == 0) throw std::runtime_error("Failed to divide by zero.");

            v.x /= len;
            v.y /= len;
            v.z /= len;

            return v;
        }

        /// @brief Normalize this vector in place to unit length
        /// @throws std::runtime_error If the vector has zero length
        void normalize() {
            float len = this->len();

            if (len == 0) throw std::runtime_error("Failed to divide by zero.");

            this->x /= len;
            this->y /= len;
            this->z /= len;
        }
    };

    /// @brief Dot product of two vectors
    /// @param a First vector in the product
    /// @param b Second vector in the product
    /// @return Dot product of the two inputted vectors
    inline float dot(const Vector3& a, const Vector3& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
    /// @brief Cross product of two vectors (not commutative: cross(a, b) = -cross(b, a))
    /// @param a First vector in the product
    /// @param b Second vector in the product
    /// @return A vector perpendicular to both a and b
    inline Vector3 cross(const Vector3& a, const Vector3& b) {
        return Vector3{
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }
    /// @brief Euclidean distance between two points
    /// @param a First point
    /// @param b Second point
    /// @return Distance between the two points
    inline float distance(const Vector3& a, const Vector3& b) { 
        return std::sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y) + (b.z - a.z)*(b.z - a.z));
    }
    /// @brief Reflect a vector off of a surface normal
    /// @param velocity The incoming vector to reflect
    /// @param normal The surface normal to reflect across (must be unit length for a correct result)
    /// @return The reflected vector
    inline Vector3 reflect(const Vector3& velocity, const Vector3& normal) {
        float dt = dot(velocity, normal);
        return velocity - (normal * 2.0f * dt);
    }
    /// @brief Project one vector onto another
    /// @param v The vector being projected
    /// @param u The vector being projected onto
    /// @return The projection of v onto u (parallel to u)
    /// @throws std::runtime_error If u has zero length
    inline Vector3 project(const Vector3& v, const Vector3& u) {
        float dt = dot(u, u);

        if (dt == 0.0f) throw std::runtime_error("Failed to divide by zero.");

        float scalar = dot(u, v) / dt;
        return Vector3{scalar * u.x, scalar * u.y, scalar * u.z};
    }
    /// @brief Get the component of one vector perpendicular to another
    /// @param a The vector being rejected
    /// @param b The vector being rejected from
    /// @return The component of a perpendicular to b (a minus the projection of a onto b)
    /// @throws std::runtime_error If b has zero length
    inline Vector3 reject(const Vector3& a, const Vector3& b) {
        float dtAB = dot(a, b);
        float dtBB = dot(b, b);

        if (dtBB == 0.0f) throw std::runtime_error("Failed to divide by zero.");

        float scalarFactor = dtAB / dtBB;

        Vector3 rejection;
        rejection.x = a.x - (scalarFactor * b.x);
        rejection.y = a.y - (scalarFactor * b.y);
        rejection.z = a.z - (scalarFactor * b.z);

        return rejection;
    }
    /// @brief Linearly interpolate between two vectors
    /// @param a The start vector (returned when t = 0)
    /// @param b The end vector (returned when t = 1)
    /// @param t Interpolation factor; not clamped, so values outside [0, 1] extrapolate
    /// @return The interpolated vector
    inline Vector3 lerp(const Vector3& a, const Vector3& b, float t) { return a + (b - a) * t; }
    /// @brief Component-wise minimum of two vectors
    /// @param a First vector
    /// @param b Second vector
    /// @return A vector containing the smaller of each component pair
    inline Vector3 min(const Vector3& a, const Vector3& b) { return Vector3{std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)}; }
    /// @brief Component-wise maximum of two vectors
    /// @param a First vector
    /// @param b Second vector
    /// @return A vector containing the larger of each component pair
    inline Vector3 max(const Vector3& a, const Vector3& b) { return Vector3{std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)}; }
    /// @brief Clamp each component of a vector between the matching components of two bounds
    /// @param v The vector to clamp
    /// @param l The lower bound (each component must be <= the matching component of h)
    /// @param h The upper bound
    /// @return The clamped vector
    inline Vector3 clamp(const Vector3& v, const Vector3& l, const Vector3& h) {
        return Vector3{std::clamp(v.x, l.x, h.x), std::clamp(v.y, l.y, h.y), std::clamp(v.z, l.z, h.z)};
    }
}

#endif
