#pragma once
#include <vector>
#include <string>

class Card {
private:
    int val;
    char suit;

public:
    Card(int v, char s);

    int getValue() const;
    char getSuit() const;
    std::string toString() const;
};

class Deck {
private:
    std::vector<Card> cards;
    int currentIndex = 0;

public:
    Deck();

    Card deal();
    void shuffle();
    bool isEmpty() const;
};

class Player {
private:
    std::string name;
    int chips;
    int seat;
    bool active;
    std::vector<Card> hand;

public:
    Player(const std::string& name, int chips, int seat);

    void dealCard(const Card& card);
    void resetHand();
    void fold();

    std::string getName() const;
    int getChips() const;
    int getSeat() const;
    bool isActive() const;
    std::vector<Card> getHand() const;
};

class Table {
private:
    std::vector<Player> players;
    std::vector<Card> community;
    Deck deck;

public:
    void addPlayer(const std::string& name, int chips, int seat);
    void startHand();
    void dealFlop();
    void dealTurn();
    void dealRiver();

    const std::vector<Player>& getPlayers() const;
    const std::vector<Card>& getCommunity() const;
};
