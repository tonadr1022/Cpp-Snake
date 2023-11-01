//
// Created by Tony Adriansen on 10/31/23.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include "enums.h"
#include <deque>
#include <random>

struct Coordinate {

    int x;
    int y;

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }
};

class Game {
public:
    Game();
    GameState gameState;
    Coordinate fruitCoord{};
    Direction snakeDirection;
    std::deque<Coordinate> snakeCoords;
    int score{0};
    void pauseGame();
    void resumeGame();
    void endGame();
    void restartGame();

    void generateNextFruit();
    void startGame();
    void updateState(Direction newDirection);

private:
    std::default_random_engine rand_generator;
    std::uniform_int_distribution<int> int_distribution;
    static unsigned int createSeed();
    int getRandInt();
    Coordinate getRandCoords();


};


#endif //SNAKE_GAME_H
