#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(sf::Vector2f position);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isOffScreen() const;
private:
    sf::Sprite sprite;
    static sf::Texture texture; // Textura estática compartida
    static bool textureLoaded;  // Para verificar si la textura se cargó
    float speed;
    sf::Color lineColor;       // Color para la línea de fallback
};

#endif