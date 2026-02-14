#pragma once
#include <string>

// class representing a single playing card
class Card {
public:
    // holds the card's value (1-13)
    int Rank;
    // holds the card's suit text
    std::string Suit;
};