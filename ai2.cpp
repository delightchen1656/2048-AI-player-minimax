#include "ai2.h"

char getNextMove2(const GameBoard& game) {
    int bestValue = INT_MIN; 
    char bestMove = ' ';     
    int alpha = INT_MIN, beta = INT_MAX; 

    static const char moves[] = {'w', 'a', 's', 'd'};

    for (char move : moves) {
        GameBoard boardCopy = game; 
        if (boardCopy.makeMove(move)) { 
            int moveValue = alphaBeta(boardCopy, a , alpha, beta, true); 
            if (moveValue > bestValue) { 
                bestValue = moveValue;
                bestMove = move; 
            }
        }
    }
    return bestMove; 
}


int alphaBeta(GameBoard& board, int depth, int alpha, int beta, bool maximizingPlayer) {
    if (depth == 0 || !board.canMove()) { 
        return b*board.countEmptySpaces()+c*board.monotonicity()+d*board.maxTilePosition()+e*board.smoothness(); 
    }
    if (maximizingPlayer) {
        int maxEval = INT_MIN; 
        for (char move : {'w', 'a', 's', 'd'}) { 
            GameBoard boardCopy = board;
            if (boardCopy.makeMove(move)) { 
                int eval = alphaBeta(boardCopy, depth - 1, alpha, beta, false); 
                maxEval = std::max(maxEval, eval); 
                alpha = std::max(alpha, eval); 
                if (beta <= alpha) {
                    break; 
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX; // Best evaluation for minimizer
        for (char move : {'w', 'a', 's', 'd'}) { // Explore all possible moves
            GameBoard boardCopy = board;
            if (boardCopy.makeMove(move)) { // If the move is successful
                int eval = alphaBeta(boardCopy, depth - 1, alpha, beta, true); // Recurse for maximizing player
                minEval = std::min(minEval, eval); // Update the minimum evaluation
                beta = std::min(beta, eval); // Update beta
                if (beta <= alpha) {
                    break; // Alpha cutoff
                }
            }
        }
        return minEval;
    }
}