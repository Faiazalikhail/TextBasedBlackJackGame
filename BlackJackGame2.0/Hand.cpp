#include "Hand.h"
#include <iostream>

Hand::Hand() {
    Score = 0;
    AceCounter = 0;
    Credits = 1000;
    Bet = 0;
}

Hand::~Hand() {
    for (int i = 0; i < Cards.size(); i++) {
        delete Cards[i];
    }
}

void Hand::AddCard(Card* newCard) {
    Cards.push_back(newCard);
    if (newCard->Rank == 1) {
        AceCounter++;
        Score += 11;
    }
    else if (newCard->Rank == 11 || newCard->Rank == 12 || newCard->Rank == 13) {
        Score += 10;
    }
    else {
        Score += newCard->Rank;
    }

    while(Score > 21 && AceCounter > 0) {
        Score -= 10;
        AceCounter--;
    }
}

void Hand::PrintHand() {
    for (int i = 0; i < Cards.size(); i++) {
        if (Cards[i]->Rank == 1) {
            std::cout << "Ace" << " of " << Cards[i]->Suit << std::endl;
        }
        else if (Cards[i]->Rank == 11) {
            std::cout << "Jack" << " of " << Cards[i]->Suit << std::endl;
        }
        else if (Cards[i]->Rank == 12) {
            std::cout << "Queen" << " of " << Cards[i]->Suit << std::endl;
        }
        else if (Cards[i]->Rank == 13) {
            std::cout << "King" << " of " << Cards[i]->Suit << std::endl;
        }
        else {
            std::cout << Cards[i]->Rank << " of " << Cards[i]->Suit << std::endl;
        }
    }

    std::cout << "Hand Total: " << Score << std::endl;
}

void Hand::ClearHand() {
    this->Bet = 0;
    this->Score = 0;
    this->AceCounter = 0;
    this->Cards.clear();
}