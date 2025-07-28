#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"
#include <SFML/Audio.hpp>

class Game {
public:
    Game();
    void run();
private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void spawnAsteroid();
    void showLevelScreen();
    void showMenu();
    void showGameOver();

    enum GameState { Menu, Playing, LevelScreen, GameOver };
    GameState gameState;

    sf::RenderWindow window;
    Ship ship;
    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;
    sf::Clock spawnClock;
    int score;
    int lives;
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;
    sf::SoundBuffer collisionBuffer;
    sf::Sound collisionSound;
    sf::Text gameOverText;
    bool gameOver;
    int level;
    sf::Text levelText;
    sf::Text menuText;
    sf::Text playOption;
    sf::Text exitOption;
    sf::Text levelScreenText;
    sf::Text gameOverRetry;
    sf::Text gameOverExit;
    int menuSelection;
    int gameOverSelection;
    sf::Clock levelScreenClock;
    bool shipUpgraded; // Para rastrear si la nave cambió
};

#endif