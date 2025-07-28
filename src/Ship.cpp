#include "../lib/Ship.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Texture Ship::texture; // Definición de la textura estática
sf::Texture Ship::upgradeTexture; // Textura para nivel 3+
bool Ship::textureLoaded = false; // Inicialización de la bandera
bool Ship::upgradeTextureLoaded = false; // Inicialización para la textura de upgrade

Ship::Ship() {
    if (!textureLoaded) {
        if (!texture.loadFromFile("assets/ship.png")) {
            std::cout << "Error: No se pudo cargar imagen1. Usando triangulo." << std::endl;
            textureLoaded = false;
        } else {
            textureLoaded = true;
        }
    }
    if (!upgradeTextureLoaded) {
        if (!upgradeTexture.loadFromFile("assets/ship_level2.png")) {
            std::cout << "Error: No se pudo cargar imagen2. Usando triangulo." << std::endl;
            upgradeTextureLoaded = false;
        } else {
            upgradeTextureLoaded = true;
        }
    }

    if (textureLoaded) {
        sprite.setTexture(texture);
        sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
        sprite.setScale(0.3f, 0.3f);
    } else {
        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(0.f, -20.f));
        triangle.setPoint(1, sf::Vector2f(-25.f, 20.f));
        triangle.setPoint(2, sf::Vector2f(25.f, 20.f));
        triangle.setFillColor(sf::Color::Green);
        sf::RenderTexture renderTexture;
        renderTexture.create(50, 40);
        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(triangle);
        renderTexture.display();
        texture = renderTexture.getTexture();
        sprite.setTexture(texture);
        sprite.setOrigin(25.f, 20.f);
    }
    sprite.setPosition(375.f, 550.f);
    speed = 300.f;
}

void Ship::move(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x > 0)
        sprite.move(-speed * deltaTime, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sprite.getPosition().x < 750)
        sprite.move(speed * deltaTime, 0.f);
}

void Ship::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Ship::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Ship::getPosition() const {
    return sprite.getPosition();
}

void Ship::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

void Ship::upgradeShip(int level) {
    if (level >= 4 && upgradeTextureLoaded) { // Nivel 4 (tras 3 niveles: 600 puntos)
        sprite.setTexture(upgradeTexture);
        sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
        sprite.setScale(0.3f, 0.3f);
    } else if (level >= 4 && !upgradeTextureLoaded && !textureLoaded) {
        // Cambiar color del triángulo a azul si no hay imagen
        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(0.f, -20.f));
        triangle.setPoint(1, sf::Vector2f(-25.f, 20.f));
        triangle.setPoint(2, sf::Vector2f(25.f, 20.f));
        triangle.setFillColor(sf::Color::Blue);
        sf::RenderTexture renderTexture;
        renderTexture.create(50, 40);
        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(triangle);
        renderTexture.display();
        sprite.setTexture(renderTexture.getTexture());
        sprite.setOrigin(25.f, 20.f);
    }
}