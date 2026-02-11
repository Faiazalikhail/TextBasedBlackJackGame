#pragma once
#include <string>

class Card {
public:
    int Rank;       // 1=Ace, 11-13=Face, 2-10=Number. Holds the card's value.
    std::string Suit; // "Hearts", "Diamonds", "Clubs", "Spades". Holds the card's suit.
};