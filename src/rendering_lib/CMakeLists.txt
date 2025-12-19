add_library(RenderingLib)

target_sources(RenderingLib
    PUBLIC
        scene_object.h
    PRIVATE
        scene_object.cpp
)

target_include_directories(RenderingLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(RenderingLib
    PUBLIC
        MathsLib
    PRIVATE
        MeshParser
        SFML::Graphics
        SFML::Window
        SFML::System
)