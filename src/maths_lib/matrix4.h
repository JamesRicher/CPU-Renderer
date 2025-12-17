#ifndef MATRIX4_H
#define MATRIX4_H

#include "vector4.h"

template <typename T>
struct Matrix4 {
    T data[4][4];

    Matrix4<T>(T data[4][4]) : data(data) {}

    Vector4<T> mult(const Vector4<T>& v) const;
};

template<typename T>
Vector4<T> Matrix4<T>::mult(const Vector4<T>& v) const {
    T[4];
    int coord;
    for (int row=0; row < 4; row++) {
        coord=0;
        for (int col=0; col < 4; col++) {
            coord += data[row][col]*v[col];
        }
        T[row] = coord;
    }
}

#endif