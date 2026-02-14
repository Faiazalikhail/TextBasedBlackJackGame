#pragma once
#include "Card.h"
#include <vector>
#include <string>

// class managing a player or dealer's cards and stats
class Hand {
private:
    // tracks aces to handle soft/hard totals
    int AceCounter;

public:
    // collection of card pointers in this hand
    std::vector<Card*> Cards;
    // current calculated score
    int Score;
    // player's available money
    int Credits;
    // money wagered on this specific hand
    int Bet;
    // display name for the hand owner
    std::string Name;

    // constructor
    Hand();
    // destructor
    ~Hand();
    // adds card and updates score
    void AddCard(Card* newCard);
    // displays hand to console
    void PrintHand();
    // resets hand for new round
    void ClearHand();
};