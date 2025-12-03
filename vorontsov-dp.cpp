#include "vorontsov-dp.h"
#include <algorithm>
#include <functional>

vector<vector<int>> dp_method(Knapsack knapsack)
{
	vector<vector<int>> items = knapsack.getItems();
	vector<int> weights, prices;

	for (auto& item : items) {
		weights.push_back(item[0]);
		prices.push_back(item[1]);
	}

	int itemsSize = knapsack.getItemsSize();
	int capacity = knapsack.getCapacity();
	vector<vector<int>> table(itemsSize + 1, vector<int>(capacity + 1, -1));

	function<int(int, int)> fillingKnapsack;

	fillingKnapsack = [&weights, &prices, &table, &fillingKnapsack](int k, int s) {
		if (k == 0 || s == 0) { return 0; }

		if (table[k][s] != -1) { return table[k][s]; }

		if (weights[k - 1] > s) {
			table[k][s] = fillingKnapsack(k - 1, s);
		} else {
			table[k][s] = max(fillingKnapsack(k - 1, s), 
				fillingKnapsack(k - 1, s - weights[k - 1]) + prices[k - 1]);
		}

		return table[k][s];
	};

	fillingKnapsack(itemsSize, capacity);

	vector<vector<int>> result;
	
	while (itemsSize > 0 && capacity > 0) {
		if (table[itemsSize][capacity] != table[itemsSize - 1][capacity]) {
			result.push_back({weights[itemsSize - 1], prices[itemsSize - 1]});
			capacity -= weights[itemsSize - 1];
		}
		itemsSize--;
	}

	return result;
}