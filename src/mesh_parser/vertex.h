#ifndef VERTEX_H
#define VERTEX_H

#include "vector3.h"
#include "vector2.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Vertex {
    Vector3<float> position;
    Vector3<float> normal;
    Vector2<float> uv;
};

inline void to_json(json& j, const Vertex& vert) {
    j = json{{"position", vert.position}, {"normal", vert.normal}, {"uv", vert.uv}};
}

inline void from_json(const json& j, Vertex& vert) {
    j.at("position").get_to(vert.position);
    j.at("normal").get_to(vert.normal);
    j.at("uv").get_to(vert.uv);
}

#endif
