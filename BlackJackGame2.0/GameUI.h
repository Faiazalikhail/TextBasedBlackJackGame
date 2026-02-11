#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Hand.h"

// ================== HELPER FUNCTIONS ==================

std::string GetFullCardName(int rank, std::string suit) {
    if (rank == 1) return "Ace of " + suit;
    if (rank == 11) return "Jack of " + suit;
    if (rank == 12) return "Queen of " + suit;
    if (rank == 13) return "King of " + suit;
    return std::to_string(rank) + " of " + suit;
}

std::string GetRankStr(int rank) {
    if (rank == 1) return "A";
    if (rank == 11) return "J";
    if (rank == 12) return "Q";
    if (rank == 13) return "K";
    return std::to_string(rank);
}

std::string GetSuitArtLine(std::string suit, int line) {
    char s = suit.empty() ? '?' : suit[0]; // Get first char of suit
    if (s == 'D') {
        if (line == 0) return "  /\\   "; 
        if (line == 1) return " /  \\  ";
        if (line == 2) return " \\  /  "; 
        if (line == 3) return "  \\/   ";
    }
    if (s == 'H') {
        if (line == 0) return " _  _  "; 
        if (line == 1) return "( \\/ ) ";
        if (line == 2) return " \\  /  "; 
        if (line == 3) return "  \\/   ";
    }
    if (s == 'C') {
        if (line == 0) return "   _   "; 
        if (line == 1) return "  ( )  ";
        if (line == 2) return " (_|_) "; 
        if (line == 3) return "   |   ";
    }
    if (s == 'S') {
        if (line == 0) return "   ^   "; 
        if (line == 1) return "  / \\  ";
        if (line == 2) return " (_|_) "; 
        if (line == 3) return "   |   ";
    }
    return "       ";
}

void PrintCentered(std::string text, int width) {
    int padding = width - (int)text.length();
    if (padding < 0) padding = 0;
    for (int i = 0; i < padding / 2; i++) std::cout << " ";
    std::cout << text;
    for (int i = 0; i < (padding - padding / 2); i++) std::cout << " ";
}

// ================== DRAWING LOGIC ==================

void DrawPanel(std::vector<std::string> lines) {
    size_t maxWidth = 0; // Find longest line
    for (const auto& line : lines) if (line.length() > maxWidth) maxWidth = line.length();

    int boxWidth = (int)maxWidth + 4;
    std::cout << "\n"; for (int i = 0; i < boxWidth; i++) std::cout << "="; std::cout << "\n";

    for (const auto& line : lines) {
        std::cout << "| " << line;
        for (int j = 0; j < (int)(maxWidth - line.length()); j++) std::cout << " ";
        std::cout << " |\n";
    }
    for (int i = 0; i < boxWidth; i++) std::cout << "="; std::cout << "\n";
}

void DisplayStats(const std::vector<Hand>& Players) { /* Header now in DrawGameTable */ }

void DrawGameTable(std::vector<Hand>& Players, Hand& Dealer, bool hideDealerHoleCard) {
    const int SLOT_WIDTH = 19; const int CARD_WIDTH = 11;
    int totalTableWidth = 0;
    for (const auto& p : Players) totalTableWidth += (p.Cards.size() * SLOT_WIDTH) + 4;
    totalTableWidth -= 4; // Remove last separator

    // --- Header ---
    int headerWidth = (totalTableWidth < 36) ? 36 : totalTableWidth; // Enforce min width
    std::cout << "\n  "; for (int i = 0; i < headerWidth; i++) std::cout << "=";
    std::cout << "\n  |"; PrintCentered("TFS HIGH STAKES BLACKJACK", headerWidth - 2); std::cout << "|\n  ";
    for (int i = 0; i < headerWidth; i++) std::cout << "="; std::cout << "\n\n";

    // --- Player Rows ---
    // Row A: Names
    std::cout << "  ";
    for (size_t p = 0; p < Players.size(); p++) {
        PrintCentered(Players[p].Name, Players[p].Cards.size() * SLOT_WIDTH);
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << "\n  ";

    // Row B: Stats
    for (size_t p = 0; p < Players.size(); p++) {
        std::string stats = "$" + std::to_string(Players[p].Credits) + " | Bet:" + std::to_string(Players[p].Bet);
        PrintCentered(stats, Players[p].Cards.size() * SLOT_WIDTH);
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << "\n  ";

    // Row C: Separator
    for (size_t p = 0; p < Players.size(); p++) {
        for (size_t k = 0; k < Players[p].Cards.size() * SLOT_WIDTH; k++) std::cout << "-";
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << "\n";

    // Row D: Cards (8 Lines)
    for (int line = 0; line < 8; line++) {
        std::cout << "  ";
        for (size_t p = 0; p < Players.size(); p++) {
            for (const auto& card : Players[p].Cards) {
                std::string r = GetRankStr(card->Rank);
                std::string rLeft = (r.length() == 1) ? r + " " : r;
                std::string rRight = (r.length() == 1) ? " " + r : r;
                std::string suitLine = GetSuitArtLine(card->Suit, line - 2);
                int pad = (SLOT_WIDTH - CARD_WIDTH) / 2;

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

    // Row E: Full Names
    std::cout << "  ";
    for (size_t p = 0; p < Players.size(); p++) {
        for (const auto& card : Players[p].Cards) {
            PrintCentered(GetFullCardName(card->Rank, card->Suit), SLOT_WIDTH);
        }
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << "\n  ";

    // Row F: Footer
    for (size_t p = 0; p < Players.size(); p++) {
        for (size_t k = 0; k < Players[p].Cards.size() * SLOT_WIDTH; k++) std::cout << "-";
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << "\n  ";

    // Row G: Hand Total
    for (size_t p = 0; p < Players.size(); p++) {
        PrintCentered("Hand Total: " + std::to_string(Players[p].Score), Players[p].Cards.size() * SLOT_WIDTH);
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << "\n\n";

    // --- Dealer Section ---
    int absWidth = (totalTableWidth < 36) ? 36 : totalTableWidth;
    int dealerWidth = (int)Dealer.Cards.size() * SLOT_WIDTH;
    int start = (absWidth / 2) - (dealerWidth / 2); if (start < 0) start = 0;

    std::string dTitle = "THE DEALER";
    for (int i = 0; i < start + (dealerWidth / 2 - (int)dTitle.length() / 2); i++) std::cout << " ";
    std::cout << dTitle << "\n";
    for (int i = 0; i < start; i++) std::cout << " ";
    for (int i = 0; i < dealerWidth; i++) std::cout << "-";
    std::cout << "\n";

    for (int line = 0; line < 8; line++) {
        for (int i = 0; i < start; i++) std::cout << " ";
        for (size_t c = 0; c < Dealer.Cards.size(); c++) {
            int pad = (SLOT_WIDTH - CARD_WIDTH) / 2;
            for (int s = 0; s < pad; s++) std::cout << " ";

            if (c == 0 && hideDealerHoleCard) {
                if (line == 0) std::cout << " _________ ";
                else if (line == 7) std::cout << "|_________|";
                else std::cout << "|#########|";
            }
            else {
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
    std::cout << "\n";
}