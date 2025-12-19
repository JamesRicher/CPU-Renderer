#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <string>
#include "mesh_parser/mesh.h"
#include "matrix4.h"

class SceneObject {
private:
    std::string name;
    Mesh* mesh;
    Matrix4<float> object_to_world;

public:
    SceneObject(Mesh* mesh, 
        Matrix4<float> mat = Matrix4<float>::identity(), 
        std::string name = "scene_object") :
        mesh(mesh),
        object_to_world(mat),
        name(name) {}
};

#endif