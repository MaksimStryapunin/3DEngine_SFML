#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Input Test");
    window.setFramerateLimit(60); // ограничим до 60 FPS, чтобы не жечь CPU

    while (window.isOpen()) {
        // ========== 1. ОБРАБОТКА СОБЫТИЙ ==========
        while (const std::optional event = window.pollEvent()) {
            // Закрытие окна крестиком
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Нажатие клавиши (разовое событие)
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
                if (keyPressed->code == sf::Keyboard::Key::Space) {
                    std::cout << "Space pressed!\n";
                }
            }

            // Движение мыши
            if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
                std::cout << "Mouse: " << mouseMoved->position.x
                    << ", " << mouseMoved->position.y << "\n";
            }
        }

        // ========== 2. ОБНОВЛЕНИЕ (по состоянию) ==========
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            // В реальном движке здесь мы бы двигали камеру:
            // camera.moveForward(deltaTime);
            std::cout << "moving forward\n";
        }

        // ========== 3. РЕНДЕР ==========
        window.clear(sf::Color::Black);
        // тут пока ничего не рисуем
        window.display();
    }
    return 0;
}