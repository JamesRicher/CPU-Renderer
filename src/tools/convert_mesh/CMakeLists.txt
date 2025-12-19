add_executable(ConvertMesh)

target_sources(ConvertMesh
    PRIVATE
        convert_mesh.cpp
)

target_link_libraries(ConvertMesh
    PRIVATE
        MeshParser
)

target_include_directories(MeshParser
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/src
)
