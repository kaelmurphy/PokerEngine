#include "header.h"
#include <iostream>

int main() {
    Game game;

    // Start game and initialize players
    game.startGame();

    // Display players and their hands
    const std::vector<Player>& players = game.getPlayers();
    std::cout << "\n== Players and Hands ==\n";
    for (const Player& player : players) {
        std::cout << player.getName() << ": ";
        for (const Card& card : player.getHand()) {
            std::cout << card.toString() << " ";
        }
        std::cout << "\n";
    }

    // Pre-flop betting round
    game.bettingRound("pre-flop");

    // Deal and display flop
    game.dealFlop();
    std::cout << "\n== Flop ==\n";
    for (const Card& card : game.getCommunity()) {
        std::cout << card.toString() << " ";
    }
    std::cout << "\n";

    // Post-flop betting round
    game.bettingRound("post-flop");

    // Deal and display turn
    game.dealTurn();
    std::cout << "\n== Turn ==\n";
    for (const Card& card : game.getCommunity()) {
        std::cout << card.toString() << " ";
    }
    std::cout << "\n";

    // Turn betting round
    game.bettingRound("turn");

    // Deal and display river
    game.dealRiver();
    std::cout << "\n== River ==\n";
    for (const Card& card : game.getCommunity()) {
        std::cout << card.toString() << " ";
    }
    std::cout << "\n";

    // Final betting round
    game.bettingRound("river");

    return 0;
}