#pragma once
#include <vector>
#include <iostream>
#include "Engine.h"

class Game {
public:
    enum Cell { BLANK, X, O };
    enum GameStatus { ONGOING, X_WON, O_WON, DRAW };

    Game(int boardSize = 7);

    void printBoard() const;
    bool play(int row, int col);
    GameStatus getStatus() const;
    Cell getCurrentToken() const;
    void draw(Engine* e, int row = -1, int col = -1);
    int moveCount();

private:
    std::vector<std::vector<Cell>> board;
    int boardSize;

    bool isFull() const;
    void horizontalBar() const;
};
