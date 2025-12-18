add_library(MeshParser)

target_sources(MeshParser
    PRIVATE
        mesh_parser.cpp
        vertex_key.h
        vertex_key_hash.h
    
    PUBLIC
        FILE_SET HEADERS
        TYPE HEADERS
        FILES
            mesh_parser.h
            vertex.h
            mesh.h
)

target_compile_features(MeshParser PUBLIC cxx_std_17)

target_link_libraries(MeshParser
    PRIVATE
        nlohmann_json::nlohmann_json
    PUBLIC
        MathsLib
)

target_include_directories(MeshParser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})