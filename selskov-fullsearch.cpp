#include "selskov-fullsearch.h"
#include <vector>

using namespace std;

vector<vector<int>> fullsearch_method(Knapsack knapsack)
{
    vector<vector<int>> result;
    
    vector<vector<int>> items = knapsack.getItems();
    int capacity = knapsack.getCapacity();
    int n = knapsack.getItemsSize();
    
    int maxValue = 0;
    int maxWeight = 0;
    vector<int> bestItems; 
    
    int totalCombinations = 1 << n;
    
    for (int mask = 0; mask < totalCombinations; ++mask) {
        int currentWeight = 0;
        int currentValue = 0;
        vector<int> currentItems;
        
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                currentWeight += items[i][0];
                currentValue += items[i][1];
                currentItems.push_back(i);
            }
        }
        
        if (currentWeight <= capacity && currentValue > maxValue) {
            maxValue = currentValue;
            maxWeight = currentWeight;
            bestItems = currentItems;
        }
    }
      
    for (int idx : bestItems) {
        vector<int> itemPair;
        itemPair.push_back(items[idx][0]); 
        itemPair.push_back(items[idx][1]); 
        result.push_back(itemPair);
    }
    
    return result;
}