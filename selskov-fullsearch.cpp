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
    vector<int> bestItems; 
    
    int totalCombinations = 1 << n;

        // Перебор всех масок (битовых комбинаций)
    for (int mask = 0; mask < totalCombinations; ++mask) {
        int currentWeight = 0;
        int currentValue = 0;
        vector<int> currentItems;
        
     // Проверка включенных в маску предметов
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                currentWeight += items[i][0];
                currentValue += items[i][1];
                currentItems.push_back(i);
            }
        }
        
        //Проверка вместимости и стоимости
        if (currentWeight <= capacity && currentValue > maxValue) {
            maxValue = currentValue;
            bestItems = currentItems; 
        }
    }
      
    //Форматирование результата
    for (int idx : bestItems) {
        result.push_back({items[idx][0], items[idx][1]});
    }
    
    return result;
}