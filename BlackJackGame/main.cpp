#include "GameFunctions.h"


int main() {

	std::srand(std::time(0));

	
	std::cout << "Welcome to the Black Jack Game" << std::endl;
	std::cout << "____________________________________________________________________________________________" << std::endl;
	std::cout << "Please Enter Player 1 Name: ";
	std::cin >> Player1_Name;
	std::cout << "____________________________________________________________________________________________" << std::endl;

	std::cout << "Hello (" << Player1_Name << ") you have been alocated total amount of (" << Player1credits << ") Credits. Enjoy Playing BlackJack" << std::endl;
	std::cout << "____________________________________________________________________________________________" << std::endl;


	system("cls");
	//place bet
	int player1CurrentBet = GetBet(Player1credits);
	Player1credits = Player1credits - player1CurrentBet;
	std::cout << "Your remaining credit is : " << Player1credits << std::endl;
	
	
	std::cout << "____________________________________________________________________________________________" << std::endl;
		
	std::vector<int> ShuffledDeck = Shuffle();

	std::vector<int> DealerHand;
	std::vector<int> PlayerHand;

	// first round
	std::cout << "Dealing First round" << std::endl;
	std::cout << "____________________________________________________________________________________________" << std::endl;

	for (int i = 0; i < 2; i++) {
		int card1 = ShuffledDeck.back();
		PlayerHand.push_back(card1);
		ShuffledDeck.pop_back();

		int card2 = ShuffledDeck.back();
		DealerHand.push_back(card2);
		ShuffledDeck.pop_back();
	}

	//Player Hand Show
		std::cout << std::endl << std::endl;
		std::cout << "____________________________________________________________________________________________" << std::endl;
		std::cout << "Player Hand" << std::endl << std::endl;
	for (int i = 0; i < PlayerHand.size(); i++) {

		int player = PlayerHand[i];	
		std::cout << GetCardName(suits[player / 13], ranks[player % 13]) << "      |      ";		
	}
	
	
	// Dealer Hand
	std::cout << std::endl << std::endl;
	std::cout << "____________________________________________________________________________________________" << std::endl;
		std::cout << "Dealer hand:" << std::endl << std::endl;
	for (int i = 0; i < 2; i++) {

		int Dealer = DealerHand[i];
		
		if (i == 0) {
			std::cout << GetCardName(suits[Dealer / 13], ranks[Dealer % 13]) << "      |      ";
		}
		else {
			std::cout << "[ XXXXXXXXXXX ]" << std::endl;
		}		
		
	}


	std::cout << std::endl << std::endl;
	std::cout << std::endl << std::endl;



	std::cout << std::endl << std::endl;
	std::cout << "____________________________________________________________________________________________" << std::endl;

	char PlayerChoice;
	bool IsPlayerTurn = true;
	
	while(IsPlayerTurn) {
		
		int CurrentScore = GetHandValue(PlayerHand);
		std::cout << "Your current score is: " << CurrentScore << std::endl;
		std::cout << std::endl << std::endl;
		if (CurrentScore > 21) {
			std::cout << "You BUSTED! (Score: " << CurrentScore << ")" << std::endl;
			IsPlayerTurn = false;
			break;
		}
		std::cout << "Action? (H)it, (S)tand, (D)ouble: ";
		std::cin >> PlayerChoice;

		if (PlayerChoice == 'h' || PlayerChoice == 'H') {
			std::cout << "--- HIT ---" << std::endl;
			int card1 = ShuffledDeck.back();
			PlayerHand.push_back(card1);
			ShuffledDeck.pop_back();
		}
		else if (PlayerChoice == 's' || PlayerChoice == 'S') {
			std::cout << "--- STAND ---" << std::endl;
			IsPlayerTurn = false;
		}
		else if (PlayerChoice == 'd' || PlayerChoice == 'D') {
			Player1credits = Player1credits - player1CurrentBet;
			player1CurrentBet = player1CurrentBet * 2;
			std::cout << "You Have Succesfully Doubled your bet and your total bet is (" << player1CurrentBet << ")" << std::endl;
			std::cout << "Your remaining credit is : " << Player1credits << std::endl;
			int card1 = ShuffledDeck.back();
			PlayerHand.push_back(card1);
			ShuffledDeck.pop_back();

			std::cout << std::endl << std::endl;
			std::cout << "____________________________________________________________________________________________" << std::endl;
			std::cout << "Player Hand" << std::endl << std::endl;
			for (int i = 0; i < 3; i++) {

				int player = PlayerHand[i];
				std::cout << GetCardName(suits[player / 13], ranks[player % 13]) << "      |      ";
			}

			IsPlayerTurn = false;
			break;
			
		}else{
			std::cout << "Invalid input, try again." << std::endl;
		}
	}



	return 0;
}



/*for (int i = 0; i <= 51; i++) {
	int card2 = ShuffledDeck[i];
	std::cout << GetCardName(suits[card2 / 13], ranks[card2 % 13]) << " = " << GetCardValue(ranks[card2 % 13]) << std::endl;
}*/