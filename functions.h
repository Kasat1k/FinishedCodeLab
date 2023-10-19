#pragma once
#include <map>
#include <iostream>
#include <vector>

using namespace std;
// ������� ��� ����������� ������� ������ � ��������� ��������
map<int, double> calculatePercentageOfPileLengths(const vector<int>& pileSizes);
// ������� ��� ����������� �������, ��� ����������� ���������
int findMostFrequentLength(const vector<int>& pileSizes);
// ������� ��� ����������� �������� ������� ������
double calculateAverageLength(const vector<int>& pileSizes);
// ������� ��� ����������� ������� ������� ������
double calculateMedianLength(vector<int>& pileSizes);