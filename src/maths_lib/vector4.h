#ifndef VECTOR4_H
#define VECTOR4_H

#include <cmath>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

template <typename T = float>
struct Vector4 {
    T x, y, z, w;

    Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    Vector4(T coords[4]) : x(coords[0]), y(coords[1]), z(coords[2]), w(coords[3]) {}

    T magnitude() const;
    void normalise();
    T dot(const Vector4<T>& v) const;
    void persp_divide();

    const T& operator[](int i) const;
    T& operator[](int i);
};

template <typename T>
T Vector4<T>::magnitude() const {
    return std::sqrt(x*x + y*y + z*z + w*w);
}

template <typename T>
void Vector4<T>::normalise() {
    T mag = magnitude();
    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;
}

template <typename T>
T Vector4<T>::dot(const Vector4<T>& v) const {
    return (x*v.x + y*v.y + z*v.z + w*v.w);
}

template <typename T>
void Vector4<T>::persp_divide() {
    x/=w;
    y/=w;
    z/=w;
    w/=w;
}

template <typename T>
Vector4<T> operator+(const Vector4<T>& a, const Vector4<T>& b) {
    return Vector4<T>(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w);
}

template <typename T>
Vector4<T> operator+(const Vector4<T>& a, T b) {
    return Vector4<T>(a.x+b, a.y+b, a.z+b, a.w+b);
}

template <typename T>
Vector4<T> operator-(const Vector4<T>& a, const Vector4<T>& b) {
    return Vector4<T>(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w);
}

template <typename T>
Vector4<T> operator/(const Vector4<T>& a, T b) {
    return Vector4<T>(a.x/b, a.y/b, a.z/b, a.w/b);
}

template<typename T>
const T& Vector4<T>::operator[](int i) const {
    return (&x)[i];
}

template<typename T>
T& Vector4<T>::operator[](int i) {
    return (&x)[i];
}

// SERIALISATION
template <typename T>
inline void to_json(json& j, const Vector4<T>& v) {
    j = json{{"x",v.x}, {"y",v.y}, {"z",v.z}, {"w",v.w}};
}

template <typename T>
inline void from_json(const json& j, Vector4<T>& v) {
    j.at("x").get_to(v.x);
    j.at("y").get_to(v.y);
    j.at("z").get_to(v.z);
    j.at("w").get_to(v.w);
}

#endif
