cmake_minimum_required(VERSION 3.23)
project(CPURenderer)

add_executable(CPURenderer src/main.cpp)
target_compile_features(CPURenderer PRIVATE cxx_std_20)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(external/SFML SYSTEM)
add_subdirectory(external/nlohmann_json SYSTEM)
add_subdirectory(src/mesh_parser)
add_subdirectory(src/maths_lib)

option(BUILD_CONVERT_MESH "Build an exe that turns a given obj into json form (optional)" ON)
if(BUILD_CONVERT_MESH) 
    add_subdirectory(src/tools/convert_mesh)
endif()

target_link_libraries(CPURenderer
    PRIVATE
        SFML::Graphics
        MeshParser
        nlohmann_json::nlohmann_json
        MathsLib
)

target_include_directories(CPURenderer
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)