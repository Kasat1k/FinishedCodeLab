#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <map>
#include "functions.h"
using namespace std;

map<int, double> calculatePercentageOfPileLengths(const vector<int>& pileSizes) {
    if (pileSizes.empty()) {
        throw invalid_argument("Input vector is empty.");
    }

    map<int, int> lengthCount; // Мапа для зберігання кількості стопок для кожної довжини
    map<int, double> percentageOfLengths; // Мапа для зберігання відсотка стопок для кожної довжини

    for (int length : pileSizes) {
        lengthCount[length]++;
    }

    int totalPiles = pileSizes.size();

    for (const auto& pair : lengthCount) {
        int length = pair.first;
        int count = pair.second;
        double percentage = (static_cast<double>(count) / totalPiles) * 100.0;
        percentageOfLengths[length] = percentage;
    }

    return percentageOfLengths;
}
// Функція для знаходження довжини, яка зустрічалася найчастіше
int findMostFrequentLength(const vector<int>& pileSizes) {
    if (pileSizes.empty()) {
        throw invalid_argument("Input vector is empty.");
    }

    // Визначаємо, яка довжина зустрічалася найчастіше
    int mostFrequentLength = pileSizes[0];
    int maxCount = 1;
    int currentLength = pileSizes[0];
    int currentCount = 1;

    for (size_t i = 1; i < pileSizes.size(); ++i) {
        if (pileSizes[i] == currentLength) {
            currentCount++;
        }
        else {
            if (currentCount > maxCount) {
                maxCount = currentCount;
                mostFrequentLength = currentLength;
            }
            currentLength = pileSizes[i];
            currentCount = 1;
        }
    }

    if (currentCount > maxCount) {
        mostFrequentLength = currentLength;
    }

    return mostFrequentLength;
}

// Функція для знаходження середньої довжини стопок
double calculateAverageLength(const vector<int>& pileSizes) {
    if (pileSizes.empty()) {
        throw invalid_argument("Input vector is empty.");
    }

    int sum = 0;
    for (int length : pileSizes) {
        sum += length;
    }

    return static_cast<double>(sum) / pileSizes.size();
}

// Функція для знаходження медіанної довжини стопок
double calculateMedianLength(vector<int>& pileSizes) {
    if (pileSizes.empty()) {
        throw invalid_argument("Input vector is empty.");
    }

    sort(pileSizes.begin(), pileSizes.end());

    size_t size = pileSizes.size();
    if (size % 2 == 0) {
        // Якщо кількість елементів парна, медіана - середнє значення двох середніх елементів
        return static_cast<double>(pileSizes[size / 2 - 1] + pileSizes[size / 2]) / 2.0;
    }
    else {
        // Якщо кількість елементів непарна, медіана - середній елемент
        return static_cast<double>(pileSizes[size / 2]);
    }
}