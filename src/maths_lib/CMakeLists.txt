add_library(MathsLib INTERFACE)

target_sources(MathsLib
    PUBLIC
        FILE_SET myHeaders
        TYPE HEADERS
        FILES
            vector3.h
            vector2.h
            vector4.h
            matrix4.h
)

target_compile_features(MathsLib INTERFACE cxx_std_20)

target_include_directories(MathsLib INTERFACE 
        ${PROJECT_SOURCE_DIR}/src
)