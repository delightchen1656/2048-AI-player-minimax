#include "ai1.h"

char getNextMove1(const GameBoard& game) {
    static const char commands[] = {'w', 'a', 's', 'd'};
    static int i = 0;  // Static to preserve its value across loop iterations
    char command = commands[i % 4];
    i++;
    return command;
}

