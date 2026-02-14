#pragma once
#include "Card.h"
#include <vector>

// class managing the deck of 52 cards
class Deck {
private:
    // stores the actual card objects
    std::vector<Card*> Cards;

public:
    // constructor
    Deck();
    // destructor
    ~Deck();
    // returns top card and removes from deck
    Card* Draw();
    // randomizes card order
    void Shuffle();
    // debug helper
    void PrintDeck();
    // returns current deck size
    int GetRemainingCards() { return Cards.size(); }
};