#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Deck.h"
#include "Hand.h"
#include "GameUI.h"
#include "GameFunctions.h" 

// total number of players at table
int NumberOfPlayers;

int main() {
    // seed random generator
    std::srand((unsigned int)std::time(0));

    // get player count
    DrawPanel({ "Welcome to the Black Jack Game", "How many players? (1-2)" });
    std::cin >> NumberOfPlayers;
    system("cls");

    // validate player count
    while (NumberOfPlayers < 1 || NumberOfPlayers > 2) {
        system("cls");
        DrawPanel({ "ERROR: Invalid Number of Players!", "Please enter a number between 1 and 2." });
        std::cin >> NumberOfPlayers;
    }
    system("cls");

    // initialize players and dealer
    std::vector<Hand> Player(NumberOfPlayers);
    Hand Dealer;
    Dealer.Name = "Dealer";

    // --- Name Registration ---
    for (int i = 0; i < NumberOfPlayers; i++) {
        DrawPanel({ "Registration for Player " + std::to_string(i + 1), "Please enter your name:" });
        std::cin >> Player[i].Name;
    }

    // initialize deck
    Deck* GameDeck = new Deck();
    GameDeck->Shuffle();

    // ================== MAIN GAME LOOP ==================
    while (true) {
        system("cls");
        DisplayStats(Player);

        // --- Bankruptcy Check ---
        if (Player.size() <= 0) {
            DrawPanel({ "Game Over", "No players left at the table." });
            break;
        }

        // remove broke players
        for (int i = 0; i < Player.size(); i++) {
            // check credits (ignoring splits)
            if (Player[i].Name.find("(Split)") == std::string::npos && Player[i].Credits <= 0) {
                DrawPanel({ "Total Credit of " + Player[i].Name + " reached 0. Player leaves table." });
                system("pause");
                Player.erase(Player.begin() + i);
                i--;
            }
        }

        // exit if table empty
        if (Player.size() <= 0) break;

        // --- Deck Check ---
        if (GameDeck->GetRemainingCards() < 20) {
            GameDeck->Shuffle();
            DrawPanel({ "Deck reshuffled before new round!" });
            system("pause");
        }

        // --- Start Round & Bets ---
        system("cls");
        DisplayStats(Player);
        PlaceBets(Player);

        system("cls");
        DisplayStats(Player);

        // --- Dealing Phase ---
        for (int d = 0; d < 2; d++) {
            for (int i = 0; i < Player.size(); i++) {
                Player[i].AddCard(GameDeck->Draw());
            }
            Dealer.AddCard(GameDeck->Draw());
        }

        // --- Visualization (Initial Deal) ---
        system("cls");
        DisplayStats(Player);
        DrawGameTable(Player, Dealer, true);
        std::cout << "  (Press 'Enter' to start turns...)" << std::endl;
        std::cin.ignore();
        std::cin.get();

        // --- Calls Phase (Player Turns) ---
        for (int i = 0; i < Player.size(); i++) {
            PlayTurn(Player, Dealer, i, GameDeck);
        }

        // --- Dealer Play Phase ---

        // reveal hidden card
        system("cls");
        DisplayStats(Player);
        DrawGameTable(Player, Dealer, false);
        std::cout << "  Dealer reveals hidden card. (Press 'Enter' to continue...)" << std::endl;
        std::cin.get();

        // dealer hits until 17
        while (Dealer.Score < 17) {
            Dealer.AddCard(GameDeck->Draw());

            system("cls");
            DisplayStats(Player);
            DrawGameTable(Player, Dealer, false);

            std::cout << "  Dealer hits... (Press 'Enter' to continue)" << std::endl;
            std::cin.get();
        }

        std::cout << "  (Round Over. Press 'Enter' to see results...)" << std::endl;
        std::cin.get();

        // --- Rewarding System ---
        std::vector<std::string> results;
        results.push_back("ROUND RESULTS");
        results.push_back("-------------------------------------------");

        for (int i = 0; i < Player.size(); i++) {
            std::string resultText = Player[i].Name + ": ";
            int betAmount = Player[i].Bet;
            int winnings = 0;

            // check bust
            if (Player[i].Score > 21) {
                resultText += "BUST! (Lost -$" + std::to_string(betAmount) + ")";
            }
            // check dealer bust
            else if (Dealer.Score > 21) {
                winnings = betAmount * 2;
                Player[i].Credits += winnings;
                resultText += "WIN! (Dealer Bust) -> Added +$" + std::to_string(winnings);
            }
            else {
                // compare scores
                if (Player[i].Score > Dealer.Score) {
                    winnings = betAmount * 2;
                    Player[i].Credits += winnings;
                    resultText += "WIN! (" + std::to_string(Player[i].Score) + " vs " + std::to_string(Dealer.Score) + ") -> Added +$" + std::to_string(winnings);
                }
                else if (Player[i].Score == Dealer.Score) {
                    winnings = betAmount;
                    Player[i].Credits += winnings;
                    resultText += "PUSH (Money Back) -> Returned +$" + std::to_string(winnings);
                }
                else {
                    resultText += "LOST (" + std::to_string(Player[i].Score) + " vs " + std::to_string(Dealer.Score) + ") -> Lost -$" + std::to_string(betAmount);
                }
            }
            results.push_back(resultText);
        }

        system("cls");
        DisplayStats(Player);
        DrawGameTable(Player, Dealer, false);
        DrawPanel(results);

        std::cout << "  (Press 'Enter' to clean up...)" << std::endl;
        std::cin.get();

        // --- MERGE SPLIT HANDS & CLEANUP ---
        for (int i = Player.size() - 1; i >= 0; i--) {
            // find split hands
            if (Player[i].Name.find("(Split)") != std::string::npos) {
                if (i > 0) {
                    // return money to parent
                    Player[i - 1].Credits += Player[i].Credits;
                }
                // delete split hand
                Player.erase(Player.begin() + i);
            }
            else {
                // reset main hand
                Player[i].ClearHand();
            }
        }
        Dealer.ClearHand();

        // --- Next Round Prompt ---
        char PlayerChoice;
        bool ValidInput = false;
        bool QuitGame = false;

        // input loop
        while (!ValidInput) {
            DrawPanel({ "Do you want to start next round?", "Enter [Y]es or [N]o" });
            std::cin >> PlayerChoice;

            if (PlayerChoice == 'y' || PlayerChoice == 'Y') {
                ValidInput = true;
            }
            else if (PlayerChoice == 'n' || PlayerChoice == 'N') {
                ValidInput = true;
                QuitGame = true;
            }
        }

        if (QuitGame) break;
    }

    // free memory
    delete GameDeck;
    system("cls");
    DrawPanel({ "Thanks for playing TFS High Stakes Blackjack!", "See you next time!" });
    std::cout << "  (Press 'Enter' to exit)" << std::endl;
    std::cin.ignore();
    std::cin.get();
    return 0;
}