cmake_minimum_required(VERSION 3.23)
project(CPURenderer)

add_executable(CPURenderer)
target_compile_features(CPURenderer PRIVATE cxx_std_20)
target_sources(CPURenderer
    PRIVATE
        src/main.cpp
)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(external/SFML SYSTEM)
add_subdirectory(external/nlohmann_json SYSTEM)
add_subdirectory(src/mesh_parser)

target_link_libraries(CPURenderer
    PRIVATE
        SFML::Graphics
        MeshParser
        nlohmann_json::nlohmann_json 
)

target_link_libraries(MeshParser
    PRIVATE
        nlohmann_json::nlohmann_json
)

target_include_directories(CPURenderer
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)