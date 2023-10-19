#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <map>
using namespace std;

DeckOfCards::DeckOfCards(int n) {
    if (n > 52) throw invalid_argument("Maximum 52 cards are allowed.");

    for (int value = Card::TWO; value <= Card::ACE; ++value) {
        for (int suit = Card::HEARTS; suit <= Card::SPADES; ++suit) {
            deck.push_back({ static_cast<Card::Suit>(suit), static_cast<Card::Value>(value) });
        }
    }

    if (n < 52) {
        deck.resize(n);
    }
}

// ������ ������ ����
void DeckOfCards::shuffleDeck() {
    random_device rd;
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);
}

// ������� ����� � ����� ������
Card DeckOfCards::drawCard() {
    if (deck.empty()) throw out_of_range("Deck is empty.");

    Card top = deck.back();
    deck.pop_back();
    return top;
}

// ��������� �� �������� ������ ����
void DeckOfCards::printUnshuffledDeck() {
    for (const Card& card : deck) {
        card.print();
    }
}

// ������� ���� � ��������� ������
void DeckOfCards::dealCards(int n) {
    for (int i = 0; i < n; ++i) {
        Card card = drawCard();
        if (!pile.empty()) {
            Card topPileCard = pile.back();
            if (card.value > topPileCard.value) {
                // ������ ����� �� ������
                pile.push_back(card);
            }
            else {
                // �������� ����� ������
                pileSizes.push_back(pile.size());
             
                pile.clear();
                pile.push_back(card);
            }
        }
        else {
            // ����� ����� � ������
            pile.push_back(card);
        }
    }

    // �������� ����� �������� ������
    if (!pile.empty()) {
        pileSizes.push_back(pile.size());
    }
}


// �������� ������ ��� ������
vector<int> DeckOfCards::returnPileSizes() {
    return  pileSizes;
}
