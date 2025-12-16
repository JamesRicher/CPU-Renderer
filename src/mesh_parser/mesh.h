#ifndef MESH_H
#define MESH_H

#include <vector>
#include "vertex.h"

class Mesh {
private:
    std::vector<Vertex> vertices;
    std::vector<uint16_t> triangles; // size = 3 * tri count

public:
    Mesh() = default;
};

#endif
