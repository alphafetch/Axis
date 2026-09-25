#ifndef AXIS_VECTOR4_HPP
#define AXIS_VECTOR4_HPP

#include <cmath>
#include <stdexcept>

namespace axis {
    class Vector4 {
    public:
        float x, y, z, w;
        
        Vector4(Vector4&& other) noexcept : x(other.x), y(other.y), z(other.z), w(other.w) {}
        Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
        Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
        Vector4() : x(0), y(0), z(0), w(0) {}

        Vector4 operator+(Vector4& other) {
            Vector4 v(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
            return v;
        }

        Vector4 operator-(Vector4& other) {
            Vector4 v(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
            return v;
        }

        Vector4 operator*(float scalar) {
            Vector4 v(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
            return v;
        }

        float len() { return std::sqrt((this->x*this->x) + (this->y*this->y) + (this->z*this->z) + (this->w*this->w)); }
        float lensq() { return (this->x*this->x) + (this->y*this->y) + (this->z*this->z) + (this->w*this->w); }
        Vector4 normalized() {
            Vector4 v = *this;
            float len = v.len();
            v.x /= len;
            v.y /= len;
            v.z /= len;
            v.w /= len;

            return v;
        }

        void normalize() {
            float len = this->len();

            if (len == 0) throw std::runtime_error("Failed to divide by zero.");

            this->x /= len;
            this->y /= len;
            this->z /= len;
            this->w /= len;
        }
    };

    inline float dot(const Vector4& a, const Vector4& b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; }
    inline float distance(const Vector4& a, const Vector4& b) { 
        return std::sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y) + (b.z - a.z)*(b.z - a.z) + (b.w - a.w)*(b.w - a.w));
    }
}

#endif