#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

/**
 * @brief Class representing a game board, specifically designed for a 2048 game logic.
 */
class GameBoard {
private:
    static const int SIZE = 4; // Board size, set to 4x4 for the 2048 game.
    std::vector<std::vector<int>> board; // 2D vector to store the game state.
    int score; // Current score of the game.
    char lastMove; // Last move made by the player.

public:
    /**
     * @brief Default constructor that initializes a new game board.
     */
    GameBoard();

    /**
     * @brief Copy constructor.
     * @param other The game board to copy.
     */
    GameBoard(const GameBoard& other);

    /**
     * @brief Prints the current state of the board to the console.
     */
    void printBoard() const;

    /**
     * @brief Adds a random tile to the board in a vacant space.
     */
    void addRandom();

    /**
     * @brief Checks if any moves are possible on the current board.
     * @return true if a move can be made, false otherwise.
     */
    bool canMove() const;

    /**
     * @brief Compresses the board by sliding all tiles to the left.
     */
    void compress();

    /**
     * @brief Merges tiles on the board that are adjacent and have the same value.
     */
    void merge();

    /**
     * @brief Attempts to move all tiles on the board to the left.
     * @return true if the move was successful, false otherwise.
     */
    bool moveLeft();

    /**
     * @brief Rotates the board 90 degrees clockwise.
     */
    void rotateBoard();

    /**
     * @brief Attempts to move all tiles on the board to the right.
     * @return true if the move was successful, false otherwise.
     */
    bool moveRight();

    /**
     * @brief Attempts to move all tiles on the board upward.
     * @return true if the move was successful, false otherwise.
     */
    bool moveUp();

    /**
     * @brief Attempts to move all tiles on the board downward.
     * @return true if the move was successful, false otherwise.
     */
    bool moveDown();

    /**
     * @brief Makes a move on the board based on the input character.
     * @param move The character representing the move direction (wasd).
     * @return true if the move was successful, false otherwise.
     */
    bool makeMove(char move);

    /**
     * @brief Retrieves the current score of the game.
     * @return Current score as an integer.
     */
    int getScore() const;

    /**
     * @brief Retrieves the maximum tile value on the board.
     * @return Maximum tile value as an integer.
     */
    int maxTile() const;
    /**
     * @brief Counts the number of empty spaces on the board.
     * @return Number of empty spaces.
     */
    int countEmptySpaces() const;
    int monotonicity() const;  // 计算棋盘的单调性得分
    int maxTilePosition() const;  // 计算最大瓦片位置得分
    int smoothness() const;  // 计算棋盘的平滑性得分
    
};

#endif // GAMEBOARD_H
