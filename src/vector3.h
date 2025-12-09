#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

template <typename T>
struct Vector3 {
    T x,y,z;
    
    Vector3() : x(0), y(0), z(0) {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    T magnitude() const;
    void normalise();
};

template <typename T>
T Vector3<T>::magnitude() const { return std::sqrt(x*x + y*y + z*z); }

template <typename T>
void Vector3<T>::normalise() {
    T mag = magnitude();
    x /= mag;
    y /= mag;
    z /= mag;
}

template <typename T>
Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b) {
    return Vector3<T>(a.x+b.x,a.y+b.y,a.z+b.z); 
}

template <typename T>
Vector3<T> operator+(const Vector3<T>& a, T b) {
    return Vector3<T>(a.x+b, a.y+b, a.z+b);
}

template <typename T>
Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b) {
    return Vector3<T>(a.x-b.x,a.y-b.y,a.z-b.z); 
}

template <typename T>
Vector3<T> operator/(const Vector3<T>& a, T b) {
    return Vector3<T>(a.x/b, a.y/b, a.z/b);
}

#endif
