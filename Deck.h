#pragma once
#ifndef DECK_H
#define DECK_H
#include <iostream>
#include <vector>
#include "Card.h"
using namespace std;
class DeckOfCards {
    vector<Card> deck;
    vector<int> pileSizes; // вектор для збереження розмірів стопок

public:
    vector<Card> pile;

    DeckOfCards(int n);
    // Тасуємо колоду карт
    void shuffleDeck();
    // Виймаємо карту з верху колоди
    Card drawCard();
    // Виведення не тасованої колоди карт
     void printUnshuffledDeck();
    // Роздача карт і утворення стопки
    void dealCards(int n);

    // Виводимо розміри усіх стопок
    vector<int> returnPileSizes();
};
#endif