#include "game.h"

Game::Game() {
    board = std::vector<std::vector<Player>>(6, std::vector<Player>(7, Player::EMPTY));
    currentPlayer = Player::PLAYER_1;
    gameStatus = Status::ONGOING;
}

void Game::play(int column) {
    if (gameStatus != Status::ONGOING) return;

    if (isValidMove(column)) {
        int row = getNextAvailableRow(column);
        board[row][column] = currentPlayer;

        if (checkWin()) {
            gameStatus = (currentPlayer == Player::PLAYER_1) ? Status::PLAYER_1_WINS : Status::PLAYER_2_WINS;
        }
        else if (isBoardFull()) {
            gameStatus = Status::DRAW;
        }

        currentPlayer = (currentPlayer == Player::PLAYER_1) ? Player::PLAYER_2 : Player::PLAYER_1;
    }
}

Game::Status Game::status() const {
    return gameStatus;
}

void Game::display() const {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (board[i][j] == Player::EMPTY)
                std::cout << ".";
            else if (board[i][j] == Player::PLAYER_1)
                std::cout << "X";
            else
                std::cout << "O";
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

bool Game::isBoardFull() const {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (board[i][j] == Player::EMPTY)
                return false;
        }
    }
    return true;
}

bool Game::checkWin() const {
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            if (board[row][col] != Player::EMPTY) {
                if (col + 3 < 7 && board[row][col] == board[row][col + 1] && board[row][col] == board[row][col + 2] && board[row][col] == board[row][col + 3])
                    return true;
                if (row + 3 < 6 && board[row][col] == board[row + 1][col] && board[row][col] == board[row + 2][col] && board[row][col] == board[row + 3][col])
                    return true;
                if (row + 3 < 6 && col + 3 < 7 && board[row][col] == board[row + 1][col + 1] && board[row][col] == board[row + 2][col + 2] && board[row][col] == board[row + 3][col + 3])
                    return true;
                if (row + 3 < 6 && col - 3 >= 0 && board[row][col] == board[row + 1][col - 1] && board[row][col] == board[row + 2][col - 2] && board[row][col] == board[row + 3][col - 3])
                    return true;
            }
        }
    }
    return false;
}

bool Game::isValidMove(int column) const {
    return column >= 0 && column < 7 && board[0][column] == Player::EMPTY;
}

int Game::getNextAvailableRow(int column) const {
    for (int row = 5; row >= 0; --row) {
        if (board[row][column] == Player::EMPTY) {
            return row;
        }
    }
    return -1;
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
    game.display();
    return os;
}
