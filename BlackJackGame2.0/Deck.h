#pragma once
#include "Card.h"
#include <vector>

class Deck {
private:
    std::vector<Card*> Cards; // Stores the stack of Card objects (the deck).

public:
    Deck();
    ~Deck();
    Card* Draw();   // Returns the top card and removes it from the deck.
    void Shuffle(); // Randomizes the order of cards in the vector.
    void PrintDeck(); // Helper to visualize deck content (debugging).
};