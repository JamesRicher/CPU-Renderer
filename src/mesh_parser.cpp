#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string_view>
#include <cctype>
#include <charconv>

#include "mesh_parser.h"
#include "app_config.h"
#include "vector3.h"
#include "mesh.h"

MeshParser::MeshParser(AppConfig config) : asset_root(config.asset_root) {}

Mesh MeshParser::loadFromObj(const char* obj_rel_path) {
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

    // read in the vertex data into the three arrays
    while (obj_stream.good()) {
        char line[256];
        obj_stream.getline(line, 256);
        if (line[0] == '\0')
            continue;

        auto tokenised_line = split(line);
        if (tokenised_line[0] == "v")
            positions.push_back(lineToVector3(tokenised_line));
        else if (tokenised_line[0] == "vn") {
            normals.push_back(lineToVector3(tokenised_line));
        }
        else if (tokenised_line[0] == "vt") {
            float coords[2];
            for (int i=0; i<2; i++) {
                toFloat(tokenised_line[i+1], coords[i]);
            }

            texcoords.emplace_back(coords);
        }
        else if (tokenised_line[0] == "s" || tokenised_line[0] == "f") {
            break;
        }
    }

    // now we have extracted the raw data, form the triangles and vertices
    obj_stream.clear();
    obj_stream.seekg(0);
    while (obj_stream.good()){
        char line[256];
        obj_stream.getline(line, 256);
        if (line[0] == '\0')
            continue;

        auto tokenised_line = split(line);
        if (tokenised_line[0] == "f") {
            
        }
    }

    Mesh mesh;
    return mesh;
}

bool MeshParser::saveAsJson(const Mesh& mesh, const char* json_path) {
    return false;
}

bool MeshParser::saveAsBinary(const Mesh& mesh, const char* binary_path) {
    return false;
}

//***** INTERNAL *****//

//***** UTILS *****//
std::vector<std::string_view> split(const char* cstr) {
    std::vector<std::string_view> tokens;
    const char* start = cstr;

    while (start) {
        while(*start && std::isspace(*start)) ++start;

        if (!*start) break;
        
        const char* end = start;
        while (*end && !std::isspace(*end)) ++end;
        
        tokens.emplace_back(start, end-start);
        start=end;
    }

    return tokens;
}

bool toFloat(std::string_view sv, float& out) {
    char* end;
    out = std::strtof(sv.data(), &end);

    if (end != sv.data() + sv.size()) {
        std::cerr << "Parse error" << std::endl;
        return false;
    }
    else {
        std::cout << out << std::endl;
        return true;
    }
}

Vector3<float> lineToVector3(std::vector<std::string_view> tokens) {
    float coords[3];
    for (int i=0; i < 3; i++)
        toFloat(tokens[i+1], coords[i]);

    return Vector3<float>(coords);
}