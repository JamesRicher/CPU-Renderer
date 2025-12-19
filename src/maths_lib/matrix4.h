#ifndef MATRIX4_H
#define MATRIX4_H

#include "vector4.h"

template <typename T>
struct Matrix4 {
    T data[4][4];

    constexpr Matrix4() : data{
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    } {}
    Matrix4(T data[4][4]);

    static constexpr Matrix4 identity() { return Matrix4(); }

    Vector4<T> mult(const Vector4<T>& v) const;
};

template<typename T>
Matrix4<T>::Matrix4(T data[4][4]) {
    for (int row=0; row<4; row++)
        for (int col=0; col<4; col++)
            this->data[row][col] = data[row][col];
}

template<typename T>
Vector4<T> Matrix4<T>::mult(const Vector4<T>& v) const {
    Vector4<T> result;
    T coord;
    for (int row=0; row < 4; row++) {
        coord=0;
        for (int col=0; col < 4; col++) {
            coord += data[row][col]*v[col];
        }
        result[row] = coord;
    }

    return result;
}

#endif