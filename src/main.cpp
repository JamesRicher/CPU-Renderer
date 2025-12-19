#include <iostream>
#include <cmath>
#include <vector>

#include "mesh_parser/mesh_parser.h"
#include "app_config.h"
#include "scene_object.h"

int main() {
    // setup the config data
    AppConfig config;
    config.asset_root = std::filesystem::current_path() / "assets";
    MeshParser mesh_parser(config);

    std::vector<SceneObject> scene_objects;
    Mesh cube = mesh_parser.loadFromJson("cube_triangulated.json");
    SceneObject scene_cub = SceneObject(&cube);

    // outline of approach
    // clear the buffers
    // update each scene object's transform
    // loop through scene objects and render each one
        // get each ones MVP matrix
        // transform each vertex to a ClipVertex obect and store in a vector
        // keep the triangles vector const throuhgout
        // rasterise and interpolate
}
