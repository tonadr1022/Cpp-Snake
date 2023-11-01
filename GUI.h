//
// Created by Tony Adriansen on 10/31/23.
//

#ifndef SNAKE_GUI_H
#define SNAKE_GUI_H


#include "SFML/Graphics/RenderWindow.hpp"
#include "Game.h"
#include "SFML/Graphics/Font.hpp"

class GUI {
public:
    static int const CELL_WIDTH = 30;
    explicit GUI(sf::RenderWindow& window, Game& game, sf::Font& font);
    sf::Font font;
    sf::RenderWindow& window;
    Game& game;
    int WINDOW_HEIGHT;
    int WINDOW_WIDTH;
    void draw();
private:

    void drawLines();
    void drawEntities();
    void drawFruit();
    void drawGameOver();

};


#endif //SNAKE_GUI_H
