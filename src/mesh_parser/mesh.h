#ifndef MESH_H
#define MESH_H

#include <vector>
#include "vertex.h"

class Mesh {
private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> triangles; // size = 3 * tri count

public:
    Mesh(const std::vector<Vertex> vertices, std::vector<uint32_t> triangles) :
        vertices(vertices),
        triangles(triangles) {};
};

#endif
