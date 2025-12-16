cmake_minimum_required(VERSION 3.23)
project(CPURenderer)

add_executable(CPURenderer)
target_compile_features(CPURenderer PRIVATE cxx_std_17)
target_sources(CPURenderer
    PRIVATE
        src/main.cpp
)

add_subdirectory(external/SFML SYSTEM)
add_subdirectory(src/mesh_parser)

target_link_libraries(CPURenderer
    PRIVATE
        SFML::Graphics
        MeshParser
)

target_include_directories(CPURenderer
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)