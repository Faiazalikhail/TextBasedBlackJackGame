#pragma once
#include "Card.h"
#include <vector>
#include <string>

class Hand {
private:
    int AceCounter; // Tracks number of Aces to handle soft/hard totals (1 vs 11).

public:
    std::vector<Card*> Cards; // Stores pointers to the Card objects currently in this hand.
    int Score;      // Current calculated value of the hand (e.g., 21).
    int Credits;    // Player's remaining money/balance.
    int Bet;        // Amount currently wagered in this round.
    std::string Name; // Name of the player (e.g., "Player 1", "Dealer").

    Hand();
    ~Hand();
    void AddCard(Card* newCard);
    void PrintHand();
    void ClearHand();
};