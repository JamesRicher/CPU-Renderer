#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string_view>
#include <cctype>
#include <charconv>
#include <unordered_map>
#include <cassert>

#include "mesh_parser.h"
#include "app_config.h"
#include "vector3.h"
#include "mesh.h"
#include "vertex_key.h"
#include "vertex_key_hash.h"

//----- INTERNAL -----
namespace {
// extracts the three indices from a sv such as 4/11/23 and packs them in a vector3
static Vector3<int> extractTokens(std::string_view sv) {
    const char* start = sv.data();
    const char* end = start;
    const char* limit = start + sv.size();

    int tokens_read = 0;
    int tokens[3] = {0,0,0};

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

    if (tokens[0] == 0 || tokens[1] == 0 || tokens[2] == 0) {
        std::cerr << "ERROR: wrong number of tokens for a vertex" << std::endl;
        throw std::runtime_error("wromg number of tokens for a vertex");
    }

    return Vector3<int>(tokens);
}

static std::vector<std::string_view> split(const char* cstr) {
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

static bool toFloat(std::string_view sv, float& out) {
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

static bool toInt(std::string_view sv, int& out) {
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

static Vector3<float> lineToVector3(std::vector<std::string_view> tokens) {
    float coords[3];
    for (int i=0; i < 3; i++)
        toFloat(tokens[i+1], coords[i]);

    return Vector3<float>(coords);
}

struct ObjData {
    std::vector<Vector3<float>> positions;
    std::vector<Vector3<float>> normals;
    std::vector<Vector2<float>> texcoords;
};

static bool openObjFile(std::ifstream& obj_stream, std::filesystem::path obj_path) {
    obj_stream.open(obj_path);
    if (!obj_stream.good()) {
        std::cerr << "ERROR: problem reading the obj file supplied" << std::endl;
        return false;
    }

    return true;
}

static ObjData parseObjAttributes(std::ifstream& obj_stream) {
    ObjData obj_data;

    std::string line;
    // read in the vertex data into the three arrays
    while (std::getline(obj_stream, line)) {
        if (line[0] == '\0')
            continue;

        auto tokenised_line = split(line.c_str());
        if (tokenised_line[0] == "v")
            obj_data.positions.push_back(lineToVector3(tokenised_line));
        else if (tokenised_line[0] == "vn") {
            obj_data.normals.push_back(lineToVector3(tokenised_line));
        }
        else if (tokenised_line[0] == "vt") {
            float coords[2];
            for (int i=0; i<2; i++) {
                toFloat(tokenised_line[i+1], coords[i]);
            }

            obj_data.texcoords.emplace_back(coords);
        }
    }

    return obj_data;
}

static void parseObjFaces(
    std::ifstream& obj_stream, 
    const ObjData& obj_data,
    std::vector<Vertex>& vertex_buffer,
    std::vector<uint32_t>& triangle_buffer
) {
    // consruct the vertex hashmap
    std::unordered_map<VertexKey, uint32_t, VertexKeyHash> vertex_map;

    vertex_map.reserve(obj_data.positions.size() * 3);
    vertex_buffer.reserve(obj_data.positions.size());
    triangle_buffer.reserve(obj_data.positions.size());

    std::string line;
    while (std::getline(obj_stream, line)){
        if (line[0] == '\0')
            continue;

        auto tokenised_line = split(line.c_str());
        assert(tokenised_line.size() == 4);
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
                    v.position = obj_data.positions[vertex_key.pos_i];
                    v.normal = obj_data.normals[vertex_key.norm_i];
                    v.uv = obj_data.texcoords[vertex_key.tex_i];

                    vertex_buffer.push_back(v);
                }

                triangle_buffer.push_back(it->second);
            }
        }
    }
}
} // end of anonymous namespace

//----- MEMBERS -----
MeshParser::MeshParser(AppConfig config) : asset_root(config.asset_root) {}

Mesh MeshParser::loadFromObj(const char* obj_rel_path) {
    // open the obj file
    std::ifstream obj_stream;
    if (!openObjFile(obj_stream, asset_root / obj_rel_path))
        throw std::runtime_error("ERROR loading obj");

    // read in the raw geometry data 
    ObjData obj_data = parseObjAttributes(obj_stream);
    
    // reset the filestream
    obj_stream.clear();
    obj_stream.seekg(0);

    // create a map to store the vertices in
    std::vector<Vertex> vertex_buffer;
    std::vector<uint32_t> triangle_buffer;
    parseObjFaces(obj_stream, obj_data, vertex_buffer, triangle_buffer);

    obj_stream.close();

    // DEBUG
    int loop_count = 1;
    for (int x: triangle_buffer) {
        std::cout << x << ", ";
        if (loop_count==0) std::cout << std::endl;
        loop_count = (loop_count +1)% 3;
    }

    return Mesh(vertex_buffer, triangle_buffer);
}

bool MeshParser::saveAsJson(const Mesh& mesh, const char* json_path) {
    return false;
}

bool MeshParser::saveAsBinary(const Mesh& mesh, const char* binary_path) {
    return false;
}