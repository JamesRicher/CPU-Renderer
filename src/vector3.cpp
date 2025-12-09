#include "vector.h"
#include <cmath>

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

float Vector3::magnitude() const { return std::sqrt(x*x + y*y + z*z); }

void Vector3::normalise() {
    float mag = magnitude();
    x /= mag;
    y /= mag;
    z /= mag;
}

Vector3 operator+ (const Vector3& a, const Vector3& b) {
    return Vector3(a.x+b.x,a.y+b.y,a.z+b.z); 
}

Vector3 operator+ (const Vector3 a, const float& b) {
    return Vector3(a.x+b, a.y+b, a.z+b);
}

Vector3 operator- (const Vector3& a, const Vector3& b) {
    return Vector3(a.x-b.x,a.y-b.y,a.z-b.z); 
}

Vector3 operator/ (const Vector3& a, const float& b) {
    return Vector3(a.x/b, a.y/b, a.z/b);
}

