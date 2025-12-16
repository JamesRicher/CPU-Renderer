#ifndef VERTEX_H
#define VERTEX_H

#include "vector3.h"
#include "vector2.h"

struct Vertex {
    Vector3<float> position;
    Vector3<float> normal;
    Vector2<float> uv;
};

#endif
