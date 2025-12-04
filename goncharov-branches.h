#include "Knapsack.h"
#include <vector>

using namespace std;

struct Node {
    int level;
    int weight;
    int value;
    double bound;
    vector<int> items;
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) {
        return a.bound < b.bound;
    }
};

double calcBound(int level, int weight, int value,
    const vector<vector<int>>& items,
    int capacity, int n,
    const vector<pair<double, int>>& ratios);

vector<vector<int>> bb_method(Knapsack knapsack); 