#pragma once
#ifndef DECK_H
#define DECK_H
#include <iostream>
#include <vector>
#include "Card.h"
using namespace std;
class DeckOfCards {
    vector<Card> deck;
    vector<int> pileSizes; // ������ ��� ���������� ������ ������

public:
    vector<Card> pile;

    DeckOfCards(int n);
    // ������ ������ ����
    void shuffleDeck();
    // ������� ����� � ����� ������
    Card drawCard();
    // ��������� �� �������� ������ ����
     void printUnshuffledDeck();
    // ������� ���� � ��������� ������
    void dealCards(int n);

    // �������� ������ ��� ������
    vector<int> returnPileSizes();
};
#endif