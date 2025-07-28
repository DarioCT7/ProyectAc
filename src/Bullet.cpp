#include "../lib/Bullet.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

sf::Texture Bullet::texture;
bool Bullet::textureLoaded = false;

Bullet::Bullet(sf::Vector2f position) {
    if (!textureLoaded) {
        if (!texture.loadFromFile("assets/bullet.png")) {
            std::cout << "Error: No se pudo cargar la imagen. Usando linea." << std::endl;
            textureLoaded = false;
        } else {
            textureLoaded = true;
        }
    }

    if (textureLoaded) {
        sprite.setTexture(texture);
        sprite.setScale(0.15f, 0.15f); // Tamaño ajustable
    } else {
        lineColor = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256); // Color aleatorio
    }
    sprite.setPosition(position);
    speed = 400.f;
}

void Bullet::update(float deltaTime) {
    sprite.move(0.f, -speed * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) {
    if (textureLoaded) {
        window.draw(sprite);
    } else {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(sprite.getPosition().x + 2.5f, sprite.getPosition().y), lineColor),
            sf::Vertex(sf::Vector2f(sprite.getPosition().x + 2.5f, sprite.getPosition().y - 15.f), lineColor) // Línea más larga
        };
        window.draw(line, 2, sf::Lines);
    }
}

sf::FloatRect Bullet::getBounds() const {
    if (textureLoaded) {
        return sprite.getGlobalBounds();
    } else {
        return sf::FloatRect(sprite.getPosition().x, sprite.getPosition().y, 5.f, 15.f); // Tamaño ajustable
    }
}

bool Bullet::isOffScreen() const {
    return sprite.getPosition().y < 0;
}