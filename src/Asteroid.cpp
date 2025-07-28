#include "../lib/Asteroid.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

sf::Texture Asteroid::texture;
bool Asteroid::textureLoaded = false;

Asteroid::Asteroid(float initialSpeed) {
    if (!textureLoaded) {
        if (!texture.loadFromFile("assets/asteroid.png")) {
            std::cout << "Error: No se pudo cargar imagen. Usando figuras." << std::endl;
            textureLoaded = false;
        } else {
            textureLoaded = true;
        }
    }

    if (textureLoaded) {
        sprite.setTexture(texture);
        scale = (std::rand() % 2 + 1) * 0.4f; // Escala 0.05 o 0.1 (pequeño o mediano)
        sprite.setScale(scale, scale);
    } else {
        sf::CircleShape shape(static_cast<float>(std::rand() % 30 + 10)); // Tamaño 10-40
        shape.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
        sf::RenderTexture renderTexture;
        renderTexture.create(shape.getRadius() * 2, shape.getRadius() * 2);
        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(shape);
        renderTexture.display();
        texture = renderTexture.getTexture();
        sprite.setTexture(texture);
        scale = (std::rand() % 2 + 1) * 0.4f; // Escala variable
        sprite.setScale(scale, scale);
    }
    sprite.setPosition(static_cast<float>(std::rand() % 760), -20.f);
    speed = initialSpeed;
    rotationSpeed = (std::rand() % 2 == 0) ? 50.f : 0.f; // 50% chance de girar
}

void Asteroid::update(float deltaTime) {
    sprite.move(0.f, speed * deltaTime);
    if (rotationSpeed > 0) {
        sprite.rotate(rotationSpeed * deltaTime);
    }
}

void Asteroid::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Asteroid::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Asteroid::isOffScreen() const {
    return sprite.getPosition().y > 600;
}