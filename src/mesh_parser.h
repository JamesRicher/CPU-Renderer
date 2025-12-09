#ifndef MESH_PARSER_H
#define MESH_PARSER_H

class Mesh;

namespace MeshParser {
    Mesh loadFromObj(const char* obj_path);
    bool saveAsJson(const Mesh& mesh, const char* json_path);
    bool saveAsBinary(const Mesh& mesh, const char* binary_path);
}

#endif
