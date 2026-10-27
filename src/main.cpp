#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <optional>
#include <cmath>

// =========================================================================
// Принудительное использование дискретной видеокарты (NVIDIA / AMD)
// Это прямой аналог макроса SFML_DEFINE_DISCRETE_GPU_PREFERENCE, 
// но работает без ошибок компиляции.
// =========================================================================
extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
// =========================================================================

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

// ---------- Главная программа ----------

int main() {
    std::cout << "1. Program started" << std::endl;

    const unsigned W = 800, H = 600;

    // Настройки контекста OpenGL (запрашиваем совместимый 2.1)
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antiAliasingLevel = 0;   // В SFML 3 регистр буквы 'A' изменился
    settings.majorVersion = 2;
    settings.minorVersion = 1;
    settings.attributeFlags = sf::ContextSettings::Default;

    std::cout << "2. Creating window..." << std::endl;

    // Создаем окно (в SFML 3 добавлен параметр sf::State::Windowed)
    sf::RenderWindow window(
        sf::VideoMode({ W, H }),
        "Wireframe Cube",
        sf::Style::Default,
        sf::State::Windowed,          // <-- Обязательно для SFML 3
        settings
    );

    std::cout << "3. Window created successfully!" << std::endl;
    std::cout << "OpenGL version: " << window.getSettings().majorVersion
        << "." << window.getSettings().minorVersion << std::endl;

    window.setFramerateLimit(60);

    // Вершины куба от -1 до +1 (8 штук)
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

    std::cout << "4. Entering main loop..." << std::endl;

    while (window.isOpen()) {
        // Обработка событий
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Обновление (независимое от FPS)
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
        window.draw(lines);
        window.display();
    }

    std::cout << "5. Program finished normally." << std::endl;
    return 0;
}