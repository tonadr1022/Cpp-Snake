//
// Created by Tony Adriansen on 10/31/23.
//
#include <iostream>
#include "Game.h"
#include <chrono>


Coordinate Game::getRandCoords() {
    return Coordinate{getRandInt(), getRandInt()};
}

void Game::generateNextFruit() {
    Coordinate initCoords = getRandCoords();
    Coordinate curr = initCoords;
    while (true) {
        curr = getRandCoords();
        for (Coordinate snakeCoord: snakeCoords) {
            if (fruitCoord == snakeCoord) {
                break;
            }
        }
        break;
    }
    fruitCoord = curr;
}

Game::Game() : rand_generator(createSeed()), int_distribution(0, 20),
               gameState(NONE), snakeDirection(LEFT) {

}

unsigned int Game::createSeed() {
    return static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
}


int Game::getRandInt() {
    return int_distribution(rand_generator);
}

void Game::startGame() {
    // init snake body
    for (int col = 7; col < 12; col++) {
        snakeCoords.push_back({10, col});
    }
    // reset fruit
    generateNextFruit();
}


void Game::updateState(Direction newDirection) {
snakeDirection = newDirection;
    Coordinate frontCoords = snakeCoords.front();
    Coordinate nextCoord = frontCoords;
    switch (newDirection) {
        case UP:
            nextCoord.y -= 1;
            break;
        case DOWN:
            nextCoord.y += 1;
            break;
        case RIGHT:
            nextCoord.x += 1;
            break;
        case LEFT:
            nextCoord.x -= 1;
            break;
    }

    // check snake eats fruit
    if (nextCoord == fruitCoord) {
        generateNextFruit();
        snakeCoords.push_front(nextCoord);
        score++;

        // check snake collides with itself
    } else if (std::find(snakeCoords.begin(), snakeCoords.end(), nextCoord) != snakeCoords.end()) {
        endGame();

        // check snake collides with wall
    } else if (nextCoord.x < 0 || nextCoord.x > 20 || nextCoord.y < 0 || nextCoord.y > 20) {
        endGame();

        // otherwise move snake forward in the direction it is facing
    } else {
        snakeCoords.push_front(nextCoord);
        snakeCoords.pop_back();
    }
}

void Game::pauseGame() {
    gameState = PAUSED;
}

void Game::resumeGame() {
    gameState = PLAYING;
}

void Game::endGame() {
    gameState = GAME_OVER;
}

void Game::restartGame() {
    snakeCoords.clear();
    startGame();
    score = 0;
    gameState = PLAYING;
}
