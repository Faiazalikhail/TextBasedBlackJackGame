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

void PlayTurn(std::vector<Hand>& Player, int PlayerIndex, Deck* GameDeck) {

    
    // --- Split Execution ---
    if (Player[PlayerIndex].Cards.size() == 2 && Player[PlayerIndex].Cards[0]->Rank == Player[PlayerIndex].Cards[1]->Rank && Player[PlayerIndex].Credits >= Player[PlayerIndex].Bet) {
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

    }


    // --- Double Down Execution ---


    // --- Hit Execution ---

    // --- Stand Execution ---

    // --- Pass Execution ---

}