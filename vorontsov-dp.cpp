#include "vorontsov-dp.h"
#include <algorithm>
#include <functional>

vector<vector<int>> dp_method(Knapsack knapsack)
{
	vector<vector<int>> items = knapsack.getItems();

	int n = knapsack.getItemsSize();
	int W = knapsack.getCapacity();
	vector<vector<int>> table(n + 1, vector<int>(W + 1, 0));

	for (int k = 1; k <= n; k++) {
        int weight = items[k - 1][0];
        int price = items[k - 1][1];
        
        for (int s = 0; s <= W; s++) {
            if (weight > s) {
                table[k][s] = table[k - 1][s];
            } else {
                table[k][s] = max(table[k - 1][s], table[k - 1][s - weight] + price);
            }
        }
    }

	vector<vector<int>> result;
	
	while (n > 0 && W > 0) {
		if (table[n][W] != table[n - 1][W]) {
			result.push_back(items[n - 1]);
			W -= items[n - 1][0];
		}
		n--;
	}

	return result;
}