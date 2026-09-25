#ifndef AXIS_VECTOR3_HPP
#define AXIS_VECTOR3_HPP

#include <cmath>
#include <stdexcept>

namespace axis {
    class Vector3 {
    public:
        float x, y, z; 
        
        Vector3(Vector3&& other) noexcept : x(other.x), y(other.y), z(other.z) {}
        Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
        Vector3() : x(0), y(0), z(0) {}

        Vector3 operator+(const Vector3& other) const {
            Vector3 v(this->x + other.x, this->y + other.y, this->z + other.z);
            return v;
        }

        Vector3 operator-(const Vector3& other) const {
            Vector3 v(this->x - other.x, this->y - other.y, this->z - other.z);
            return v;
        }

        Vector3 operator*(float scalar) const {
            Vector3 v(this->x * scalar, this->y * scalar, this->z * scalar);
            return v;
        }
        friend Vector3 operator*(float scalar, const Vector3& v) {
            Vector3 v(v.x * scalar, v.y * scalar, v.z * scalar);
            return v;
        }

        float len() const { return std::sqrt((this->x*this->x) + (this->y*this->y) + (this->z*this->z)); }
        float lensq() const { return (this->x*this->x) + (this->y*this->y) + (this->z*this->z); }
        Vector3 normalized() const {
            Vector3 v = *this;
            float len = v.len();

            if (len == 0) throw std::runtime_error("Failed to divide by zero.");

            v.x /= len;
            v.y /= len;
            v.z /= len;

            return v;
        }

        void normalize() {
            float len = this->len();

            if (len == 0) throw std::runtime_error("Failed to divide by zero.");

            this->x /= len;
            this->y /= len;
            this->z /= len;
        }
    };

    inline float dot(const Vector3& a, const Vector3& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
    inline Vector3 cross(const Vector3& a, const Vector3& b) {
        return Vector3{
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }
    inline float distance(const Vector3& a, const Vector3& b) { 
        return std::sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y) + (b.z - a.z)*(b.z - a.z));
    }
    inline Vector3 reflect(const Vector3& velocity, const Vector3& normal) {
        float dt = dot(velocity, normal);
        return velocity - (normal * 2.0f * dt);
    }
}

#endif