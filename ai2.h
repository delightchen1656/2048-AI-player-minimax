#ifndef AI2_H
#define AI2_H

#include "gameboard.h"
#include <climits>

extern int a,b,c,d,e;
/**
 * @file AI2.h
 * @brief Function declarations for AI moves in a game.
 */

/**
 * @brief Gets the next move for the AI in the game.
 *
 * This function evaluates the current state of the game and determines the best move for the AI.
 *
 * @param game A constant reference to the current state of the GameBoard.
 * @return A character representing the next move.
 */
char getNextMove2(const GameBoard& game);

/**
 * @brief Implements the alpha-beta pruning algorithm to optimize the minimax decision process.
 *
 * Alpha-beta pruning is used to reduce the number of nodes evaluated in the minimax algorithm,
 * which helps in efficient decision-making for AI in games.
 *
 * @param board A reference to the GameBoard being evaluated.
 * @param depth The current depth in the game tree.
 * @param alpha The current alpha value, representing the best already explored option along the path to the root for the maximizer.
 * @param beta The current beta value, representing the best already explored option along the path to the root for the minimizer.
 * @param maximizingPlayer A boolean that is true if the current move is by the maximizing player; otherwise, it's false.
 * @return An integer representing the score calculated from the alpha-beta pruning algorithm.
 */
int alphaBeta(GameBoard& board, int depth, int alpha, int beta, bool maximizingPlayer);

#endif // AI2_H