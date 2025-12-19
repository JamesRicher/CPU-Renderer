add_library(MathsLib INTERFACE)

target_sources(MathsLib
    INTERFACE
        FILE_SET HEADERS
        TYPE HEADERS
        FILES
            vector3.h
            vector2.h
            vector4.h
            matrix4.h
)

target_link_libraries(MathsLib
    INTERFACE
        nlohmann_json::nlohmann_json
)

target_compile_features(MathsLib INTERFACE cxx_std_17)
target_include_directories(MathsLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})