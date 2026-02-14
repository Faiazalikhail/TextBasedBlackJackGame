#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Hand.h"

// ================== HELPER FUNCTIONS ==================

// format full card name string
std::string GetFullCardName(int rank, std::string suit) {
    if (rank == 1) return "Ace of " + suit;
    if (rank == 11) return "Jack of " + suit;
    if (rank == 12) return "Queen of " + suit;
    if (rank == 13) return "King of " + suit;
    return std::to_string(rank) + " of " + suit;
}

// get short rank for card art
std::string GetRankStr(int rank) {
    if (rank == 1) return "A";
    if (rank == 11) return "J";
    if (rank == 12) return "Q";
    if (rank == 13) return "K";
    return std::to_string(rank);
}

// get specific ascii art line for suit symbol
std::string GetSuitArtLine(std::string suit, int line) {
    char s = suit.empty() ? '?' : suit[0];

    // diamonds art
    if (s == 'D') {
        if (line == 0) return "  /\\   ";
        if (line == 1) return " /  \\  ";
        if (line == 2) return " \\  /  ";
        if (line == 3) return "  \\/   ";
    }
    // hearts art
    if (s == 'H') {
        if (line == 0) return " _  _  ";
        if (line == 1) return "( \\/ ) ";
        if (line == 2) return " \\  /  ";
        if (line == 3) return "  \\/   ";
    }
    // clubs art
    if (s == 'C') {
        if (line == 0) return "   _   ";
        if (line == 1) return "  ( )  ";
        if (line == 2) return " (_|_) ";
        if (line == 3) return "   |   ";
    }
    // spades art
    if (s == 'S') {
        if (line == 0) return "   ^   ";
        if (line == 1) return "  / \\  ";
        if (line == 2) return " (_|_) ";
        if (line == 3) return "   |   ";
    }
    return "       ";
}

// print text centered within width
void PrintCentered(std::string text, int width) {
    int padding = width - (int)text.length();
    if (padding < 0) {
        padding = 0;
    }

    // print left padding
    for (int i = 0; i < padding / 2; i++) {
        std::cout << " ";
    }
    std::cout << text;
    // print right padding
    for (int i = 0; i < (padding - padding / 2); i++) {
        std::cout << " ";
    }
}

// ================== DRAWING LOGIC ==================

// draw a bordered box with text lines
void DrawPanel(std::vector<std::string> lines) {
    size_t maxWidth = 0;

    // find max width
    for (const auto& line : lines) {
        if (line.length() > maxWidth) {
            maxWidth = line.length();
        }
    }

    int boxWidth = (int)maxWidth + 4;

    // print top border
    std::cout << "\n";
    for (int i = 0; i < boxWidth; i++) {
        std::cout << "=";
    }
    std::cout << "\n";

    // print content lines
    for (const auto& line : lines) {
        std::cout << "| " << line;
        for (int j = 0; j < (int)(maxWidth - line.length()); j++) {
            std::cout << " ";
        }
        std::cout << " |\n";
    }

    // print bottom border
    for (int i = 0; i < boxWidth; i++) {
        std::cout << "=";
    }
    std::cout << "\n";
}

// placeholder for legacy calls
void DisplayStats(const std::vector<Hand>& Players) {
}

// main visualization function for table state
void DrawGameTable(std::vector<Hand>& Players, Hand& Dealer, bool hideDealerHoleCard) {
    const int SLOT_WIDTH = 19;
    const int CARD_WIDTH = 11;
    int totalTableWidth = 0;

    // calculate table width
    for (const auto& p : Players) {
        totalTableWidth += (p.Cards.size() * SLOT_WIDTH) + 4;
    }
    totalTableWidth -= 4;

    // determine header width
    int headerWidth = (totalTableWidth < 36) ? 36 : totalTableWidth;

    // --- Header ---
    std::cout << "\n  ";
    for (int i = 0; i < headerWidth; i++) std::cout << "=";
    std::cout << "\n  |";
    PrintCentered("TFS HIGH STAKES BLACKJACK", headerWidth - 2);
    std::cout << "|\n  ";
    for (int i = 0; i < headerWidth; i++) std::cout << "=";
    std::cout << "\n\n";

    // --- Player Names ---
    std::cout << "  ";
    for (size_t p = 0; p < Players.size(); p++) {
        PrintCentered(Players[p].Name, Players[p].Cards.size() * SLOT_WIDTH);
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << "\n  ";

    // --- Player Stats ---
    for (size_t p = 0; p < Players.size(); p++) {
        std::string stats = "$" + std::to_string(Players[p].Credits) + " | Bet:" + std::to_string(Players[p].Bet);
        PrintCentered(stats, Players[p].Cards.size() * SLOT_WIDTH);
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << "\n  ";

    // --- Separator ---
    for (size_t p = 0; p < Players.size(); p++) {
        for (size_t k = 0; k < Players[p].Cards.size() * SLOT_WIDTH; k++) std::cout << "-";
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << "\n";

    // --- Player Cards (8 lines of art) ---
    for (int line = 0; line < 8; line++) {
        std::cout << "  ";
        for (size_t p = 0; p < Players.size(); p++) {
            for (const auto& card : Players[p].Cards) {
                // get art parts
                std::string r = GetRankStr(card->Rank);
                std::string rLeft = (r.length() == 1) ? r + " " : r;
                std::string rRight = (r.length() == 1) ? " " + r : r;
                std::string suitLine = GetSuitArtLine(card->Suit, line - 2);
                int pad = (SLOT_WIDTH - CARD_WIDTH) / 2;

                // print card line
                for (int s = 0; s < pad; s++) std::cout << " ";

                if (line == 0) std::cout << " _________ ";
                else if (line == 1) std::cout << "|" << rLeft << "       |";
                else if (line >= 2 && line <= 5) std::cout << "| " << suitLine << " |";
                else if (line == 6) std::cout << "|       " << rRight << "|";
                else if (line == 7) std::cout << "|_________|";

                for (int s = 0; s < (SLOT_WIDTH - CARD_WIDTH - pad); s++) std::cout << " ";
            }
            if (p < Players.size() - 1) std::cout << " || ";
        }
        std::cout << "\n";
    }

    // --- Full Card Names ---
    std::cout << "  ";
    for (size_t p = 0; p < Players.size(); p++) {
        for (const auto& card : Players[p].Cards) {
            PrintCentered(GetFullCardName(card->Rank, card->Suit), SLOT_WIDTH);
        }
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << "\n  ";

    // --- Footer ---
    for (size_t p = 0; p < Players.size(); p++) {
        for (size_t k = 0; k < Players[p].Cards.size() * SLOT_WIDTH; k++) std::cout << "-";
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << "\n  ";

    // --- Hand Totals ---
    for (size_t p = 0; p < Players.size(); p++) {
        std::string scoreTxt = "Hand Total: " + std::to_string(Players[p].Score);
        if (Players[p].Score > 21) scoreTxt += " (BUST)";
        PrintCentered(scoreTxt, Players[p].Cards.size() * SLOT_WIDTH);
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << "\n\n";

    // --- Dealer Section ---
    int absWidth = (totalTableWidth < 36) ? 36 : totalTableWidth;
    int dealerWidth = (int)Dealer.Cards.size() * SLOT_WIDTH;
    int start = (absWidth / 2) - (dealerWidth / 2);
    if (start < 0) start = 0;

    std::string dTitle = "THE DEALER";

    // print centered title
    for (int i = 0; i < start + (dealerWidth / 2 - (int)dTitle.length() / 2); i++) std::cout << " ";
    std::cout << dTitle << "\n";

    // print separator
    for (int i = 0; i < start; i++) std::cout << " ";
    for (int i = 0; i < dealerWidth; i++) std::cout << "-";
    std::cout << "\n";

    // --- Dealer Cards (8 lines) ---
    for (int line = 0; line < 8; line++) {
        for (int i = 0; i < start; i++) std::cout << " ";
        for (size_t c = 0; c < Dealer.Cards.size(); c++) {
            int pad = (SLOT_WIDTH - CARD_WIDTH) / 2;
            for (int s = 0; s < pad; s++) std::cout << " ";

            // handle hidden card
            if (c == 0 && hideDealerHoleCard) {
                if (line == 0) std::cout << " _________ ";
                else if (line == 7) std::cout << "|_________|";
                else std::cout << "|#########|";
            }
            else {
                // handle visible card
                std::string r = GetRankStr(Dealer.Cards[c]->Rank);
                std::string suitLine = GetSuitArtLine(Dealer.Cards[c]->Suit, line - 2);
                if (line == 0) std::cout << " _________ ";
                else if (line == 1) std::cout << "|" << (r.length() == 1 ? r + " " : r) << "       |";
                else if (line >= 2 && line <= 5) std::cout << "| " << suitLine << " |";
                else if (line == 6) std::cout << "|       " << (r.length() == 1 ? " " + r : r) << "|";
                else if (line == 7) std::cout << "|_________|";
            }
            for (int s = 0; s < (SLOT_WIDTH - CARD_WIDTH - pad); s++) std::cout << " ";
        }
        std::cout << "\n";
    }

    // --- Dealer Score ---
    std::cout << "\n";
    for (int i = 0; i < start; i++) std::cout << " ";

    std::string dealerScoreTxt;
    if (hideDealerHoleCard) {
        dealerScoreTxt = "Hand Total: ?";
    }
    else {
        dealerScoreTxt = "Hand Total: " + std::to_string(Dealer.Score);
        if (Dealer.Score > 21) {
            dealerScoreTxt += " (BUSTED!)";
        }
    }
    PrintCentered(dealerScoreTxt, dealerWidth);
    std::cout << "\n";

    // --- Bottom Separator ---
    for (int i = 0; i < start; i++) std::cout << " ";
    for (int i = 0; i < dealerWidth; i++) std::cout << "-";
    std::cout << "\n";

    // --- Bottom Border ---
    for (int i = 0; i < headerWidth; i++) std::cout << "=";
    std::cout << "\n";
}