#include "Game.h"

Game::Game(int boardSize)
    : boardSize(boardSize), board(boardSize, std::vector<Cell>(boardSize, BLANK))
{}

bool Game::isFull() const {
    for (const auto& row : board)
        for (auto cell : row)
            if (cell == BLANK)
                return false;
    return true;
}

void Game::horizontalBar() const {
    std::cout << " +";
    for (int col = 0; col < boardSize; ++col)
        std::cout << "---+";
    std::cout << "\n";
}

int Game::moveCount() {
    int sum = 0;
    for (int row = 0; row < boardSize; ++row)
        for (int col = 0; col < boardSize; ++col)
            sum += board[row][col] != BLANK;
    return sum;
}

void Game::draw(Engine* e, int r, int c) {
    int tokenRadius = 30;
    Cell current = getCurrentToken();
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            int cx = 50 + 100 * col;
            int cy = 50 + 100 * row;
            e->drawRectangle(cx, cy, 90, 90, {100, 60, 200, 255});
            if (board[row][col] != BLANK)
                e->drawCircle(cx + 5, cy + 5, tokenRadius, {0, 0, 0, 64});

            if (board[row][col] == X)
                e->drawCircle(cx, cy, tokenRadius, {0, 0, 0, 255});
            else if (board[row][col] == O)
                e->drawCircle(cx, cy, tokenRadius, {255, 255, 255, 255});
            else if (r == row && c == col && board[row][col] == BLANK) {
                if (current == X) e->drawCircle(cx, cy, tokenRadius, {0, 0, 0, 128});
                else e->drawCircle(cx, cy, tokenRadius, {255, 255, 255, 125});
            }
        }
    }
}

void Game::printBoard() const {
    std::cout << "   ";
    for (int col = 1; col <= boardSize; ++col)
        std::cout << col << "   ";
    std::cout << "\n";

    for (int row = 0; row < boardSize; ++row) {
        horizontalBar();
        std::cout << row + 1 << "|";
        for (int col = 0; col < boardSize; ++col) {
            char symbol = ' ';
            if (board[row][col] == X)
                symbol = 'X';
            else if (board[row][col] == O)
                symbol = 'O';
            std::cout << " " << symbol << " |";
        }
        std::cout << "\n";
    }
    horizontalBar();
}

Game::Cell Game::getCurrentToken() const {
    int count = 0;
    for (const auto& row : board)
        for (auto cell : row)
            if (cell != BLANK)
                ++count;
    return (count % 2 == 0) ? X : O;
}

bool Game::play(int row, int col) {
    if (row < 0 || row >= boardSize || col < 0 || col >= boardSize)
        return false;
    if (board[row][col] != BLANK)
        return false;
    board[row][col] = getCurrentToken();
    return true;
}

Game::GameStatus Game::getStatus() const {
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize - 4; ++col) {
            if (board[row][col] != BLANK) {
                Cell token = board[row][col];
                bool isWinner = true;
                for (int i = 1; i < 5; i++) {
                    if (board[row][col + i] != token) {
                        isWinner = false;
                        break;
                    }
                }
                if (isWinner)
                    return token == X ? X_WON : O_WON;
            }
        }
    }
    for (int row = 0; row < boardSize - 4; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            if (board[row][col] != BLANK) {
                Cell token = board[row][col];
                bool isWinner = true;
                for (int i = 1; i < 5; i++) {
                    if (board[row + i][col] != token) {
                        isWinner = false;
                        break;
                    }
                }
                if (isWinner)
                    return token == X ? X_WON : O_WON;
            }
        }
    }
    for (int row = 0; row < boardSize - 4; ++row) {
        for (int col = 0; col < boardSize - 4; ++col) {
            if (board[row][col] != BLANK) {
                Cell token = board[row][col];
                bool isWinner = true;
                for (int i = 1; i < 5; i++) {
                    if (board[row + i][col + i] != token) {
                        isWinner = false;
                        break;
                    }
                }
                if (isWinner)
                    return token == X ? X_WON : O_WON;
            }
            if (board[row + 4][col] != BLANK) {
                Cell token = board[row + 4][col];
                bool isWinner = true;
                for (int i = 1; i < 5; i++) {
                    if (board[row + 4 - i][col + i] != token) {
                        isWinner = false;
                        break;
                    }
                }
                if (isWinner)
                    return token == X ? X_WON : O_WON;
            }
        }
    }
    return isFull() ? DRAW : ONGOING;
}
