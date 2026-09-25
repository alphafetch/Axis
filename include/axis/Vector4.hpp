#ifndef AXIS_VECTOR4_HPP
#define AXIS_VECTOR4_HPP

#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace axis {
    class Vector4 {
    public:
        float x, y, z, w;
        
        Vector4(Vector4&& other) noexcept : x(other.x), y(other.y), z(other.z), w(other.w) {}
        Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
        Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
        Vector4() : x(0), y(0), z(0), w(0) {}

        Vector4 operator+(const Vector4& other) const {
            Vector4 v(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
            return v;
        }

        Vector4 operator-(const Vector4& other) const {
            Vector4 v(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
            return v;
        }

        Vector4 operator*(float scalar) const {
            Vector4 v(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
            return v;
        }
        friend Vector4 operator*(float scalar, const Vector4& v) {
            Vector4 v(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
            return v;
        }

        float len() const { return std::sqrt((this->x*this->x) + (this->y*this->y) + (this->z*this->z) + (this->w*this->w)); }
        float lensq() const { return (this->x*this->x) + (this->y*this->y) + (this->z*this->z) + (this->w*this->w); }
        Vector4 normalized() const {
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
    inline Vector4 reflect(const Vector4& velocity, const Vector4& normal) {
        float dt = dot(velocity, normal);
        return velocity - (normal * 2.0f * dt);
    }
    inline Vector4 project(const Vector4& v, const Vector4& u) {
        float dt = dot(u, u);

        if (dt == 0.0f) throw std::runtime_error("Failed to divide by zero.");

        float scalar = dot(u, v) / dt;
        return Vector4{scalar * u.x, scalar * u.y, scalar * u.z, scalar * u.w};
    }
    inline Vector4 reject(const Vector4& a, const Vector4& b) {
        float dtAB = dot(a, b);
        float dtBB = dot(b, b);

        if (dtBB == 0.0f) throw std::runtime_error("Failed to divide by zero.");

        float scalarFactor = dtAB / dtBB;

        Vector4 rejection;
        rejection.x = a.x - (scalarFactor * b.x);
        rejection.y = a.y - (scalarFactor * b.y);
        rejection.z = a.z - (scalarFactor * b.z);
        rejection.w = a.w - (scalarFactor * b.w);

        return rejection;
    }
    inline Vector4 lerp(const Vector4& a, const Vector4& b, float t) { return a + (b - a) * t; }
    inline Vector4 min(const Vector4& a, const Vector4& b) { return Vector4{std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w)}; }
    inline Vector4 max(const Vector4& a, const Vector4& b) { return Vector4{std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w)}; }
    inline Vector4 clamp(const Vector4& v, const Vector4& l, const Vector4& h) {
        return Vector4{std::clamp(v.x, l.x, h.x), std::clamp(v.y, l.y, h.y), std::clamp(v.z, l.z, h.z), std::clamp(v.w, l.w, h.w)};
    }
}

#endif