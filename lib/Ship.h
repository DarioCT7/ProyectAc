#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>

class Ship {
public:
    Ship();
    void move(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
    void upgradeShip(int level); // Método para cambiar la nave
    sf::Vector2f getOrigin() const { return sprite.getOrigin(); } // Añadido
    sf::Vector2f getScale() const { return sprite.getScale(); }   // Añadido
private:
    sf::Sprite sprite;
    static sf::Texture texture; // Textura estática compartida
    static sf::Texture upgradeTexture; // Textura para nivel 3+
    static bool textureLoaded;
    static bool upgradeTextureLoaded;
    float speed;
};

#endif