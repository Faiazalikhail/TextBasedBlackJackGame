#include <iostream>
#include <vector>
#include <ctime>
#include "Deck.h"
#include "Hand.h"
#include "GameUI.h"
#include "GameFunctions.h"

int NumberOfPlayers;

int main() {
	std::srand(std::time(0));



	
	DrawPanel({ "Welcome to the Black Jack Game", "How many players? (1-3)" });
	std::cin >> NumberOfPlayers;

	system("cls");
	
	
	while (NumberOfPlayers < 1 || NumberOfPlayers > 3) {
		system("cls");
		DrawPanel({
			"ERROR: Invalid Number of Players!",
			"Please enter a number between 1 and 3."
			});

		std::cin >> NumberOfPlayers;
	}
	system("cls");


	std::vector<Hand> Player(NumberOfPlayers);
	Hand Dealer;

	// Ask for Names
	for (int i = 0; i < NumberOfPlayers; i++) {
		// Use your DrawPanel for a nice prompt!
		DrawPanel({
			"Registration for Player " + std::to_string(i + 1),
			"Please enter your name:"
			});

		std::cin >> Player[i].Name;
	}

	// Set Dealer Name too
	Dealer.Name = "Dealer";

	// Create New Deck and Shuffle it
	Deck* GameDeck = new Deck();
	GameDeck->Shuffle();


	while (true) {

		system("cls");
		DisplayStats(Player);

		//check the cards in deck



		//Keeps Player Credits in check
		if (Player.size() <= 0) {
			DrawPanel({ "Game Over" });
			std::cout << "  (Press 'Enter' to continue...)" << std::endl;
			std::cin.ignore(); // Clears buffer
			std::cin.get();    // Waits for Enter
			break;
		}
		else {
			for (int i = 0; i < Player.size(); i++) {

				if (Player[i].Credits <= 0) {
				
					DrawPanel({ "Total Credit of  " + Player[i].Name + " reached 0, and the player has left the table" });
					std::cout << "  (Press 'Enter' to continue...)" << std::endl;
					std::cin.ignore(); // Clears buffer
					std::cin.get();    // Waits for Enter

					Player.erase(Player.begin() + i);
					i -= 1;
				}
			}

			if (Player.size() <= 0) {
				continue;
			}

		}

		//round starts
		system("cls");
		DisplayStats(Player);



		PlaceBets(Player);

		system("cls");
		DisplayStats(Player);
		
		for (int d = 0; d < 2; d++) { //this loop will make sure every player recieve one card at a time. 
			for (int i = 0; i < Player.size(); i++) { // this loop will draw for each player
				Player[i].AddCard(GameDeck->Draw());

			}

			Dealer.AddCard(GameDeck->Draw());
		}


		// ==========================================
		// 3. VISUALIZATION PHASE
		// ==========================================

		// Clear the screen so we don't see the betting history anymore
		system("cls");

		// Draw the Header (Credits/Names)
		DisplayStats(Player);

		// Draw the Table (Cards side-by-side)
		// We pass 'true' because the round just started, so Dealer hides one card.
		DrawGameTable(Player, Dealer, true);

		// Pause so the human can actually see the cards!
		std::cout << "  (Press 'Enter' to collect cards...)" << std::endl;
		std::cin.ignore(); // Clears buffer
		std::cin.get();    // Waits for Enter



		//only for memory managment purposes.
			for (int i = 0; i < Player.size(); i++) {

				Player[i].ClearHand();
			}
			Dealer.ClearHand();

		char PlayerChoise;
		bool NextRound = false;
		while (NextRound == false) {
			DrawPanel({ "Do you want to start next round?", "Enter Y or N" });
			std::cin >> PlayerChoise;
			if (PlayerChoise == 'y' || PlayerChoise == 'Y') {
				NextRound = true;
			}
			else {
				break;

			}

		}

	}




	delete GameDeck;
	std::cout << "  (Game has been Closed Succesfully Press Enter to exit)" << std::endl;
	std::cin.ignore(); // Clears buffer
	std::cin.get();    // Waits for Enter
	return 0;
}