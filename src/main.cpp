#include <iostream>
#include <cmath>

#include "mesh_parser/mesh_parser.h"
#include "app_config.h"

int main() {
    // setup the config data
    AppConfig config;
    config.asset_root = std::filesystem::current_path() / "assets";

    MeshParser mesh_parser(config);
    Mesh mesh = mesh_parser.loadFromObj("cube_triangulated.obj");
    mesh_parser.saveAsJson(mesh, "cube_triangulated.json");
    mesh = mesh_parser.loadFromJson("cube_triangulated.json");

    // outline of approach
    // clear the buffers
    // update each scene object's transform
    // loop through scene objects and render each one
        // get each ones MVP matrix
        // transform each vertex to a ClipVertex obect and store in a vector
        // keep the triangles vector const throuhgout
        // rasterise and interpolate
}
