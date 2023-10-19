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

// Тасуємо колоду карт
void DeckOfCards::shuffleDeck() {
    random_device rd;
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);
}

// Виймаємо карту з верху колоди
Card DeckOfCards::drawCard() {
    if (deck.empty()) throw out_of_range("Deck is empty.");

    Card top = deck.back();
    deck.pop_back();
    return top;
}

// Виведення не тасованої колоди карт
void DeckOfCards::printUnshuffledDeck() {
    for (const Card& card : deck) {
        card.print();
    }
}

// Роздача карт і утворення стопки
void DeckOfCards::dealCards(int n) {
    for (int i = 0; i < n; ++i) {
        Card card = drawCard();
        if (!pile.empty()) {
            Card topPileCard = pile.back();
            if (card.value > topPileCard.value) {
                // Додаємо карту до стопки
                pile.push_back(card);
            }
            else {
                // Зберігаємо розмір стопки
                pileSizes.push_back(pile.size());
             
                pile.clear();
                pile.push_back(card);
            }
        }
        else {
            // Перша карта у стопці
            pile.push_back(card);
        }
    }

    // Зберігаємо розмір останньої стопки
    if (!pile.empty()) {
        pileSizes.push_back(pile.size());
    }
}


// Виводимо розміри усіх стопок
vector<int> DeckOfCards::returnPileSizes() {
    return  pileSizes;
}
