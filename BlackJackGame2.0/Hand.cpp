#include "Hand.h"
#include <iostream>

// initialize default values for a new hand
Hand::Hand() {
    Score = 0;
    AceCounter = 0;
    Credits = 1000;
    Bet = 0;
}

// clear card references without deleting memory
Hand::~Hand() {
    Cards.clear();
}

// add card to hand and recalculate score
void Hand::AddCard(Card* newCard) {
    Cards.push_back(newCard);

    // calculate basic score based on rank
    if (newCard->Rank == 1) {
        AceCounter++;
        Score += 11;
    }
    else if (newCard->Rank >= 11) {
        Score += 10;
    }
    else {
        Score += newCard->Rank;
    }

    // adjust score if busted and aces are present
    while (Score > 21 && AceCounter > 0) {
        Score -= 10;
        AceCounter--;
    }
}

// print all cards in the hand
void Hand::PrintHand() {
    for (Card* c : Cards) {
        std::string name;

        // determine rank name
        if (c->Rank == 1) {
            name = "Ace";
        }
        else if (c->Rank == 11) {
            name = "Jack";
        }
        else if (c->Rank == 12) {
            name = "Queen";
        }
        else if (c->Rank == 13) {
            name = "King";
        }
        else {
            name = std::to_string(c->Rank);
        }
        std::cout << name << " of " << c->Suit << std::endl;
    }
    std::cout << "Hand Total: " << Score << std::endl;
}

// reset variables for next round
void Hand::ClearHand() {
    Bet = 0;
    Score = 0;
    AceCounter = 0;
    Cards.clear();
}