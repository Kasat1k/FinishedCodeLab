#pragma once
#include <iostream>
using namespace std;
struct Card {
    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
    enum Value { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

    Suit suit;
    Value value;

    void print() const {
        const char* suitNames[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        const char* valueNames[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

        cout << valueNames[value - TWO] << " of " << suitNames[suit] << endl;
    }
};
