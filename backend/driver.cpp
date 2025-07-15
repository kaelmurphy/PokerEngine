#include "header.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <stdexcept>

//Card

Card::Card(int v, char s) : val(v), suit(s) {}

int Card::getValue() const { return val; }

char Card::getSuit() const { return suit; }

std::string Card::toString() const {
    std::string valStr;
    if (val <= 10) valStr = std::to_string(val);
    else if (val == 11) valStr = "J";
    else if (val == 12) valStr = "Q";
    else if (val == 13) valStr = "K";
    else if (val == 14) valStr = "A";

    return valStr + suit;
}

//Deck

Deck::Deck() {
    const char suits[] = {'H', 'D', 'S', 'C'};
    for (char s : suits) {
        for (int v = 2; v <= 14; ++v) {
            cards.emplace_back(v, s);
        }
    }
    for (int i = 0; i < 5; ++i) shuffle();
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cards.begin(), cards.end(), gen);
    currentIndex = 0;
}

Card Deck::deal() {
    if (isEmpty()) throw std::out_of_range("Deck is empty.");
    return cards[currentIndex++];
}

bool Deck::isEmpty() const {
    return currentIndex >= cards.size();
}

//Player

Player::Player(const std::string& name, int chips, int seat)
    : name(name), chips(chips), seat(seat), active(true) {}

void Player::dealCard(const Card& card) {
    if (hand.size() < 2) hand.push_back(card);
}

void Player::resetHand() {
    hand.clear();
    active = true;
}

void Player::fold() {
    active = false;
}

std::string Player::getName() const { return name; }

int Player::getChips() const { return chips; }

int Player::getSeat() const { return seat; }

bool Player::isActive() const { return active; }

std::vector<Card> Player::getHand() const { return hand; }

//Table

void Table::addPlayer(const std::string& name, int chips, int seat) {
    players.emplace_back(name, chips, seat);
}

void Table::startHand() {
    community.clear();
    deck.shuffle();
    for (Player& p : players) p.resetHand();

    for (int i = 0; i < 2; ++i) {
        for (Player& p : players) {
            p.dealCard(deck.deal());
        }
    }
}

void Table::dealFlop() {
    for (int i = 0; i < 3; ++i) {
        community.push_back(deck.deal());
    }
}

void Table::dealTurn() {
    community.push_back(deck.deal());
}

void Table::dealRiver() {
    community.push_back(deck.deal());
}

const std::vector<Player>& Table::getPlayers() const { return players; }

const std::vector<Card>& Table::getCommunity() const { return community; }

//Game

void Game::setup() {
    table.addPlayer("Alice", 1000, 0);
    table.addPlayer("Bob", 1000, 1);
    table.addPlayer("Charlie", 1000, 2);
    table.addPlayer("Dana", 1000, 3);
    table.addPlayer("Eli", 1000, 4);
    table.addPlayer("Frank", 1000, 5);
    table.addPlayer("Grace", 1000, 6);
    table.addPlayer("Hank", 1000, 7);
    table.addPlayer("Ivy", 1000, 8);
    table.addPlayer("Jack", 1000, 9);
}

void Game::startGame() {
    setup();
    table.startHand();
}

void Game::playHand() {
    table.startHand();
    dealFlop();
    dealTurn();
    dealRiver();

    std::cout << "\n== Player Hands ==\n";
    for (const auto& p : table.getPlayers()) {
        std::cout << p.getName() << ": ";
        for (const auto& c : p.getHand()) {
            std::cout << c.toString() << " ";
        }
        std::cout << '\n';
    }

    std::cout << "\n== Community Cards ==\n";
    for (const auto& c : table.getCommunity()) {
        std::cout << c.toString() << " ";
    }
    std::cout << "\n";
}

void Game::bettingRound(const std::string& stage) {
    const std::vector<Player>& players = table.getPlayers();
    std::cout << "\n[" << stage << " betting round]\n";
    for (const auto& player : players) {
        if (player.isActive()) {
            std::cout << player.getName() << " checks.\n";
        }
    }
}

void Game::dealFlop() { table.dealFlop(); }

void Game::dealTurn() { table.dealTurn(); }

void Game::dealRiver() { table.dealRiver(); }

const std::vector<Player>& Game::getPlayers() const { return table.getPlayers(); }

const std::vector<Card>& Game::getCommunity() const { return table.getCommunity(); }