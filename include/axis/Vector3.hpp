#ifndef AXIS_VECTOR3_HPP
#define AXIS_VECTOR3_HPP

namespace axis {
    class Vector3 {
    public:
        float x, y, z; 
        
        Vector3(Vector3&& other) noexcept : x(other.x), y(other.y), z(other.z) {}
        Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
        Vector3() : x(0), y(0), z(0) {}

        Vector3& operator+(Vector3& other) {
            Vector3 v(this->x + other.x, this->y + other.y, this->z + other.z);
            return v;
        }

        Vector3& operator-(Vector3& other) {
            Vector3 v(this->x - other.x, this->y - other.y, this->z - other.z);
            return v;
        }

        Vector3& operator*(float scalar) {
            Vector3 v(this->x * scalar, this->y * scalar, this->z * scalar);
            return v;
        }
    };
}

#endif