#include "Deck.h"
#include <algorithm> // for std::swap
#include <ctime>     // for std::time
#include <cstdlib>   // for std::rand
#include <iostream>

Deck::Deck() {
    std::string suits[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    // --- Generate 52 Cards ---
    for (int s = 0; s < 4; s++) {
        for (int r = 0; r < 13; r++) {
            Card* c = new Card();
            c->Suit = suits[s]; c->Rank = r + 1;
            Cards.push_back(c);
        }
    }
}

Deck::~Deck() { for (Card* c : Cards) delete c; } // Delete all card objects

void Deck::Shuffle() {
    for (int i = 0; i < Cards.size(); i++) {
        int RandomIndex = std::rand() % Cards.size(); // Pick random spot
        std::swap(Cards[i], Cards[RandomIndex]);      // Swap current with random
    }
}

void Deck::PrintDeck() {
    for (Card* c : Cards) {
        // Simple print for debugging
        std::cout << c->Rank << " of " << c->Suit << std::endl;
    }
}

Card* Deck::Draw() {
    if (Cards.empty()) return nullptr; // Safety check
    Card* temp = Cards.back();         // Grab top card
    Cards.pop_back();                  // Remove from stack
    return temp;
}