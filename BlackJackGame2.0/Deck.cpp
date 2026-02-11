#include "Deck.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>

Deck::Deck() {
	std::string suits[4] = { "Hearts" , "Diamonds", "Clubs", "Spades" };
	for (int s = 0; s < 4; s++) {
		for (int r = 0; r < 13; r++) {

			Card* c = new Card();

			c->Suit = suits[s];
			c->Rank = r + 1;

			Cards.push_back(c);

		}
	}
}

Deck::~Deck() {
	for (int i = 0; i < Cards.size(); i++) {
		delete Cards[i];
	}
	
}

void Deck::Shuffle() {

	for (int i = 0; i < Cards.size(); i++) {
		int RandomIndex = std::rand() % Cards.size();

		std::swap(Cards[i], Cards[RandomIndex]);
	}

}

void Deck::PrintDeck() {
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

}

Card* Deck::Draw() {
	Card* temp = Cards.back();
	Cards.pop_back();
	
	return temp;
}