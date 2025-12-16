#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string_view>
#include <cctype>
#include <charconv>
#include <unordered_map>

#include "mesh_parser.h"
#include "app_config.h"
#include "vector3.h"
#include "mesh.h"
#include "vertex_key.h"
#include "vertex_key_hash.h"

MeshParser::MeshParser(AppConfig config) : asset_root(config.asset_root) {}

Mesh MeshParser::loadFromObj(const char* obj_rel_path) {
    std::vector<Vector3<float>> positions, normals, texcoords;

    // open the obj file
    std::ifstream obj_stream;
    obj_stream.open(asset_root / obj_rel_path);
    if (!obj_stream.good()) {
        std::cerr << "ERROR: problem reading the obj file supplied" << std::endl;
        throw std::runtime_error("Failed to load OBJ");
    }

    // read in the raw geometry data 
    readVertexData(obj_stream, positions, texcoords, normals);

    // create a map to store the vertices in
    std::unordered_map<VertexKey, uint32_t, VertexKeyHash> vertex_map;
    std::vector<Vertex> vertex_buffer;
    std::vector<uint32_t> triangle_buffer;

    // reserve memory
    vertex_map.reserve(positions.size());
    vertex_buffer.reserve(positions.size());
    triangle_buffer.reserve(positions.size() * 3);

    // now we have extracted the raw data, form the triangles and vertices
    obj_stream.clear();
    obj_stream.seekg(0);
    char line[256];

    while (obj_stream.getline(line, 256)){
        if (line[0] == '\0')
            continue;

        auto tokenised_line = split(line);
        if (tokenised_line[0] == "f") {
            // parse the three vertices on this line
            for (int i=1; i<4; i++) {
                Vector3<int> indices = extractTokens(tokenised_line[i]);
                VertexKey vertex_key;
                vertex_key.pos_i = --indices.x;
                vertex_key.tex_i = --indices.y;
                vertex_key.norm_i = --indices.z;

                // try insert the vertex in the dictionary
                auto [it, inserted] = vertex_map.emplace(vertex_key, vertex_buffer.size()); 

                if (inserted) {
                    // construct the new vertex
                    Vertex v;
                    v.position = positions[vertex_key.pos_i];
                    v.normal = normals[vertex_key.norm_i];
                    v.uv = texcoords[vertex_key.tex_i];

                    vertex_buffer.push_back(v);
                }

                triangle_buffer.push_back(it->second);
            }
        }
    }

    obj_stream.close();

    int loop_count = 1;
    for (int x: triangle_buffer) {
        std::cout << x << ", ";
        if (loop_count==0) std::cout << std::endl;
        loop_count = (loop_count +1)% 3;
    }

    Mesh mesh(vertex_buffer, triangle_buffer);
    return mesh;
}

bool MeshParser::saveAsJson(const Mesh& mesh, const char* json_path) {
    return false;
}

bool MeshParser::saveAsBinary(const Mesh& mesh, const char* binary_path) {
    return false;
}

//***** INTERNAL *****//
void MeshParser::readVertexData(
    std::ifstream& obj_stream,
    std::vector<Vector3<float>>& positions,
    std::vector<Vector3<float>>& texcoords,
    std::vector<Vector3<float>>& normals
) {
    char line[256];
    // read in the vertex data into the three arrays
    while (obj_stream.getline(line, 256)) {
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
    }
}

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
        return true;
    }
}

bool toInt(std::string_view sv, int& out) {
    char* end;
    out = std::strtoul(sv.data(), &end, 10);

    if (end != sv.data() + sv.size()) {
        std::cerr << "Parse error" << std::endl;
        return false;
    }
    else {
        return true;
    }
}

Vector3<float> lineToVector3(std::vector<std::string_view> tokens) {
    float coords[3];
    for (int i=0; i < 3; i++)
        toFloat(tokens[i+1], coords[i]);

    return Vector3<float>(coords);
}

// extracts the three indices from a sv such as 4/11/23 and packs them in a vector3
Vector3<int> extractTokens(std::string_view sv) {
    const char* start = sv.data();
    const char* end = start;
    const char* limit = start + sv.size();

    int tokens_read = 0;
    int tokens[3];

    while (end != limit && tokens_read < 3) {
        if (*end == '/') {
            std::string_view token(start, end-start);
            toInt(token, tokens[tokens_read++]);
            start = end+1;
        }
        end++;
    }

    if (tokens_read < 3 && start < limit) {
        std::string_view token(start, limit-start);
        toInt(token, tokens[tokens_read++]);
    }

    return Vector3<int>(tokens);
}