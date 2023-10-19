#pragma once
#include <map>
#include <iostream>
#include <vector>

using namespace std;
// Функція для знаходження відсотка стопок з однаковою довжиною
map<int, double> calculatePercentageOfPileLengths(const vector<int>& pileSizes);
// Функція для знаходження довжини, яка зустрічалася найчастіше
int findMostFrequentLength(const vector<int>& pileSizes);
// Функція для знаходження середньої довжини стопок
double calculateAverageLength(const vector<int>& pileSizes);
// Функція для знаходження медіанної довжини стопок
double calculateMedianLength(vector<int>& pileSizes);