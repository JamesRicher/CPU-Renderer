add_executable(ConvertMesh)

target_sources(ConvertMesh
    PRIVATE
        convert_mesh.cpp
)

target_link_libraries(ConvertMesh
    PRIVATE
        MeshParser
)