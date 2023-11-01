//
// Created by Tony Adriansen on 10/31/23.
//

#include "GUI.h"
#include "Game.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

void GUI::draw() {
    drawLines();
    drawEntities();
    game.gameState == GAME_OVER ? drawGameOver() : drawEntities();
}

void GUI::drawLines() {
    for (int i = 0; i < 22; i++) {
        sf::RectangleShape vertical_line;
        sf::RectangleShape horizontal_line;
        horizontal_line.setSize(sf::Vector2f(1.0f, static_cast<float>(WINDOW_HEIGHT - 170)));
        horizontal_line.setPosition(static_cast<float>(WINDOW_HEIGHT - 85), static_cast<float>(85 + i * CELL_WIDTH));
        horizontal_line.rotate(90);
        vertical_line.setSize(sf::Vector2f(2.0f, static_cast<float>(WINDOW_HEIGHT -
                                                                    170))); // Set the thickness and height of the line
        vertical_line.setPosition(static_cast<float>(85 + i * CELL_WIDTH), 85); // Center the line horizontally
        window.draw(vertical_line);
        window.draw(horizontal_line);
    }
}

void GUI::drawEntities() {
    // draw snake body
    for (Coordinate coord: game.snakeCoords) {
        sf::RectangleShape bodyPart;
        bodyPart.setSize(sf::Vector2f(24, 24));
        bodyPart.setPosition(sf::Vector2f(85 + coord.x * CELL_WIDTH + 4, 85 + coord.y * CELL_WIDTH + 4));
        bodyPart.setFillColor(sf::Color::Green);
        window.draw(bodyPart);
    }

    sf::Text t;
    t.setCharacterSize(CELL_WIDTH);
    t.setFont(font);
    t.setFillColor(sf::Color::Green);
    t.setPosition(400, 50);
    switch (game.snakeDirection) {
        case UP:
            t.setString("UP");
            break;
        case DOWN:
            t.setString("DOWN");
            break;
        case LEFT:
            t.setString("LEFT");
            break;
        case RIGHT:
            t.setString("RIGHT");
            break;
    }

    t.setString(std::to_string(game.score));
    window.draw(t);

    drawFruit();
}

GUI::GUI(sf::RenderWindow &window, Game &game, sf::Font &font) : window(window), game(game), font(font) {
    WINDOW_WIDTH = 800;
    WINDOW_HEIGHT = 800;
}

void GUI::drawFruit() {
    sf::CircleShape fruit;
    fruit.setRadius(CELL_WIDTH / 2.0 - 2.0f);
    fruit.setPosition(sf::Vector2f(85 + game.fruitCoord.x * CELL_WIDTH + 2, 85 + game.fruitCoord.y * CELL_WIDTH + 2));
    fruit.setFillColor(sf::Color::Red);
    window.draw(fruit);

//    sf::Text t;
//    t.setCharacterSize(CELL_WIDTH);
//    t.setFont(font);
//    t.setFillColor(sf::Color::Green);
//    t.setPosition(85 + game.fruitCoord.y * CELL_WIDTH, 85 + game.fruitCoord.x * CELL_WIDTH);
//    t.setString(std::to_string(game.fruitCoord.x) + " " + std::to_string(game.fruitCoord.y));
//    window.draw(t);
}

void GUI::drawGameOver() {
    sf::Text t;
    t.setCharacterSize(80);
    t.setFont(font);
    t.setFillColor(sf::Color::Red);
    t.setPosition(155, 360);
    t.setString("GAME OVER\nScore: " + std::to_string(game.score) + "\nPress R to restart");
    window.draw(t);
}
