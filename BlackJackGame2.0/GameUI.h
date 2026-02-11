#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include "Hand.h" 

// ==========================================
//           HELPER FUNCTIONS
// ==========================================

std::string GetFullCardName(int rank, std::string suit) {
    std::string rStr;
    if (rank == 1) rStr = "Ace";
    else if (rank == 11) rStr = "Jack";
    else if (rank == 12) rStr = "Queen";
    else if (rank == 13) rStr = "King";
    else rStr = std::to_string(rank);
    return rStr + " of " + suit;
}

std::string GetRankStr(int rank) {
    if (rank == 1) return "A";
    if (rank == 11) return "J";
    if (rank == 12) return "Q";
    if (rank == 13) return "K";
    return std::to_string(rank);
}

// --- SUIT ART ---
std::string GetSuitArtLine(std::string suit, int line) {
    char s = suit.empty() ? '?' : suit[0];

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
    int leftPad = padding / 2;
    int rightPad = padding - leftPad;
    for (int i = 0; i < leftPad; i++) std::cout << " ";
    std::cout << text;
    for (int i = 0; i < rightPad; i++) std::cout << " ";
}

// ==========================================
//           MAIN DRAWING LOGIC
// ==========================================

// We can keep this for other messages (like errors)
void DrawPanel(std::vector<std::string> lines) {
    size_t maxWidth = 0;
    for (const auto& line : lines) {
        if (line.length() > maxWidth) maxWidth = line.length();
    }
    int boxWidth = (int)maxWidth + 4;

    std::cout << std::endl;
    for (int i = 0; i < boxWidth; i++) std::cout << "=";
    std::cout << std::endl;

    for (const auto& line : lines) {
        std::cout << "| " << line;
        for (int j = 0; j < (int)(maxWidth - line.length()); j++) std::cout << " ";
        std::cout << " |" << std::endl;
    }

    for (int i = 0; i < boxWidth; i++) std::cout << "=";
    std::cout << std::endl;
}

// Keep this empty/simple as we moved the stats into the table
void DisplayStats(const std::vector<Hand>& Players) {
    // Intentionally empty - header is now part of DrawGameTable
}

void DrawGameTable(std::vector<Hand>& Players, Hand& Dealer, bool hideDealerHoleCard) {

    const int SLOT_WIDTH = 19;
    const int CARD_WIDTH = 11;

    // 1. Calculate Table Width
    int totalTableWidth = 0;
    for (const auto& p : Players) {
        totalTableWidth += (p.Cards.size() * SLOT_WIDTH);
        totalTableWidth += 4; // for separator
    }
    // Remove the last separator width (4) for perfect fit, then add padding
    totalTableWidth -= 4;

    // --- DRAW DYNAMIC HEADER ---
    int headerWidth = totalTableWidth;

    // If only 1 player, table is small (19 chars). 
    // Title "HIGH STAKES BLACKJACK" is 21 chars.
    // So for 1 player, we force a wider box (36). 
    // For 2-3 players, we use the full table width.
    if (headerWidth < 36) headerWidth = 36;

    std::cout << "\n  ";
    for (int i = 0; i < headerWidth; i++) std::cout << "=";
    std::cout << "\n  |";
    PrintCentered("TFS HIGH STAKES BLACKJACK", headerWidth - 2);
    std::cout << "|\n  ";
    for (int i = 0; i < headerWidth; i++) std::cout << "=";
    std::cout << "\n\n"; // <--- Extra spacing as requested


    // ROW A: Names
    std::cout << "  ";
    for (int p = 0; p < Players.size(); p++) {
        int playerZoneWidth = (int)Players[p].Cards.size() * SLOT_WIDTH;
        PrintCentered(Players[p].Name, playerZoneWidth);
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << std::endl;

    // ROW B: Stats (RESTORED!)
    std::cout << "  ";
    for (int p = 0; p < Players.size(); p++) {
        int playerZoneWidth = (int)Players[p].Cards.size() * SLOT_WIDTH;

        // Format: $1000 | Bet: 50
        std::string stats = "$" + std::to_string(Players[p].Credits) + " | Bet:" + std::to_string(Players[p].Bet);

        PrintCentered(stats, playerZoneWidth);
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << std::endl;

    // ROW C: Separator
    std::cout << "  ";
    for (int p = 0; p < Players.size(); p++) {
        int playerZoneWidth = (int)Players[p].Cards.size() * SLOT_WIDTH;
        for (int k = 0; k < playerZoneWidth; k++) std::cout << "-";
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << std::endl;

    // ROW D: Cards (8 Lines)
    for (int line = 0; line < 8; line++) {
        std::cout << "  ";
        for (int p = 0; p < Players.size(); p++) {
            for (const auto& card : Players[p].Cards) {

                std::string r = GetRankStr(card->Rank);
                std::string rLeft = (r.length() == 1) ? r + " " : r;
                std::string rRight = (r.length() == 1) ? " " + r : r;

                std::string suitLine = GetSuitArtLine(card->Suit, line - 2);

                int padLeft = (SLOT_WIDTH - CARD_WIDTH) / 2;
                int padRight = SLOT_WIDTH - CARD_WIDTH - padLeft;
                for (int s = 0; s < padLeft; s++) std::cout << " ";

                if (line == 0) std::cout << " _________ ";
                else if (line == 1) std::cout << "|" << rLeft << "       |";
                else if (line >= 2 && line <= 5) std::cout << "| " << suitLine << " |";
                else if (line == 6) std::cout << "|       " << rRight << "|";
                else if (line == 7) std::cout << "|_________|";

                for (int s = 0; s < padRight; s++) std::cout << " ";
            }
            if (p < Players.size() - 1) std::cout << " || ";
        }
        std::cout << std::endl;
    }

    // ROW E: Full Names
    std::cout << "  ";
    for (int p = 0; p < Players.size(); p++) {
        for (const auto& card : Players[p].Cards) {
            std::string fullName = GetFullCardName(card->Rank, card->Suit);
            PrintCentered(fullName, SLOT_WIDTH);
        }
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << std::endl;

    // ROW F: Footer Separator
    std::cout << "  ";
    for (int p = 0; p < Players.size(); p++) {
        int playerZoneWidth = (int)Players[p].Cards.size() * SLOT_WIDTH;
        for (int k = 0; k < playerZoneWidth; k++) std::cout << "-";
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << std::endl;

    // ROW G: Hand Total
    std::cout << "  ";
    for (int p = 0; p < Players.size(); p++) {
        int playerZoneWidth = (int)Players[p].Cards.size() * SLOT_WIDTH;
        std::string totalStr = "Hand Total: " + std::to_string(Players[p].Score);
        PrintCentered(totalStr, playerZoneWidth);
        if (p < Players.size() - 1) std::cout << " || ";
    }
    std::cout << std::endl << std::endl;


    // ===========================
    //      DRAW DEALER
    // ===========================

    // Recalculate full width for centering (including separators)
    int absoluteFullWidth = 0;
    for (const auto& p : Players) {
        absoluteFullWidth += (p.Cards.size() * SLOT_WIDTH);
        absoluteFullWidth += 4;
    }
    absoluteFullWidth -= 4; // remove last separator
    if (absoluteFullWidth < 36) absoluteFullWidth = 36; // Min width

    int dealerZoneWidth = (int)Dealer.Cards.size() * SLOT_WIDTH;
    int tableCenter = absoluteFullWidth / 2;
    int dealerStart = tableCenter - (dealerZoneWidth / 2);
    if (dealerStart < 0) dealerStart = 0;

    std::string dealerTitle = "THE DEALER";
    for (int i = 0; i < dealerStart + (dealerZoneWidth / 2 - (int)dealerTitle.length() / 2); i++) std::cout << " ";
    std::cout << dealerTitle << std::endl;

    for (int i = 0; i < dealerStart; i++) std::cout << " ";
    for (int i = 0; i < dealerZoneWidth; i++) std::cout << "-";
    std::cout << std::endl;

    for (int line = 0; line < 8; line++) {
        for (int i = 0; i < dealerStart; i++) std::cout << " ";

        for (int c = 0; c < Dealer.Cards.size(); c++) {
            int padLeft = (SLOT_WIDTH - CARD_WIDTH) / 2;
            int padRight = SLOT_WIDTH - CARD_WIDTH - padLeft;
            for (int s = 0; s < padLeft; s++) std::cout << " ";

            if (c == 0 && hideDealerHoleCard) {
                if (line == 0) std::cout << " _________ ";
                else if (line == 7) std::cout << "|_________|";
                else std::cout << "|#########|";
            }
            else {
                std::string r = GetRankStr(Dealer.Cards[c]->Rank);
                std::string rLeft = (r.length() == 1) ? r + " " : r;
                std::string rRight = (r.length() == 1) ? " " + r : r;
                std::string suitLine = GetSuitArtLine(Dealer.Cards[c]->Suit, line - 2);

                if (line == 0) std::cout << " _________ ";
                else if (line == 1) std::cout << "|" << rLeft << "       |";
                else if (line >= 2 && line <= 5) std::cout << "| " << suitLine << " |";
                else if (line == 6) std::cout << "|       " << rRight << "|";
                else if (line == 7) std::cout << "|_________|";
            }
            for (int s = 0; s < padRight; s++) std::cout << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    for (int i = 0; i < dealerStart; i++) std::cout << " ";
    for (int c = 0; c < Dealer.Cards.size(); c++) {
        if (c == 0 && hideDealerHoleCard) {
            PrintCentered("HIDDEN", SLOT_WIDTH);
        }
        else {
            std::string fullName = GetFullCardName(Dealer.Cards[c]->Rank, Dealer.Cards[c]->Suit);
            PrintCentered(fullName, SLOT_WIDTH);
        }
    }
    std::cout << std::endl << std::endl;
}