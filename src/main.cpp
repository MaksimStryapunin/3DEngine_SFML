#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


// ---------- Базовые типы ----------

struct Vec3 { float x, y, z; };

Vec3 rotateY(Vec3 v, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return {
         v.x * c - v.z * s,   // x'
         v.y,                 // y'  (не меняется)
         v.x * s + v.z * c    // z'
    };
}

sf::Vector2f project(Vec3 v, float screenW, float screenH) {
    const float focal = 500.0f;   // "фокус" в пикселях — просто масштаб
    const float z_offset = 5.0f;     // сдвигаем сцену вперёд от камеры

    float z = v.z + z_offset;
    if (z < 0.1f) z = 0.1f;          // защита: z не должен быть 0/отрицательным

    float sx = v.x / z * focal + screenW * 0.5f;
    float sy = -v.y / z * focal + screenH * 0.5f; // -y: экранный Y растёт вниз

    return { sx, sy };
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Input Test");
    window.setFramerateLimit(60); 
    Vec3 vertices[8] = {
       {-1, -1, -1}, { 1, -1, -1}, { 1,  1, -1}, {-1,  1, -1}, // задняя грань (z=-1)
       {-1, -1,  1}, { 1, -1,  1}, { 1,  1,  1}, {-1,  1,  1}  // передняя (z=+1)
    };

    // 12 рёбер: пары индексов вершин
    int edges[12][2] = {
        {0,1},{1,2},{2,3},{3,0}, // задняя грань
        {4,5},{5,6},{6,7},{7,4}, // передняя
        {0,4},{1,5},{2,6},{3,7}  // соединительные
    };

    sf::Clock clock;
    float angle = 0.0f;

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
        float dt = clock.restart().asSeconds();
        angle += dt * 1.0f;  // 1 радиан/сек

        // Рендер: 12 линий × 2 вершины = 24 вершины
        sf::VertexArray lines(sf::PrimitiveType::Lines, 24);

        for (int i = 0; i < 12; ++i) {
            Vec3 a = rotateY(vertices[edges[i][0]], angle);
            Vec3 b = rotateY(vertices[edges[i][1]], angle);

            sf::Vector2f pa = project(a, W, H);
            sf::Vector2f pb = project(b, W, H);

            lines[2 * i].position = pa;
            lines[2 * i].color = sf::Color::White;
            lines[2 * i + 1].position = pb;
            lines[2 * i + 1].color = sf::Color::White;
        }

        window.clear(sf::Color::Black);
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