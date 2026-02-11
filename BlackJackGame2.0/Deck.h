#pragma once
#include "Card.h"
#include <vector>

class Deck {
private:
	std::vector<Card*> Cards;

public:
	Deck();
	~Deck();
	Card* Draw();

	void Shuffle();
	void PrintDeck();
};