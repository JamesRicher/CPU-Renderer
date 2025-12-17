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
    Mesh loadFromJson(const char* filename);

private:
    std::filesystem::path asset_root;
};


#endif