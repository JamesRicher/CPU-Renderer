#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

template <typename T = float>
struct Vector2 {
    T x,y;

    Vector2() : x(0), y(0) {}
    Vector2(T x, T y) : x(x), y(y) {}
    Vector2(T coords[2]) : x(coords[0]), y(coords[1]) {}

    T magnitude() const;
    void normalise();
};

template <typename T>
T Vector2<T>::magnitude() const { return std::sqrt(x*x + y*y); }

template <typename T>
void Vector2<T>::normalise() {
    T mag = magnitude();
    x/=mag;
    y/=mag;
}

template <typename T>
Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b) {
    return Vector2(a.x+b.x, a.y+b.y);
}

template <typename T>
Vector2<T> operator+(const Vector2<T>& a, T b) {
    return Vector2<T>(a.x+b, a.y+b);
}

template <typename T>
Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b) {
    return Vector2(a.x-b.x, a.y-b.y);
}

template <typename T>
Vector2<T> operator-(const Vector2<T>& a, T b) {
    return Vector2<T>(a.x-b, a.y-b);
}

#endif