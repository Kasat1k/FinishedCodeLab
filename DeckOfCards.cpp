#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <map>
#include "Deck.h"
#include "Card.h"
#include "functions.h"
using namespace std;
int main() {
    vector<int> pileSizesCount;
    vector<int> fullPileSizes; 
    bool compare = 1;
    int compareCount;
    while (compare) {
        cout << "Enter the number of cards to compare  : ";
        cin >> compareCount;
        if (compareCount < 1) {
            cout << "Invalid number of cards to compare. Please enter a positive number." << endl;
        }
        else compare = 0;
    }

    int totalCompared = 0;

    while (totalCompared < compareCount) {
        int n;
        bool numberDeck=1;
        while (numberDeck) {
            cout << "Enter the number of cards in the deck (1 to 13): ";
            cin >> n;

            if (n <= 0 || n > 13) {
                cout << "Invalid number of cards. Please enter a number from 1 to 13." << endl;
            }
            else numberDeck = 0;
        }
        n = n * 4;
        DeckOfCards deck(n);

        if (totalCompared + n > compareCount) {
            n = compareCount - totalCompared;
        }

        totalCompared += n;
        deck.shuffleDeck();
        deck.dealCards(n);
    
        pileSizesCount = deck.returnPileSizes();

        // Додавання розміри стопок до fullPileSizes
        fullPileSizes.insert(fullPileSizes.end(), pileSizesCount.begin(), pileSizesCount.end());

        cout << "\nTotal Compared Cards: " << totalCompared << "/" << compareCount << endl;
        if (totalCompared < compareCount) {
            char continueChoice;
            cout << "Continue comparing? (y/n): ";
            cin >> continueChoice;
            if (continueChoice != 'y' && continueChoice != 'Y') {
                break;
            }
        }
    }
    cout << "\nPile sizes:" << endl;
    for (int size : fullPileSizes) { // Виводимо всі розміри стопок
        cout << size << " ";
    }
    
    try {
        int mostFrequent = findMostFrequentLength(fullPileSizes);
        double average = calculateAverageLength(fullPileSizes);
        double median = calculateMedianLength(fullPileSizes);
        map<int, double> percentageOfLengths = calculatePercentageOfPileLengths(fullPileSizes);
        cout << "\nMost frequent length: " << mostFrequent << endl;
        cout << "\nAverage length: " << average << endl;
        cout << "\nMedian length: " << median << endl;
        cout << "\nPercentage of pile lengths:" << endl;

        for (const auto& pair : percentageOfLengths) {
            int length = pair.first;
            double percentage = pair.second;
            cout << "Length " << length << ": " << percentage << "%" << endl;
        }
    }
    catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}

