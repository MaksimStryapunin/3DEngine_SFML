#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

int main() {
    std::cout << "1. Program started" << std::endl;

    const unsigned W = 800, H = 600;

    std::cout << "2. Creating window..." << std::endl;
    sf::RenderWindow window(sf::VideoMode({ W, H }), "Wireframe Cube");
    std::cout << "3. Window created successfully!" << std::endl;

    window.setFramerateLimit(60);

    sf::Clock clock;
    float angle = 0.0f;

    std::cout << "4. Entering main loop..." << std::endl;
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                std::cout << "Close event received." << std::endl;
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();
        angle += dt * 1.0f;

        window.clear(sf::Color::Black);
        window.display();
    }

    std::cout << "5. Program finished normally." << std::endl;
    return 0;
}