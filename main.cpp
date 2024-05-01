#include <iostream>
#include <vector>
#include <chrono>
#include <numeric> 
#include <map>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <random>
#include "gameboard.h"
#include "ai1.h"
#include "ai2.h"

int a,b,c,d,e;

int main() {
    std::random_device rd;  // 随机数生成器设备
    std::mt19937 gen(rd()); // 标准 mersenne_twister_engine
    std::uniform_int_distribution<> distr(150, 350);
    srand(static_cast<unsigned int>(time(NULL)));
    GameBoard game;
    int initial_choice, auto_mode, ai_choice;
    std::cout << "Select initial mode (1 for manual, 2 for automatic): ";
    std::cin >> initial_choice;

    if (initial_choice == 2) {
        std::cout << "Select auto game mode (1 for single run, 2 for multiple runs): ";
        std::cin >> auto_mode;
        std::cout << "Choose AI algorithm (1 for AI1, 2 for AI2): ";
        std::cin >> ai_choice;
        std::cout << "Choose depth and coeff: ";
        std::cin >> a >> b >> c >> d >> e;
    }

    auto runGame = [&](auto aiFunc) {
        std::map<int, int> tileCounts = { {32, 0}, {64, 0}, {128, 0}, {256, 0}, {512, 0}, {1024, 0}, {2048, 0}, {4096, 0} };

        if (auto_mode == 1) {
            // Single auto game
            while (true) {
                char command = aiFunc(game);
                if (!game.makeMove(command)) continue;
                if (!game.canMove()) {
                    std::cout << "Game Over! Final Score: " << game.getScore() << std::endl;
                    game.printBoard();
                    break;
                }

                game.printBoard();
            }
        } else if (auto_mode == 2) {

            int highestScore = 0, lowestScore = std::numeric_limits<int>::max(), sumScores = 0;
            std::vector<double> times;
            for (int i = 0; i < 100; i++) {  // Updated to 100 runs
                int delay = distr(gen);
                GameBoard localGame; 
                auto start = std::chrono::high_resolution_clock::now();
                while (localGame.canMove()) {
                    char command = aiFunc(localGame); 
                    localGame.makeMove(command);
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> duration = end - start;
                times.push_back(duration.count());

                int finalScore = localGame.getScore();
                int maxTile = localGame.maxTile();
                // Reverse iterate to correctly account for the highest tile reached
                for (auto it = tileCounts.rbegin(); it != tileCounts.rend(); ++it) {
                    if (maxTile >= it->first) {
                        it->second++;
                        break;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                std::cout << "Game #" << (i + 1) << " finished. Score: " << finalScore << ". Max Tile: " << maxTile << std::endl;
                highestScore = std::max(highestScore, finalScore);
                lowestScore = std::min(lowestScore, finalScore);
                sumScores += finalScore;
                localGame.printBoard();
            }
            double averageScore = sumScores / 100.0;
            double averageTime = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
            std::cout << "Highest Score: " << highestScore << std::endl;
            std::cout << "Lowest Score: " << lowestScore << std::endl;
            std::cout << "Average Score: " << averageScore << std::endl;
            std::cout << "Average Duration: " << averageTime << " ms" << std::endl;

            std::cout << "Tile Frequencies:" << std::endl;
            for (const auto& pair : tileCounts) {
                std::cout << "Tile " << pair.first << ": " << pair.second << " times" << std::endl;
            }
        }
    };

    if (initial_choice == 1) {
        // Manual mode
        char command;
        game.printBoard();
        while (true) {
            std::cin >> command;
            if (!game.makeMove(command)) {
                std::cout << "Invalid move. Please try again." << std::endl;
                continue;
            }
            if (!game.canMove()) {
                std::cout << "Game Over! Final Score: " << game.getScore() << std::endl;
                game.printBoard();
                break;
            }
            game.printBoard();
        }
    } else if (initial_choice == 2) {
        // Automatic mode
        if (ai_choice == 1) {
            runGame(getNextMove1);
        } else if (ai_choice == 2) {
            runGame(getNextMove2);
        }
    }

    return 0;
}
