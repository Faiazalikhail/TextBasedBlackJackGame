#include "Deck.h"
#include <algorithm> 
#include <ctime>     
#include <cstdlib>   
#include <iostream>

// generate a standard 52 card deck
Deck::Deck() {
    std::string suits[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

    // iterate through suits
    for (int s = 0; s < 4; s++) {
        // iterate through ranks
        for (int r = 0; r < 13; r++) {
            Card* c = new Card();
            c->Suit = suits[s];
            c->Rank = r + 1;
            Cards.push_back(c);
        }
    }
}

// clean up allocated memory
Deck::~Deck() {
    for (Card* c : Cards) {
        delete c;
    }
}

// randomize the deck vector
void Deck::Shuffle() {
    for (int i = 0; i < Cards.size(); i++) {
        // pick random index to swap with
        int RandomIndex = std::rand() % Cards.size();
        std::swap(Cards[i], Cards[RandomIndex]);
    }
}

// print entire deck for debugging
void Deck::PrintDeck() {
    for (Card* c : Cards) {
        std::cout << c->Rank << " of " << c->Suit << std::endl;
    }
}

// get top card from stack
Card* Deck::Draw() {
    // safety check for empty deck
    if (Cards.empty()) {
        return nullptr;
    }
    Card* temp = Cards.back();
    Cards.pop_back();
    return temp;
}