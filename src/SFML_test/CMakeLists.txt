add_executable(SFMLTest)

target_sources(SFMLTest
    PRIVATE
        sfml_test.cpp
)

target_link_libraries(SFMLTest
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)