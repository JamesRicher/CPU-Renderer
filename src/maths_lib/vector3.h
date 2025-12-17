#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

template <typename T = float>
struct Vector3 {
    T x,y,z;
    
    Vector3() : x(0), y(0), z(0) {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
    Vector3(T coords[3]) : x(coords[0]), y(coords[1]), z(coords[2]) {}

    T magnitude() const;
    void normalise();
    T dot(const Vector3<T>& v) const;
    Vector3 cross(const Vector3<T>& v) const;
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

template<typename T>
T Vector3<T>::dot(const Vector3<T>& v) const {
    return (x*v.x + y*v.y + z*v.z);
}

template<typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T>& v) const {
    T new_x = y*v.z - z-v.y;
    T new_y = z*v.x - x*v.z;
    T new_z = x*v.y - y*v.x;
    return Vector3<T>(new_x, new_y, new_z);
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


// SERIALISATION
template <typename T>
inline void to_json(json& j, const Vector3<T>& v) {
    j = json{{"x",v.x}, {"y",v.y}, {"z",v.z}};
}

template<typename T>
inline void from_json(const json& j, Vector3<T>& v) {
    j.at("x").get_to(v.x);
    j.at("y").get_to(v.y);
    j.at("z").get_to(v.z);
}

#endif
