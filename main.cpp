#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GUI.h"



int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800),
                            "SFML window", sf::Style::Close);
    sf::Font font;
    font.loadFromFile("../fonts/Arial.ttf");


    Game game;
    game.startGame();
    GUI gui(window, game, font);

    window.setFramerateLimit(60);

    sf::Clock clock;

    // Control the speed by adjusting this value
    float updateTime = 0.1f;
    float elapsed = 0.0f;
    Direction actualDirection = game.snakeDirection;
    // Start the game loop
    while (window.isOpen()) {



        // Process events
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (game.gameState == PAUSED || game.gameState == NONE) {
                game.resumeGame();
            } else if (game.gameState == PLAYING) {
                game.pauseGame();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            game.restartGame();
        }
        Direction currDirection = game.snakeDirection;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) && currDirection != RIGHT) {
            actualDirection = LEFT;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)  && currDirection != LEFT) {
            actualDirection = RIGHT;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)|| sf::Keyboard::isKeyPressed(sf::Keyboard::W) && currDirection != DOWN) {
            actualDirection = UP;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) && currDirection != UP) {
            actualDirection = DOWN;
        }
        elapsed += clock.restart().asSeconds();

        if (elapsed < updateTime) {
            continue;
        }
        if (game.gameState == PLAYING) {
            game.updateState(actualDirection);
        }

        // Clear screen
        window.clear();
        gui.draw();

        // Update the window
        window.display();
        elapsed = 0.0f;
    }

    return EXIT_SUCCESS;
}