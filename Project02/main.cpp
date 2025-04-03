#include <iostream>
#include "game.h"

int main() {
    Game game;
    int column;

    while (game.status() == Game::Status::ONGOING) {
        game.display();

        if (game.getCurrentPlayer() == Game::Player::PLAYER_1) {
            std::cout << "Player 1 (X), choose a column (0-6): ";
        }
        else {
            std::cout << "Player 2 (O), choose a column (0-6): ";
        }

        std::cin >> column;
        game.play(column);
    }

    game.display();

    switch (game.status()) {
    case Game::Status::PLAYER_1_WINS:
        std::cout << "Player 1 (X) wins!" << std::endl;
        break;
    case Game::Status::PLAYER_2_WINS:
        std::cout << "Player 2 (O) wins!" << std::endl;
        break;
    case Game::Status::DRAW:
        std::cout << "It's a draw!" << std::endl;
        break;
    default:
        break;
    }

    return 0;
}
