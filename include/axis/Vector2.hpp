#ifndef AXIS_VECTOR2_HPP
#define AXIS_VECTOR2_HPP

#include <cmath>
#include <stdexcept>

namespace axis {
    class Vector2 {
    public:
        float x, y;

        Vector2(Vector2&& other) noexcept : x(other.x), y(other.y) {}
        Vector2(const Vector2& other) : x(other.x), y(other.y) {}
        Vector2(float x, float y) : x(x), y(y) {}
        Vector2() : x(0), y(0) {}

        Vector2 operator+(const Vector2& other) const {
            Vector2 v(this->x + other.x, this->y + other.y);
            return v;
        }

        Vector2 operator-(const Vector2& other) const {
            Vector2 v(this->x - other.x, this->y - other.y);
            return v;
        }

        Vector2 operator*(float scalar) const {
            Vector2 v(this->x * scalar, this->y * scalar);
            return v;
        }
        friend Vector2 operator*(float scalar, const Vector2& v) {
            Vector2 vs(v.x * scalar, v.y * scalar);
            return vs;
        }

        float len() const { return std::sqrt((this->x*this->x) + (this->y*this->y)); }
        float lensq() const { return (this->x*this->x) + (this->y*this->y); }
        Vector2 normalized() const {
            Vector2 v = *this;
            float len = v.len();
            
            if (len == 0) throw std::runtime_error("Failed to divide by zero.");
                
            v.x /= len;
            v.y /= len;

            return v;
        }

        void normalize() {
            float len = this->len();

            if (len == 0) throw std::runtime_error("Failed to divide by zero.");

            this->x /= len;
            this->y /= len;
        }
    };

    inline float dot(const Vector2& a, const Vector2& b) { return a.x*b.x + a.y*b.y; }
    inline float distance(const Vector2& a, const Vector2& b) { 
        return std::sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
    }
    inline Vector2 reflect(const Vector2& velocity, const Vector2& normal) {
        float dt = dot(velocity, normal);
        return velocity - (normal * 2.0f * dt);
    }
    inline Vector2 project(const Vector2& v, const Vector2& u) {
        float dt = dot(u, u);

        if (dt == 0.0f) throw std::runtime_error("Failed to divide by zero.");

        float scalar = dot(u, v) / dt;
        return Vector2{scalar * u.x, scalar * u.y};
    }
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
    inline Vector2 lerp(const Vector2& a, const Vector2& b, float t) { return a + (b - a) * t; }
}

#endif