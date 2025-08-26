#include <SFML/Graphics.hpp>
#include <optional>
#include <numbers>
#include <cmath>
#include <vector>

struct Vec3 {
    float x, y, z;
};

constexpr float PI_F = 3.14;

// Rotate around Y-axis
Vec3 rotateY(const Vec3& v, float angle) {
    float rad = angle * PI_F / 180.0f;
    float cosA = cos(rad);
    float sinA = sin(rad);
    return { v.x * cosA + v.z * sinA, v.y, -v.x * sinA + v.z * cosA };
}

// Rotate around X-axis
Vec3 rotateX(const Vec3& v, float angle) {
    float rad = angle * PI_F / 180.0f;
    float cosA = cos(rad);
    float sinA = sin(rad);
    return { v.x, v.y * cosA - v.z * sinA, v.y * sinA + v.z * cosA };
}

// Simple perspective projection
sf::Vector2f project(const Vec3& v, float width, float height, float fov = 200.0f) {
    return { width / 2 + v.x * fov / (v.z + 5), height / 2 - v.y * fov / (v.z + 5) };
}

int main() {
#if SFML_VERSION_MAJOR >= 3
    sf::RenderWindow window(sf::VideoMode({800, 600}), "3D Rotating Cube");
#else
    sf::RenderWindow window(sf::VideoMode(800, 600), "3D Rotating Cube");
#endif

    // Cube vertices
    std::vector<Vec3> cube = {
        {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
        {-1,-1,1}, {1,-1,1}, {1,1,1}, {-1,1,1}
    };

    // Cube edges (pairs of vertex indices)
    std::vector<std::pair<int, int>> edges = {
        {0,1},{1,2},{2,3},{3,0},
        {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}
    };

    float angleX = 0.0f, angleY = 0.0f;
    
    // Rotation speed variable - easily adjustable
    float rotationSpeed = 0.05f;

    while (window.isOpen()) {
#if SFML_VERSION_MAJOR >= 3
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
#else
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
#endif

        window.clear(sf::Color::Black);

        // Rotate cube
        std::vector<sf::Vector2f> projected;
        for (auto& v : cube) {
            Vec3 rotated = rotateY(rotateX(v, angleX), angleY);
            projected.push_back(project(rotated, 800, 600));
        }

        // Draw edges
        for (auto& e : edges) {
            sf::Vertex line[2];
            line[0].position = projected[e.first];
            line[0].color = sf::Color::White;
            line[1].position = projected[e.second];
            line[1].color = sf::Color::White;
#if SFML_VERSION_MAJOR >= 3
            window.draw(line, 2, sf::PrimitiveType::Lines);
#else
            window.draw(line, 2, sf::Lines);
#endif
        }

        window.display();

        // Increment rotation
        angleX += rotationSpeed;
        angleY += rotationSpeed;
    }

    return 0;
}
