#ifndef AXIS_VECTOR2_HPP
#define AXIS_VECTOR2_HPP

#include <cmath>

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
    };

    inline float dot(const Vector2& a, const Vector2& b) { return a.x*b.x + a.y*b.y; }
}

#endif