#include "../lib/Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Meteoritos"), ship() {
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    score = 0;
    lives = 3;
    gameOver = false;
    level = 1;
    gameState = Menu;
    menuSelection = 0;
    gameOverSelection = 0;
    shipUpgraded = false;

    // Cargar fuente para el texto
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cout << "Error: No se pudo cargar la fuente." << std::endl;
    }

    // Textos de interfaz
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10.f, 40.f);
    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(10.f, 70.f);

    // Cargar sonidos
    if (!shootBuffer.loadFromFile("assets/shoot.wav")) {
        std::cout << "Error: No se pudo cargar el sonido de disparo." << std::endl;
    } else {
        std::cout << "Sonido cargado correctamente." << std::endl;
    }
    shootSound.setBuffer(shootBuffer);
    if (!collisionBuffer.loadFromFile("assets/collision.wav")) {
        std::cout << "Error: No se pudo cargar el sonido de colision." << std::endl;
    } else {
        std::cout << "Sonido cargado correctamente." << std::endl;
    }
    collisionSound.setBuffer(collisionBuffer);

    // Textos de menú
    menuText.setFont(font);
    menuText.setCharacterSize(48);
    menuText.setFillColor(sf::Color::White);
    menuText.setString("Space Invaders");
    menuText.setPosition(250.f, 100.f);
    playOption.setFont(font);
    playOption.setCharacterSize(36);
    playOption.setFillColor(sf::Color::White);
    playOption.setString("Jugar");
    playOption.setPosition(340.f, 200.f);
    exitOption.setFont(font);
    exitOption.setCharacterSize(36);
    exitOption.setFillColor(sf::Color::White);
    exitOption.setString("Salir");
    exitOption.setPosition(340.f, 250.f);

    // Texto de pantalla de nivel
    levelScreenText.setFont(font);
    levelScreenText.setCharacterSize(48);
    levelScreenText.setFillColor(sf::Color::Yellow);
    levelScreenText.setPosition(300.f, 250.f);

    // Textos de Game Over
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Perdiste mejor suerte la proxima");
    gameOverText.setPosition(300.f, 200.f);
    gameOverRetry.setFont(font);
    gameOverRetry.setCharacterSize(36);
    gameOverRetry.setFillColor(sf::Color::White);
    gameOverRetry.setString("Volver a intentar");
    gameOverRetry.setPosition(280.f, 300.f);
    gameOverExit.setFont(font);
    gameOverExit.setCharacterSize(36);
    gameOverExit.setFillColor(sf::Color::White);
    gameOverExit.setString("Salir");
    gameOverExit.setPosition(320.f, 350.f);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        if (gameState == Playing) update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        if (gameState == Menu) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menuSelection = 0;
                } else if (event.key.code == sf::Keyboard::Down) {
                    menuSelection = 1;
                } else if (event.key.code == sf::Keyboard::Return) {
                    if (menuSelection == 0) {
                        gameState = Playing;
                        score = 0;
                        lives = 3;
                        level = 1;
                        asteroids.clear();
                        bullets.clear();
                        ship = Ship();
                        shipUpgraded = false;
                    } else if (menuSelection == 1) {
                        window.close();
                    }
                }
            }
        } else if (gameState == Playing) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !gameOver) {
                sf::Vector2f bulletPos = ship.getPosition();
                sf::Vector2f origin = ship.getOrigin();
                sf::Vector2f scale = ship.getScale();
                bulletPos.x -= origin.x * scale.x;
                bulletPos.y -= origin.y * scale.y;
                bullets.emplace_back(bulletPos);
                shootSound.play();
            }
        } else if (gameState == GameOver) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    gameOverSelection = 0;
                    std::cout << "Selecionar Volver a intentar (0)" << std::endl;
                } else if (event.key.code == sf::Keyboard::Down) {
                    gameOverSelection = 1;
                    std::cout << "Selecionar Salir (1)" << std::endl;
                } else if (event.key.code == sf::Keyboard::Return) {
                    std::cout << "Enter presionado, seleccion actual: " << gameOverSelection << std::endl;
                    if (gameOverSelection == 0) {
                        gameState = Playing;
                        score = 0;
                        lives = 3;
                        level = 1;
                        asteroids.clear();
                        bullets.clear();
                        ship = Ship();
                        shipUpgraded = false;
                        std::cout << "Juego reiniciado" << std::endl;
                    } else if (gameOverSelection == 1) {
                        window.close();
                        std::cout << "Juego cerrado" << std::endl;
                    }
                }
            }
        } else if (gameState == LevelScreen) {
            if (event.type == sf::Event::KeyPressed) {
                gameState = Playing; // Salir de la pantalla al presionar cualquier tecla
            }
        }
    }
}

void Game::update(float deltaTime) {
    if (gameOver) {
        gameState = GameOver;
        return;
    }

    if (gameState == LevelScreen) {
        if (levelScreenClock.getElapsedTime().asSeconds() >= 2.0f) {
            gameState = Playing;
            levelScreenClock.restart();
        }
        return;
    }

    ship.move(deltaTime);

    // Actualizar balas
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->update(deltaTime);
        if (it->isOffScreen())
            it = bullets.erase(it);
        else
            ++it;
    }

    // Generar asteroides
    if (spawnClock.getElapsedTime().asSeconds() > 1.f / level) {
        spawnAsteroid();
        spawnClock.restart();
    }

    // Actualizar asteroides
    for (auto it = asteroids.begin(); it != asteroids.end();) {
        it->update(deltaTime);
        if (it->isOffScreen())
            it = asteroids.erase(it);
        else
            ++it;
    }

    // Detectar colisiones
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool bulletRemoved = false;
        for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end() && !bulletRemoved;) {
            if (bulletIt->getBounds().intersects(asteroidIt->getBounds())) {
                score += 10;
                collisionSound.play();
                bulletIt = bullets.erase(bulletIt);
                asteroidIt = asteroids.erase(asteroidIt);
                bulletRemoved = true;
            } else {
                ++asteroidIt;
            }
        }
        if (!bulletRemoved)
            ++bulletIt;
    }

    // Colisión con la nave
    for (auto it = asteroids.begin(); it != asteroids.end();) {
        if (it->getBounds().intersects(ship.getBounds())) {
            lives--;
            collisionSound.play();
            it = asteroids.erase(it);
            sf::Vector2f impactPos = ship.getPosition();
            ship.setPosition(impactPos);
            if (lives <= 0) {
                gameOver = true;
            }
        } else {
            ++it;
        }
    }

    // Actualizar nivel
    if (score >= level * 200) {
        level++;
        gameState = LevelScreen;
        levelScreenClock.restart();
        if (level >= 4 && !shipUpgraded) {
            ship.upgradeShip(level);
            shipUpgraded = true;
        }
    }

    // Actualizar texto
    scoreText.setString("Puntuacion: " + std::to_string(score));
    livesText.setString("Vida: " + std::to_string(lives));
    levelText.setString("Nivel: " + std::to_string(level));
}

void Game::render() {
    window.clear(sf::Color::Black);
    if (gameState == Playing) {
        ship.draw(window);
        for (auto& bullet : bullets) bullet.draw(window);
        for (auto& asteroid : asteroids) asteroid.draw(window);
        if (font.getInfo().family != "") {
            window.draw(scoreText);
            window.draw(livesText);
            window.draw(levelText);
        }
    } else if (gameState == Menu) {
        if (font.getInfo().family != "") {
            window.draw(menuText);
            window.draw(playOption);
            window.draw(exitOption);
            if (menuSelection == 0) {
                playOption.setFillColor(sf::Color::Yellow);
            } else {
                playOption.setFillColor(sf::Color::White);
            }
            if (menuSelection == 1) {
                exitOption.setFillColor(sf::Color::Yellow);
            } else {
                exitOption.setFillColor(sf::Color::White);
            }
        }
    } else if (gameState == LevelScreen) {
        if (font.getInfo().family != "") {
            levelScreenText.setString("Nivel " + std::to_string(level));
            window.draw(levelScreenText);
        }
    } else if (gameState == GameOver) {
        if (font.getInfo().family != "") {
            window.draw(gameOverText);
            window.draw(gameOverRetry);
            window.draw(gameOverExit);
            if (gameOverSelection == 0) {
                gameOverRetry.setFillColor(sf::Color::Yellow);
            } else {
                gameOverRetry.setFillColor(sf::Color::White);
            }
            if (gameOverSelection == 1) {
                gameOverExit.setFillColor(sf::Color::Yellow);
            } else {
                gameOverExit.setFillColor(sf::Color::White);
            }
        }
    }
    window.display();
}

void Game::spawnAsteroid() {
    float baseSpeed = 200.f + (level - 1) * 50.f;
    asteroids.emplace_back(baseSpeed);
}

void Game::showLevelScreen() {
    // Ya manejado en update() y render()
}

void Game::showMenu() {
    // Ya manejado en render()
}

void Game::showGameOver() {
    // Ya manejado en render()
}