#include <iostream>
#include <cstring>
#include <string>
#include "mesh_parser.h"
#include "app_config.h"

// -o obj_filename -j json_filename
int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "Incorrect usage" << std::endl;
        exit(1);
    }

    bool seen_o=false, seen_j=false;
    std::string json_filename;
    std::string obj_filename;

    for (int i=1; i < argc; i+=2) {
        const char* flag = argv[i];
        const char* value = argv[i+1];

        if (!strcmp(flag, "-o")) {
            if (seen_o) exit(1);
            seen_o = true;
            obj_filename = value;
        }
        else if (!strcmp(flag, "-j")) {
            if (seen_j) exit(1);
            seen_j = true;
            json_filename = value;
        }
    }

    AppConfig config;
    config.asset_root = std::filesystem::current_path() / "assets";
    MeshParser mesh_parser(config);

    Mesh mesh = mesh_parser.loadFromObj(obj_filename.c_str());
    mesh_parser.saveAsJson(mesh, json_filename.c_str());

    return 0;
}