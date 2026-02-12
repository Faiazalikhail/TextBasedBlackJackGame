#pragma once
#include "GameUI.h"
#include "Hand.h"
#include <vector>
#include <iostream>
#include <string>

void PlaceBets(std::vector<Hand>& Player) {
    for (int i = 0; i < Player.size(); i++) {
        std::string title = Player[i].Name + " - Place Your Bet";
        std::string money = "Wallet: " + std::to_string(Player[i].Credits) + " Credits";
        bool validBet = false; 

        while (!validBet) {
            system("cls");
            DisplayStats(Player);
            DrawPanel({ title, "--------------------------------", money, "Enter amount to bet:" });

            std::cin >> Player[i].Bet;

            if (Player[i].Bet > 0 && Player[i].Bet <= Player[i].Credits) {
                Player[i].Credits -= Player[i].Bet; 
                validBet = true;
            }
            else {
                DrawPanel({ "ERROR: Invalid Bet!", "Cannot bet 0, negative,", "or more than you have!" });
                system("pause");
            }
        }
    }
}

void PlayTurn(std::vector<Hand>& Player, Hand& Dealer, int PlayerIndex, Deck* GameDeck) {

    bool TurnOver = false;

    std::string AllActions[5] = { "[H]IT", "[S]TAND", "[D]OUBLE DOWN", "S[P]LIT", "P[A]SS (Surrender)" };

    
    char PlayerCall;
    
    while (!TurnOver && Player[PlayerIndex].Score <= 21) {
        
        // --- Visualization Phase ---
        system("cls");
        DisplayStats(Player);
        DrawGameTable(Player, Dealer, true); // Show table, Hide Dealer's 1st card
        std::cout << "  (Press 'Enter' to continue...)" << std::endl;
        std::cin.ignore(); std::cin.get();


        // --- Calls Validation ---
        if (Player[PlayerIndex].Cards.size() == 2 && Player[PlayerIndex].Cards[0]->Rank == Player[PlayerIndex].Cards[1]->Rank && Player[PlayerIndex].Credits >= Player[PlayerIndex].Bet) {
            DrawPanel({ Player[PlayerIndex].Name + "'s Turn", "Available Calls: ", "           (H)IT, (S)TAND, (D)OUBLE DOWN, S(P)LIT, P(A)SS (Surrender)" , "_________________________________", "Please enter your Call" });
            std::cin >> PlayerCall;
            while (PlayerCall != 'h' && PlayerCall != 'H' && PlayerCall != 's' && PlayerCall != 'S' && PlayerCall != 'd' && PlayerCall != 'D' && PlayerCall != 'P' && PlayerCall != 'p' && PlayerCall != 'a' && PlayerCall != 'A') {
                DrawPanel({ Player[PlayerIndex].Name + "'s Turn", "ERROR: Please Enter your Call accordingly", "Available Calls: ", "           (H)IT, (S)TAND, (D)OUBLE DOWN, S(P)LIT, P(A)SS (Surrender)" , "_________________________________", "Please enter your Call" });
                std::cin >> PlayerCall;
            }
        }
        else if (Player[PlayerIndex].Credits >= Player[PlayerIndex].Bet) {
            DrawPanel({ Player[PlayerIndex].Name + "'s Turn", "Available Calls: ", "           (H)IT, (S)TAND, (D)OUBLE DOWN, P(A)SS (Surrender)" , "_________________________________", "Please enter your Call" });
            std::cin >> PlayerCall;
            while (PlayerCall != 'h' && PlayerCall != 'H' && PlayerCall != 's' && PlayerCall != 'S' && PlayerCall != 'd' && PlayerCall != 'D' && PlayerCall != 'a' && PlayerCall != 'A') {
                DrawPanel({ Player[PlayerIndex].Name + "'s Turn", "ERROR: Please Enter your Call accordingly", "Available Calls: ", "           (H)IT, (S)TAND, (D)OUBLE DOWN, P(A)SS (Surrender)" , "_________________________________", "Please enter your Call" });
                std::cin >> PlayerCall;
            }
        }
        else {
            DrawPanel({ Player[PlayerIndex].Name + "'s Turn", "Available Calls: ", "           (H)IT, (S)TAND, P(A)SS (Surrender)" , "_________________________________", "Please enter your Call" });
            std::cin >> PlayerCall;
            while (PlayerCall != 'h' && PlayerCall != 'H' && PlayerCall != 's' && PlayerCall != 'S' && PlayerCall != 'a' && PlayerCall != 'A') {
                DrawPanel({ Player[PlayerIndex].Name + "'s Turn", "ERROR: Please Enter your Call accordingly", "Available Calls: ", "           (H)IT, (S)TAND, P(A)SS (Surrender)" , "_________________________________", "Please enter your Call" });
                std::cin >> PlayerCall;
            }
        }

        // --- Split Execution ---
        if (PlayerCall == 'P' || PlayerCall == 'p') {
            int Wager = Player[PlayerIndex].Bet;
            Card* C1 = Player[PlayerIndex].Cards[0];
            Card* C2 = Player[PlayerIndex].Cards[1];
            std::string SName = Player[PlayerIndex].Name + " (Split)";

            Player[PlayerIndex].Credits -= Wager;
            Player.push_back(Hand());

            // Re-acquiring references here because push_back can move vector memory.
            Hand& Current = Player[PlayerIndex];
            Hand& Split = Player.back();

            Split.Name = SName; Split.Bet = Wager;
            Split.AddCard(C2);

            Current.ClearHand();
            Current.Bet = Wager;
            Current.AddCard(C1);

        // --- Double Down Execution ---
        }else if (PlayerCall == 'd' || PlayerCall == 'D') {
            Player[PlayerIndex].Credits -= Player[PlayerIndex].Bet;
            Player[PlayerIndex].Bet += Player[PlayerIndex].Bet;
            Player[PlayerIndex].AddCard(GameDeck->Draw());
            TurnOver = true;
        // --- Hit Execution ---
        }else if (PlayerCall == 'H' || PlayerCall == 'h') {
            Player[PlayerIndex].AddCard(GameDeck->Draw());
        // --- Stand Execution ---
        }else if (PlayerCall == 'S' || PlayerCall == 's') {
            TurnOver = true;
        // --- Pass Execution ---
        }else if (PlayerCall == 'a' || PlayerCall == 'A') {
            Player[PlayerIndex].Credits += Player[PlayerIndex].Bet / 2;
            TurnOver = true;
        }
    }
}