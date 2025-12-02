#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Knapsack
{
private:

	int items_size;
	int capacity;
	vector<vector<int>> items; // first element - weight, second - price

public:

	Knapsack();

	void fromFile(const string& filename);

	int getItemsSize() const;
	int getCapacity() const;
	vector<vector<int>> getItems() const;
};