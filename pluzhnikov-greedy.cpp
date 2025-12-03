#include "pluzhnikov-greedy.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> greedy_method(Knapsack knapsack)
{
    vector<vector<int>> result;
    
    int n = knapsack.getItemsSize();
    int M = knapsack.getCapacity();
    vector<vector<int>> items = knapsack.getItems();
    
    if (n == 0 || M == 0 || items.empty()) {
        return result;
    }
    
    vector<int> indices(n);
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }
    
    // Сортируем по убыванию удельной стоимости (цена/вес)
    sort(indices.begin(), indices.end(), 
         [&items](int a, int b) {
             double density_a = (double)items[a][1] / items[a][0]; 
             double density_b = (double)items[b][1] / items[b][0];
             return density_a > density_b; 
         });
    
    // Жадный выбор
    int current_weight = 0;
    
    for (int idx : indices) {
        int weight = items[idx][0];
        
        // Если предмет помещается в рюкзак
        if (current_weight + weight <= M) {
            // Добавляем предмет в результат как [вес, цена]
            result.push_back({items[idx][0], items[idx][1]});
            current_weight += weight;
        }
    }
    
    return result;
}