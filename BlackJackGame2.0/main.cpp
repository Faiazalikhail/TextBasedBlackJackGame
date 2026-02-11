#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Deck.h"
#include "Hand.h"
#include "GameUI.h"
#include "GameFunctions.h"

int NumberOfPlayers; // Tracks total players (1-3) at the table

int main() {
    std::srand((unsigned int)std::time(0)); // Seed random number generator

    DrawPanel({ "Welcome to the Black Jack Game", "How many players? (1-3)" });
    std::cin >> NumberOfPlayers;
    system("cls");

    // --- Input Validation ---
    while (NumberOfPlayers < 1 || NumberOfPlayers > 3) {
        system("cls");
        DrawPanel({ "ERROR: Invalid Number of Players!", "Please enter a number between 1 and 3." });
        std::cin >> NumberOfPlayers;
    }
    system("cls");

    std::vector<Hand> Player(NumberOfPlayers); // Array of Player objects
    Hand Dealer;                               // Single Dealer object
    Dealer.Name = "Dealer";

    // --- Name Registration ---
    for (int i = 0; i < NumberOfPlayers; i++) {
        DrawPanel({ "Registration for Player " + std::to_string(i + 1), "Please enter your name:" });
        std::cin >> Player[i].Name;
    }

    Deck* GameDeck = new Deck(); // Create and allocate new deck
    GameDeck->Shuffle();

    // ================== MAIN GAME LOOP ==================
    while (true) {
        system("cls");
        DisplayStats(Player);

        // TODO: check the cards in deck

        // --- Bankruptcy Check ---
        if (Player.size() <= 0) {
            DrawPanel({ "Game Over" });
            std::cout << "  (Press 'Enter' to continue...)" << std::endl;
            std::cin.ignore(); std::cin.get();
            break; // Exit Main Loop
        }
        else {
            // Loop backwards to safely erase players while iterating
            for (int i = 0; i < Player.size(); i++) {
                if (Player[i].Credits <= 0) {
                    DrawPanel({ "Total Credit of " + Player[i].Name + " reached 0. Player leaves table." });
                    std::cout << "  (Press 'Enter' to continue...)" << std::endl;
                    std::cin.ignore(); std::cin.get();

                    Player.erase(Player.begin() + i); // Remove player
                    i -= 1; // Adjust index after erase
                }
            }
            if (Player.size() <= 0) continue; // Restart loop if everyone is gone
        }

        // --- Start Round ---
        system("cls");
        DisplayStats(Player);
        PlaceBets(Player);

        system("cls");
        DisplayStats(Player);

        // --- Dealing Phase ---
        for (int d = 0; d < 2; d++) {
            for (int i = 0; i < Player.size(); i++) Player[i].AddCard(GameDeck->Draw());
            Dealer.AddCard(GameDeck->Draw());
        }

        // --- Visualization Phase ---
        system("cls");
        DisplayStats(Player);
        DrawGameTable(Player, Dealer, true); // Show table, Hide Dealer's 1st card
        std::cout << "  (Press 'Enter' to collect cards...)" << std::endl;
        std::cin.ignore(); std::cin.get();

        // --- Reset / Cleanup ---
        for (int i = 0; i < Player.size(); i++) Player[i].ClearHand();
        Dealer.ClearHand();

        // --- Next Round Prompt ---
        char PlayerChoice; // Stores 'Y' or 'N'
        bool NextRound = false;
        while (!NextRound) {
            DrawPanel({ "Do you want to start next round?", "Enter Y or N" });
            std::cin >> PlayerChoice;
            if (PlayerChoice == 'y' || PlayerChoice == 'Y') NextRound = true;
            else break; // Logic here might need review (currently breaks prompt loop, not game loop)
        }
    }

    delete GameDeck; // Clean up Heap memory
    std::cout << "  (Game has been Closed Successfully. Press Enter to exit)" << std::endl;
    std::cin.ignore(); std::cin.get();
    return 0;
}