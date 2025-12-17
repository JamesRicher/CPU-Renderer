#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "mesh_parser/mesh.h"
#include "matrix4.h"

class SceneObject {
    Mesh* mesh;
    Matrix4<float> object_to_world;
};

#endif