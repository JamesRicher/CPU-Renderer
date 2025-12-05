cmake_minimum_required(VERSION 3.23)
project(CPURenderer)

add_executable(CPURenderer)
target_compile_features(CPURenderer PRIVATE cxx_std_17)
target_sources(CPURenderer
    PRIVATE
        src/main.cpp
)

add_subdirectory(external/SFML SYSTEM)
target_link_libraries(CPURenderer SFML::Graphics)