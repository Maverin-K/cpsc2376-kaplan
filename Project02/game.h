#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

class Game {
public:
    enum class Status {
        ONGOING,
        PLAYER_1_WINS,
        PLAYER_2_WINS,
        DRAW
    };

    enum class Player {
        EMPTY,
        PLAYER_1,
        PLAYER_2
    };

    Game();
    void play(int column);
    Status status() const;
    void display() const;

    friend std::ostream& operator<<(std::ostream& os, const Game& game);

    Player getCurrentPlayer() const { return currentPlayer; }

private:
    std::vector<std::vector<Player>> board;
    Player currentPlayer;
    Status gameStatus;

    bool isBoardFull() const;
    bool checkWin() const;
    bool isValidMove(int column) const;
    int getNextAvailableRow(int column) const;
};

#endif
