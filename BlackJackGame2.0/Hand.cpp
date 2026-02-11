#include "Hand.h"
#include <iostream>

Hand::Hand() { Score = 0; AceCounter = 0; Credits = 1000; Bet = 0; } // Initialize defaults

Hand::~Hand() { for (Card* c : Cards) delete c; } // Clean up memory for any cards left

void Hand::AddCard(Card* newCard) {
    Cards.push_back(newCard);

    // --- Score Calculation ---
    if (newCard->Rank == 1) { AceCounter++; Score += 11; }      // Ace defaults to 11
    else if (newCard->Rank >= 11) { Score += 10; }              // Face cards are 10
    else { Score += newCard->Rank; }                            // Number cards are face value

    // --- Ace Adjustment ---
    while (Score > 21 && AceCounter > 0) { Score -= 10; AceCounter--; } // Demote Ace 11->1
}

void Hand::PrintHand() {
    for (Card* c : Cards) {
        std::string name;
        if (c->Rank == 1) name = "Ace";
        else if (c->Rank == 11) name = "Jack";
        else if (c->Rank == 12) name = "Queen";
        else if (c->Rank == 13) name = "King";
        else name = std::to_string(c->Rank);
        std::cout << name << " of " << c->Suit << std::endl;
    }
    std::cout << "Hand Total: " << Score << std::endl;
}

void Hand::ClearHand() { Bet = 0; Score = 0; AceCounter = 0; Cards.clear(); } // Reset round stats