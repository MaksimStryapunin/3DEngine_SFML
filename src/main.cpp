#include <SFML/Window.hpp>
#include <iostream>
#include <optional>
#include <cmath>

#ifdef SFML_SYSTEM_WINDOWS
SFML_DEFINE_DISCRETE_GPU_PREFERENCE
#endif

int main() {
    std::cout << "1. Program started" << std::endl;
    const unsigned W = 800, H = 600;
    std::cout << "2. Creating window..." << std::endl;

    // Используем sf::Window (без контекста рендеринга OpenGL)
    sf::Window window(sf::VideoMode({ W, H }), "Test Window");

    std::cout << "3. Window created successfully!" << std::endl;

    // Цикл, чтобы окно не закрывалось сразу
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                std::cout << "Close event received." << std::endl;
                window.close();
            }
        }
    }
    std::cout << "5. Program finished." << std::endl;
    return 0;
}