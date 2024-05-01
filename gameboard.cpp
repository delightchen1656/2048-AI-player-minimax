#include "gameboard.h"

// default constructor
GameBoard::GameBoard() : score(0), lastMove(0) {
    board = std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE, 0));
    srand(static_cast<unsigned int>(time(NULL)));
    addRandom();
    addRandom();    // 2048 game start with 2 random number.
}

// copy constructor
GameBoard::GameBoard(const GameBoard& other)
    : board(other.board), score(other.score), lastMove(other.lastMove) {
}

// score getter
int GameBoard::getScore() const {
    return score;
}

// print the board to let player see
void GameBoard::printBoard() const {
    std::cout << "Score: " << score << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) std::cout << ".\t";
            else std::cout << board[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

// add a random number to the board, use the law:
// 90% "2" and 10% "4" generate in board.
void GameBoard::addRandom() {
    int x, y;
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (board[x][y] != 0);
    board[x][y] = (rand() % 10 < 9) ? 2 : 4;
}

// check the game board can move or not
bool GameBoard::canMove() const {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) return true;
            if (j + 1 < SIZE && board[i][j] == board[i][j + 1]) return true;
            if (i + 1 < SIZE && board[i][j] == board[i + 1][j]) return true;
        }
    }
    return false;
}

// The non-zero numbers on the game board 
// are compressed to the left of the row in 
// preparation for the merge and move operations.
void GameBoard::compress() {
    for (int i = 0; i < SIZE; ++i) {
        int k = 0;
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] != 0) {
                board[i][k++] = board[i][j];
            }
        }
        for (; k < SIZE; ++k) {
            board[i][k] = 0;
        }
    }
}

// merge the number
void GameBoard::merge() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) {
            if (board[i][j] == board[i][j + 1] && board[i][j] != 0) {
                board[i][j] *= 2;
                score += board[i][j];
                board[i][j + 1] = 0;
            }
        }
    }
}

// move to left, command "a"
bool GameBoard::moveLeft() {
    srand(static_cast<unsigned int>(time(NULL)));
    std::vector<std::vector<int>> oldBoard = board;
    compress();
    merge();
    compress();
    bool moved = (oldBoard != board);
    if (moved) {
        addRandom();
    }
    return moved;
}

void GameBoard::rotateBoard() {
    std::vector<std::vector<int>> temp(SIZE, std::vector<int>(SIZE));
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[j][SIZE - 1 - i] = board[i][j];
        }
    }
    board = temp;
}

// move to right, command "d"
bool GameBoard::moveRight() {
    rotateBoard();
    rotateBoard();
    bool moved = moveLeft();
    rotateBoard();
    rotateBoard();
    return moved;
}

// move to up, command "w"
bool GameBoard::moveUp() {
    rotateBoard();
    rotateBoard();
    rotateBoard();
    bool moved = moveLeft();
    rotateBoard();
    return moved;
}

// move to down, command "s"
bool GameBoard::moveDown() {
    rotateBoard();
    bool moved = moveLeft();
    rotateBoard();
    rotateBoard();
    rotateBoard();
    return moved;
}

// make the movement
bool GameBoard::makeMove(char move) {
    bool validMove = false;
    switch (move) {
        case 'w': validMove = moveUp(); break;
        case 's': validMove = moveDown(); break;
        case 'a': validMove = moveLeft(); break;
        case 'd': validMove = moveRight(); break;
        default: validMove = false; break;
    }
    return validMove;
}

int GameBoard::maxTile() const {
    int maxTile = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] > maxTile) {
                maxTile = board[i][j];
}
        }
    }
    return maxTile;
}

// count the empty space, preparation for the heuristic function
int GameBoard::countEmptySpaces() const {
    int count = 0;
    for (const auto& row : board) {
        for (int cell : row) {
            if (cell == 0) {
                count++;
            }
        }
    }
    return (count * 100) / (SIZE * SIZE);
}

int GameBoard::monotonicity() const {
    int score = 0;
    int maxScore = 2 * SIZE * (SIZE - 1); 
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) {
            if (board[i][j] <= board[i][j + 1]) score++;
            if (board[i][j] >= board[i][j + 1]) score++;
        }
        for (int j = 0; j < SIZE - 1; ++j) {
            if (board[j][i] <= board[j + 1][i]) score++;
            if (board[j][i] >= board[j + 1][i]) score++;
        }
    }
    return (score * 100) / maxScore;
}

int GameBoard::maxTilePosition() const {
    int maxTile = 0;
    int cornerCount = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] > maxTile) maxTile = board[i][j];
        }
    }
    if (board[0][0] == maxTile) cornerCount++;
    if (board[0][SIZE - 1] == maxTile) cornerCount++;
    if (board[SIZE - 1][0] == maxTile) cornerCount++;
    if (board[SIZE - 1][SIZE - 1] == maxTile) cornerCount++;
    if (cornerCount > 0) {
        return 100 * cornerCount / 4;
    }
    return 0;
}

int GameBoard::smoothness() const {
    int smoothScore = 0;
    int totalDiff = 0; 
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) {
            totalDiff += abs(board[i][j] - board[i][j + 1]);       
            totalDiff += abs(board[j][i] - board[j + 1][i]);
        }
    }
    if (totalDiff == 0) return 100; 
    int maxDiff = 2 * SIZE * (SIZE - 1) * (2048 - 2); 
    smoothScore = 100 - (totalDiff * 100 / maxDiff);
    return smoothScore;
}
