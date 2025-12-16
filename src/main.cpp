#include <iostream>
#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "mesh_parser/mesh_parser.h"
#include "app_config.h"

int main() {
    // setup the config data
    AppConfig config;
    config.asset_root = std::filesystem::current_path() / "assets";

    MeshParser mesh_parser(config);
    mesh_parser.loadFromObj("cube_triangulated.obj");

    int width = 150;
    int height = 150;
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(width,height), 8),
        "Demo Window"
    );

    sf::Clock frame_clock;
    sf::Clock global_clock;

    const float targetFPS = 30.0f;
    const sf::Time frame_time = sf::seconds(1.0f/targetFPS);

    unsigned char* pixels = new unsigned char[width*height*4];
    for (int i=0; i < width*height*4; i++) {
        pixels[i] = 255;
    }

    sf::Texture fb_texture(sf::Vector2u(width, height));
    sf::Sprite fb_sprite(fb_texture);

    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        float time = global_clock.getElapsedTime().asSeconds();
        float brightness = (1.0f + std::sin(time)) * 127.0;
        for (int i=0; i < width*height*4; i++) {
            pixels[i] = brightness;
        }

        fb_texture.update(pixels);
        window.draw(fb_sprite);

        window.display();

        sf::Time elapsed = frame_clock.getElapsedTime();
        if (elapsed < frame_time) {
            sf::sleep(frame_time - elapsed);
        }
        frame_clock.restart();
    }

    delete[] pixels;

    return 0;
}
