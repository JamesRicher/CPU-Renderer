#ifndef MESH_PARSER_H
#define MESH_PARSER_H

#include "mesh.h"
#include "app_config.h"
#include "vector3.h"
#include <filesystem>
#include <string_view>
#include <vector>

class MeshParser {
public:
    MeshParser(AppConfig config);

    Mesh loadFromObj(const char* obj_rel_path);
    bool saveAsJson(const Mesh& mesh, const char* json_path);
    bool saveAsBinary(const Mesh& mesh, const char* binary_path);

private:
    std::filesystem::path asset_root;
};

//***** UTILS *****//
std::vector<std::string_view> split(const char* cstr);
bool toFloat(std::string_view sv, float& out);
Vector3<float> lineToVector3(std::vector<std::string_view> tokens);

#endif