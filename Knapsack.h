#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Knapsack
{
// Knapsack class is not a class of fully assembled backpack, but a class which provide
// access to items that should be packed in knapsack, number of those items
// and capacity of backpack that should be packed as a result of your algorithm's work
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