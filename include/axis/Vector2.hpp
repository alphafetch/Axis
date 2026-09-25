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

        Vector2 operator+(Vector2& other) {
            Vector2 v(this->x + other.x, this->y + other.y);
            return v;
        }

        Vector2 operator-(Vector2& other) {
            Vector2 v(this->x - other.x, this->y - other.y);
            return v;
        }

        Vector2 operator*(float scalar) {
            Vector2 v(this->x * scalar, this->y * scalar);
            return v;
        }

        float len() { return std::sqrt((this->x*this->x) + (this->y*this->y)); }
        float lensq() { return (this->x*this->x) + (this->y*this->y); }
        Vector2 normalized() {
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
}

#endif