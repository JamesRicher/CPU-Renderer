add_library(MeshParser)

target_sources(MeshParser
    PRIVATE
        mesh_parser.cpp
        mesh.cpp
    
    PUBLIC
        FILE_SET myHeaders
        TYPE HEADERS
        FILES
            mesh_parser.h
            vertex.h
            mesh.h
)

target_compile_features(MeshParser PRIVATE cxx_std_17)

target_include_directories(MeshParser
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)