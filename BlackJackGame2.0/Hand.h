#pragma once
#include "Card.h"
#include <vector>

class Hand {
private:
	int AceCounter;

public:
	std::vector<Card*> Cards;
	Hand();
	~Hand();

	void AddCard(Card* newCard);
	void PrintHand();
	void ClearHand();
	int Score;
	int Credits;
	int Bet;
	std::string Name;
};