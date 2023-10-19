#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <map>

using namespace std;

// Функція для знаходження відсотка стопок з однаковою довжиною
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
// Оголошення структури Card
struct Card {
    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
    enum Value { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

    Suit suit;
    Value value;

    void print() const {
        const char* suitNames[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        const char* valueNames[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

        std::cout << valueNames[value - TWO] << " of " << suitNames[suit] << std::endl;
    }
};

class DeckOfCards {
    std::vector<Card> deck;
    std::vector<int> pileSizes; // вектор для збереження розмірів стопок

public:
    std::vector<Card> pile;

    DeckOfCards(int n) {
        if (n > 52) throw std::invalid_argument("Maximum 52 cards are allowed.");

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
    void shuffleDeck() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(deck.begin(), deck.end(), g);
    }

    // Виймаємо карту з верху колоди
    Card drawCard() {
        if (deck.empty()) throw std::out_of_range("Deck is empty.");

        Card top = deck.back();
        deck.pop_back();
        return top;
    }

    // Виведення не тасованої колоди карт
    void printUnshuffledDeck() const {
        for (const Card& card : deck) {
            card.print();
        }
    }

    // Роздача карт і утворення стопки
    void dealCards(int n) {
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
                    // Виводимо стопку та починаємо нову стопку
                    cout << "\nNew Pile:" << endl;
                    for (const Card& pileCard : pile) {
                        pileCard.print();
                    }
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
    vector<int> returnPileSizes() const {
        return pileSizes;
    }
};

int main() {
    vector<int> pileSizesCount;
    vector<int> fullPileSizes; // Додано новий вектор

    int compareCount;
    cout << "\nEnter the number of cards to compare: ";
    cin >> compareCount;

    if (compareCount < 1) {
        cout << "Invalid number of cards to compare. Please enter a positive number." << endl;
        return 1;
    }

    int totalCompared = 0;

    while (totalCompared < compareCount) {
        int n;
        cout << "Enter the number of cards in the deck (1 to 13): ";
        cin >> n;

        if (n <= 0 || n > 13) {
            cout << "Invalid number of cards. Please enter a number from 1 to 13." << endl;
            return 1;
        }
        n = n * 4;
        DeckOfCards deck(n);

        if (totalCompared + n > compareCount) {
            n = compareCount - totalCompared;
        }

        totalCompared += n;
        cout << "Unshuffled Deck:" << endl;
        deck.printUnshuffledDeck();

        deck.shuffleDeck();

        cout << "\nShuffled Deck:" << endl;
        deck.dealCards(n);

        cout << "\nLast Pile:" << endl;
        for (const Card& pileCard : deck.pile) {
            pileCard.print();
        }

        pileSizesCount = deck.returnPileSizes();

        // Додайте розміри стопок до fullPileSizes
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

        cout << "\nMost frequent length: " << mostFrequent << endl;
        cout << "Average length: " << average << endl;
        cout << "Median length: " << median << endl;

        map<int, double> percentageOfLengths = calculatePercentageOfPileLengths(fullPileSizes);

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

