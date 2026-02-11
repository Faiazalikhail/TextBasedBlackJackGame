#pragma once
#include "GameUI.h"

void PlaceBets(std::vector<Hand>& Player) {
    for (int i = 0; i < Player.size(); i++) {

        // 1. Prepare the info for the box
        std::string playerTitle = Player[i].Name + " - Place Your Bet";
        std::string currentMoney = "Wallet: " + std::to_string(Player[i].Credits) + " Credits";

        bool validBet = false;

        // 2. Loop until they give a valid bet
        while (!validBet) {

            system("cls");          
            DisplayStats(Player);   // 2. Re-draw the Header 
            

            // Draw the dashboard
            DrawPanel({
                playerTitle,
                "--------------------------------", // A separator line
                currentMoney,
                "Enter amount to bet:"
                });

            std::cin >> Player[i].Bet;

            // 3. Logic Check
            if (Player[i].Bet > 0 && Player[i].Bet <= Player[i].Credits) {
                // Success! Deduct money and exit loop
                Player[i].Credits -= Player[i].Bet;
                validBet = true;
            }
            else {
                // Failure! Show error box
                DrawPanel({
                    "ERROR: Invalid Bet!",
                    "You cannot bet 0, negative numbers,",
                    "or more money than you have!"
                    });

                system("pause"); // Wait so they can read the error before the screen clears
            }
        }
    }
}



