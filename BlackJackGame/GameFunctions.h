#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

int Player1credits = 1000;
std::string Player1_Name;

std::string suits[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
int ranks[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1 };

std::string CardName;



std::vector<int> CreateDeck() {
	std::vector<int> NewDeck;
	for (int i = 0; i <= 51; i++) {
		NewDeck.push_back(i);
	}

	return NewDeck;
}

std::vector<int> Shuffle() {
	std::vector<int> ShuffledDeck = CreateDeck();

	for (int i = 0; i < 52; i++) {
		int RandomIndex = std::rand() % 52;
		std::swap(ShuffledDeck[i], ShuffledDeck[RandomIndex]);
	}

	return ShuffledDeck;
}

int GetCardValue(int rank) {
	if (rank == 1) {
		return 11;
	}
	else if (rank == 11 || rank == 12 || rank == 13) {
		return 10;
	}
	else {
		return rank;
	}
}




std::string GetCardName(std::string suits, int ranks) {

	std::string CardFace;

	if (ranks == 11) {
		CardFace = "Jack";
	}
	else if (ranks == 12) {
		CardFace = "Queen";
	}
	else if (ranks == 13) {
		CardFace = "King";
	}
	else if (ranks == 1) {
		CardFace = "Ace";
	}
	else {
		CardFace = std::to_string(ranks);
	}

	CardName = "[ " + CardFace + " of " + suits + " ]";

	return CardName;
}

int GetBet(int Credits) {
	int bet;

	do {
		std::cout << "Hello Place your Bet to start the round: ";
		std::cin >> bet;

		if (bet > 0 && bet <= Credits) {
			std::cout << "You Have Succesfully Placed a bet of (" << bet << ")" << std::endl;
			return bet;
		}
		else {
			std::cout << "Insuffecit credits, your remaining credit is: " << Credits << std::endl;
		}

	} while (bet <= 0 || bet > Credits);
}


int GetHandValue(std::vector<int> Hand) {

	int HandValue = 0;
	int AceCount = 0;

	for (int i = 0; i < Hand.size(); i++) {
		HandValue = GetCardValue(ranks[Hand[i] % 13]) + HandValue;
		if (Hand[i] % 13 == 12) {
			AceCount = AceCount + 1;
		}
	}

	while (HandValue > 21 && AceCount > 0) {
		HandValue = HandValue - 10;
		AceCount = AceCount - 1;
	}

	return HandValue;

}