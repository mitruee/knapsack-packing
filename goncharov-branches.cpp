#include "goncharov-branches.h"
#include <algorithm>
#include <queue>

double calcBound(int level, int weight, int value,
    const vector<vector<int>>& items,
    int capacity, int n,
    const vector<pair<double, int>>& ratios) {

    if (weight >= capacity) return 0;

    double bound = value;
    int totalWeight = weight;

    for (int i = level; i < n; i++) {
        int idx = ratios[i].second;
        int w = items[idx][0];
        int v = items[idx][1];

        if (totalWeight + w <= capacity) {
            totalWeight += w;
            bound += v;
        }
        else {
            int remain = capacity - totalWeight;
            bound += v * ((double)remain / w);
            break;
        }
    }

    return bound;
}

vector<vector<int>> bb_method(Knapsack knapsack) {
    vector<vector<int>> result;
    int n = knapsack.getItemsSize();
    int capacity = knapsack.getCapacity();
    vector<vector<int>> items = knapsack.getItems();

    if (n == 0 || capacity == 0) return result;

    vector<pair<double, int>> ratios;
    for (int i = 0; i < n; i++) {
        ratios.push_back({ (double)items[i][1] / items[i][0], i });
    }

    sort(ratios.begin(), ratios.end(),
        [](auto& a, auto& b) { return a.first > b.first; });

    priority_queue<Node, vector<Node>, CompareNode> pq;

    Node root{ -1, 0, 0, calcBound(0, 0, 0, items, capacity, n, ratios), {} };
    pq.push(root);

    int maxValue = 0;
    vector<int> bestItems;

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.bound <= maxValue) continue;

        if (cur.level < n - 1) {
            int next = cur.level + 1;
            int idx = ratios[next].second;
            int w = items[idx][0];
            int v = items[idx][1];

            if (cur.weight + w <= capacity) {
                Node include{ next, cur.weight + w, cur.value + v,
                            calcBound(next + 1, cur.weight + w, cur.value + v,
                                     items, capacity, n, ratios), cur.items };
                include.items.push_back(idx);

                if (include.value > maxValue) {
                    maxValue = include.value;
                    bestItems = include.items;
                }

                if (include.bound > maxValue) pq.push(include);
            }

            Node exclude{ next, cur.weight, cur.value,
                        calcBound(next + 1, cur.weight, cur.value,
                                 items, capacity, n, ratios), cur.items };

            if (exclude.bound > maxValue) pq.push(exclude);
        }
    }

    for (int idx : bestItems) {
        result.push_back(items[idx]);
    }

    return result;
}