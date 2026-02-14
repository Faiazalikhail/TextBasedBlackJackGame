#pragma once
#include "GameUI.h"
#include "Hand.h"
#include <vector>
#include <iostream>
#include <string>

// helper to get card values (face cards are 10)
int GetCardValue(Card* c) {
    if (c->Rank > 10) {
        return 10;
    }
    return c->Rank;
}

// betting phase logic
void PlaceBets(std::vector<Hand>& Player) {
    for (int i = 0; i < Player.size(); i++) {
        std::string title = Player[i].Name + " - Place Your Bet";
        std::string money = "Wallet: " + std::to_string(Player[i].Credits) + " Credits";
        // flag for input loop
        bool validBet = false;

        // validation loop
        while (!validBet) {
            system("cls");
            DisplayStats(Player);
            DrawPanel({ title, "--------------------------------", money, "Enter amount to bet:" });

            std::cin >> Player[i].Bet;

            // check bounds
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

// turn logic for a single hand
void PlayTurn(std::vector<Hand>& Player, Hand& Dealer, int PlayerIndex, Deck* GameDeck) {
    // flag to exit turn loop
    bool TurnOver = false;
    // stores user input char
    char PlayerCall;

    // index tracking the parent hand holding the credits
    int WalletIndex = PlayerIndex;

    // find wallet owner if this is a split hand
    while (Player[WalletIndex].Name.find("(Split)") != std::string::npos && WalletIndex > 0) {
        WalletIndex--;
    }

    // main turn loop
    while (!TurnOver && Player[PlayerIndex].Score <= 21) {

        // check deck level
        if (GameDeck->GetRemainingCards() < 20) {
            GameDeck->Shuffle();
            DrawPanel({ "The Deck has been reshuffled!" });
            system("pause");
        }

        // --- Visualization Phase ---
        system("cls");
        DisplayStats(Player);
        DrawGameTable(Player, Dealer, true);

        std::cout << "  (Press 'Enter' to make a call...)" << std::endl;
        std::cin.ignore();
        std::cin.get();

        // --- Calls Validation ---

        // check split availability
        if (Player[PlayerIndex].Cards.size() == 2 &&
            GetCardValue(Player[PlayerIndex].Cards[0]) == GetCardValue(Player[PlayerIndex].Cards[1]) &&
            Player[WalletIndex].Credits >= Player[PlayerIndex].Bet) {

            DrawPanel({ Player[PlayerIndex].Name + "'s Turn", "Available Calls: ", "           (H)IT, (S)TAND, (D)OUBLE DOWN, S(P)LIT, P(A)SS (Surrender)" , "_________________________________", "Please enter your Call" });
            std::cin >> PlayerCall;

            // validate input
            while (PlayerCall != 'h' && PlayerCall != 'H' && PlayerCall != 's' && PlayerCall != 'S' &&
                PlayerCall != 'd' && PlayerCall != 'D' && PlayerCall != 'P' && PlayerCall != 'p' &&
                PlayerCall != 'a' && PlayerCall != 'A') {
                DrawPanel({ Player[PlayerIndex].Name + "'s Turn", "ERROR: Please Enter your Call accordingly", "Available Calls: ", "           (H)IT, (S)TAND, (D)OUBLE DOWN, S(P)LIT, P(A)SS (Surrender)" , "_________________________________", "Please enter your Call" });
                std::cin >> PlayerCall;
            }
        }
        // check double down availability
        else if (Player[WalletIndex].Credits >= Player[PlayerIndex].Bet) {
            DrawPanel({ Player[PlayerIndex].Name + "'s Turn", "Available Calls: ", "           (H)IT, (S)TAND, (D)OUBLE DOWN, P(A)SS (Surrender)" , "_________________________________", "Please enter your Call" });
            std::cin >> PlayerCall;

            // validate input
            while (PlayerCall != 'h' && PlayerCall != 'H' && PlayerCall != 's' && PlayerCall != 'S' &&
                PlayerCall != 'd' && PlayerCall != 'D' && PlayerCall != 'a' && PlayerCall != 'A') {
                DrawPanel({ Player[PlayerIndex].Name + "'s Turn", "ERROR: Please Enter your Call accordingly", "Available Calls: ", "           (H)IT, (S)TAND, (D)OUBLE DOWN, P(A)SS (Surrender)" , "_________________________________", "Please enter your Call" });
                std::cin >> PlayerCall;
            }
        }
        // standard hit/stand
        else {
            DrawPanel({ Player[PlayerIndex].Name + "'s Turn", "Available Calls: ", "           (H)IT, (S)TAND, P(A)SS (Surrender)" , "_________________________________", "Please enter your Call" });
            std::cin >> PlayerCall;

            // validate input
            while (PlayerCall != 'h' && PlayerCall != 'H' && PlayerCall != 's' && PlayerCall != 'S' &&
                PlayerCall != 'a' && PlayerCall != 'A') {
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

            // deduct from wallet hand
            Player[WalletIndex].Credits -= Wager;

            // insert new hand object
            Player.insert(Player.begin() + PlayerIndex + 1, Hand());

            Hand& Current = Player[PlayerIndex];
            Hand& Split = Player[PlayerIndex + 1];

            // initialize split hand
            Split.Credits = 0;
            Split.Name = SName;
            Split.Bet = Wager;
            Split.AddCard(C2);
            Split.AddCard(GameDeck->Draw());

            // reset current hand
            Current.ClearHand();
            Current.Bet = Wager;
            Current.AddCard(C1);
            Current.AddCard(GameDeck->Draw());
        }
        // --- Double Down Execution ---
        else if (PlayerCall == 'd' || PlayerCall == 'D') {
            Player[WalletIndex].Credits -= Player[PlayerIndex].Bet;
            Player[PlayerIndex].Bet += Player[PlayerIndex].Bet;
            Player[PlayerIndex].AddCard(GameDeck->Draw());
            TurnOver = true;
        }
        // --- Hit Execution ---
        else if (PlayerCall == 'H' || PlayerCall == 'h') {
            Player[PlayerIndex].AddCard(GameDeck->Draw());
        }
        // --- Stand Execution ---
        else if (PlayerCall == 'S' || PlayerCall == 's') {
            TurnOver = true;
        }
        // --- Pass Execution ---
        else if (PlayerCall == 'a' || PlayerCall == 'A') {
            Player[WalletIndex].Credits += Player[PlayerIndex].Bet / 2;
            TurnOver = true;
        }

        // --- Check for Bust ---
        if (Player[PlayerIndex].Score > 21) {
            system("cls");
            DisplayStats(Player);
            DrawGameTable(Player, Dealer, true);
            DrawPanel({ Player[PlayerIndex].Name + " BUSTED!", "Score: " + std::to_string(Player[PlayerIndex].Score) });
            std::cout << "  (Press 'Enter' to continue...)" << std::endl;
            std::cin.ignore();
            std::cin.get();
        }
    }
}