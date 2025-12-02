#include "Knapsack.h"

class Knapsack;

Knapsack::Knapsack() : items_size(0), capacity(0), items({}) {}

void Knapsack::fromFile(const string& filename) {

    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Openning file error: " + filename);
    }

    file >> items_size >> capacity;

    vector<vector<int>> items;
    for (int i = 0; i < items_size; i++) {
        file >> weight >> value;
        items.push_back({ weight, value });
    }

    file.close();
    return Knapsack(items_size, capacity, items);
}

int Knapsack::getItemsSize() const { return items_size; }
int Knapsack::getCapacity() const { return capacity; }
vector<vector<int>> Knapsack::getItems() const { return items; }