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
        bool validBet = false; // Controls the betting loop until input is valid

        while (!validBet) {
            system("cls");
            DisplayStats(Player);
            DrawPanel({ title, "--------------------------------", money, "Enter amount to bet:" });

            std::cin >> Player[i].Bet;

            if (Player[i].Bet > 0 && Player[i].Bet <= Player[i].Credits) {
                Player[i].Credits -= Player[i].Bet; // Deduct bet from wallet
                validBet = true;
            }
            else {
                DrawPanel({ "ERROR: Invalid Bet!", "Cannot bet 0, negative,", "or more than you have!" });
                system("pause");
            }
        }
    }
}