#include <iostream>
#include "header.h"

void printPlayerHands(const std::vector<Player>& players) {
    for (const auto& p : players) {
        std::cout << p.getName() << " (Seat " << p.getSeat() << "): ";
        for (const Card& c : p.getHand()) {
            std::cout << c.toString() << " ";
        }
        std::cout << '\n';
    }
}

void printCommunityCards(const std::vector<Card>& board) {
    std::cout << "Community Cards: ";
    for (const Card& c : board) {
        std::cout << c.toString() << " ";
    }
    std::cout << '\n';
}

int main() {
    Table table;

    table.addPlayer("Alice", 1000, 0);
    table.addPlayer("Bob", 1000, 1);
    table.addPlayer("Charlie", 1000, 2);

    table.startHand();
    table.dealFlop();
    table.dealTurn();
    table.dealRiver();

    std::cout << "\n== Player Hands ==\n";
    printPlayerHands(table.getPlayers());

    std::cout << "\n== Table Board ==\n";
    printCommunityCards(table.getCommunity());

    return 0;
}