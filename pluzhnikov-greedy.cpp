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
    
    sort(indices.begin(), indices.end(), 
         [&items](int a, int b) {
             double density_a = (double)items[a][1] / items[a][0]; 
             double density_b = (double)items[b][1] / items[b][0];
             return density_a > density_b; 
         });
    
    vector<int> selected_indices;
    int current_weight = 0;       
    int total_value = 0;         
    
    for (int idx : indices) {
        int weight = items[idx][0];
        int value = items[idx][1];
        
        if (current_weight + weight <= M) {
            selected_indices.push_back(idx);    
            current_weight += weight;           
            total_value += value;             
        }
    }
    
    sort(selected_indices.begin(), selected_indices.end());
	
    result.push_back(selected_indices);
    
    return result;
}