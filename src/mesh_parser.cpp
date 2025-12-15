#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "mesh_parser.h"
#include "app_config.h"
#include "vector3.h"
#include "mesh.h"

MeshParser::MeshParser(AppConfig config) : asset_root(config.asset_root) {}

Mesh MeshParser::loadFromObj(const char* obj_rel_path) {
    Mesh mesh;
    std::vector<Vector3<float>> positions;
    std::vector<Vector3<float>> texcoords;
    std::vector<Vector3<float>> normals;

    // open the obj file
    std::ifstream obj_stream;
    obj_stream.open(asset_root / obj_rel_path);
    if (!obj_stream.good()) {
        std::cerr << "ERROR: problem reading the obj file supplied" << std::endl;
        exit(1);
    }

    while (obj_stream.good()) {
        char line[256];
        obj_stream.getline(line, 256);
        std::cout << line << std::endl;
    }

    std::cout << std::filesystem::current_path().c_str() << std::endl;

    return mesh;
}

bool MeshParser::saveAsJson(const Mesh& mesh, const char* json_path) {
    return false;
}

bool MeshParser::saveAsBinary(const Mesh& mesh, const char* binary_path) {
    return false;
}
