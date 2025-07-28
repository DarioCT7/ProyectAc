#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>

class Asteroid {
public:
    Asteroid(float initialSpeed = 200.f);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isOffScreen() const;
private:
    sf::Sprite sprite;
    static sf::Texture texture;
    static bool textureLoaded;
    float speed;
    float rotationSpeed; // Velocidad de rotación
    float scale;        // Escala para variar tamaño
};

#endif