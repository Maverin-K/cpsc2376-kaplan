#include <iostream>
#include <vector>

enum class Cell { EMPTY, PLAYER_1, PLAYER_2 };
enum class GameState { ONGOING, PLAYER_1_WINS, PLAYER_2_WINS, DRAW };

const int ROWS = 6;
const int COLS = 7;

void printRules();
void makeBoard(std::vector<std::vector<Cell>>& board);
void printBoard(const std::vector<std::vector<Cell>>& board);
bool play(std::vector<std::vector<Cell>>& board, int column, Cell player);
GameState gameStatus(const std::vector<std::vector<Cell>>& board);
bool isValidMove(const std::vector<std::vector<Cell>>& board, int column);

void printRules() {
    std::cout << "Welcome to Connect Four!" << std::endl;
    std::cout << "Players take turns dropping pieces into columns." << std::endl;
    std::cout << "First to four in a row wins!" << std::endl;
    std::cout << "Enter a column number (0-6) to drop your piece." << std::endl;
}

void makeBoard(std::vector<std::vector<Cell>>& board) {
    board.assign(ROWS, std::vector<Cell>(COLS, Cell::EMPTY));
}

void printBoard(const std::vector<std::vector<Cell>>& board) {
    for (const auto& row : board) {
        for (Cell cell : row) {
            char symbol = (cell == Cell::PLAYER_1) ? 'X' : (cell == Cell::PLAYER_2) ? 'O' : '.';
            std::cout << symbol << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "_____________" << std::endl;
    std::cout << "0 1 2 3 4 5 6" << std::endl;
}

bool isValidMove(const std::vector<std::vector<Cell>>& board, int column) {
    return column >= 0 && column < COLS && board[0][column] == Cell::EMPTY;
}

bool play(std::vector<std::vector<Cell>>& board, int column, Cell player) {
    if (!isValidMove(board, column)) return false;

    for (int row = ROWS - 1; row >= 0; --row) {
        if (board[row][column] == Cell::EMPTY) {
            board[row][column] = player;
            return true;
        }
    }
    return false;
}

GameState gameStatus(const std::vector<std::vector<Cell>>& board) {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (board[r][c] == Cell::EMPTY) continue;
            Cell player = board[r][c];

            if (c + 3 < COLS && board[r][c + 1] == player && board[r][c + 2] == player && board[r][c + 3] == player)
                return (player == Cell::PLAYER_1) ? GameState::PLAYER_1_WINS : GameState::PLAYER_2_WINS;
            if (r + 3 < ROWS && board[r + 1][c] == player && board[r + 2][c] == player && board[r + 3][c] == player)
                return (player == Cell::PLAYER_1) ? GameState::PLAYER_1_WINS : GameState::PLAYER_2_WINS;
            if (r + 3 < ROWS && c + 3 < COLS && board[r + 1][c + 1] == player && board[r + 2][c + 2] == player && board[r + 3][c + 3] == player)
                return (player == Cell::PLAYER_1) ? GameState::PLAYER_1_WINS : GameState::PLAYER_2_WINS;
            if (r - 3 >= 0 && c + 3 < COLS && board[r - 1][c + 1] == player && board[r - 2][c + 2] == player && board[r - 3][c + 3] == player)
                return (player == Cell::PLAYER_1) ? GameState::PLAYER_1_WINS : GameState::PLAYER_2_WINS;
        }
    }
    for (int c = 0; c < COLS; ++c)
        if (board[0][c] == Cell::EMPTY)
            return GameState::ONGOING;
    return GameState::DRAW;
}

int main() {
    char playAgain;
    do {
        std::vector<std::vector<Cell>> board;
        makeBoard(board);
        printRules();

        Cell currentPlayer = Cell::PLAYER_1;
        GameState state = GameState::ONGOING;

        while (state == GameState::ONGOING) {
            printBoard(board);
            int column;
            std::cout << "Player " << ((currentPlayer == Cell::PLAYER_1) ? "1" : "2") << " - Choose a column: ";
            while (!(std::cin >> column) || !isValidMove(board, column)) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Invalid input. Choose a valid column (0-6): ";
            }

            play(board, column, currentPlayer);
            state = gameStatus(board);
            currentPlayer = (currentPlayer == Cell::PLAYER_1) ? Cell::PLAYER_2 : Cell::PLAYER_1;
        }

        printBoard(board);
        if (state == GameState::PLAYER_1_WINS)
            std::cout << "Player 1 wins!" << std::endl;
        else if (state == GameState::PLAYER_2_WINS)
            std::cout << "Player 2 wins!" << std::endl;
        else
            std::cout << "It's a draw!" << std::endl;

        std::cout << "Play again? (y/n): ";
        std::cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
