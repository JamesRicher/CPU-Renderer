#ifndef MESH_H
#define MESH_H

#include <vector>
#include "vector3.h"
#include "vector2.h"
#include "vertex.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> triangles; // size = 3 * tri count

    Mesh() = default;
    Mesh(const std::vector<Vertex> vertices, std::vector<uint32_t> triangles) :
        vertices(vertices),
        triangles(triangles) {};
};

inline void to_json(json& j, const Mesh& mesh) {
    j = json{{"vertices", mesh.vertices}, {"triangles", mesh.triangles}};
}

inline void from_json(const json& j, Mesh& mesh) {
    j.at("vertices").get_to(mesh.vertices);
    j.at("triangles").get_to(mesh.triangles);
}

#endif
