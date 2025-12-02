#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <map>
#include <functional>
#include "Knapsack.h"
#include "selskov-fullsearch.h"
#include "goncharov-branches.h"
#include "pluzhnikov-greedy.h"
#include "vorontsov-dp.h"

using namespace std;

static void generateTestCases() 
{
    srand(time(0));

    system("mkdir test_cases 2>nul");

    string filepath = "test_cases/test_";
    vector<int> sizes = { 5, 10, 20, 40, 80 };

    for (int i = 1; i <= 5; i++) 
    {
        string filename = filepath + to_string(i) + ".txt";
        ofstream file(filename);

        int n = sizes[i - 1];
        int max_item_weight = n * 2;

        int capacity = (max_item_weight / 2) * (n / 2);
        if (capacity < 10) capacity = 10;

        file << n << " " << capacity << endl;

        for (int j = 0; j < n; j++) 
        {
            int weight = rand() % max_item_weight + 1;
            int value = rand() % (weight * 10) + 1;
            file << weight << " " << value << endl;
        }

        file.close();
    }
}

int main() {

    generateTestCases();

    map < string, function<vector<vector<int>>(Knapsack)>> funcs;
    string test_dir = "test_cases/test_";

    funcs["fulsearch_method"] = fullsearch_method;
    funcs["bb_method"] = bb_method;
    funcs["greedy_method"] = greedy_method;
    funcs["dp_method"] = dp_method;

    cout << "KNAPSACK PACKING METHODS COMPETITION" << endl;
    cout << "====================================";

    for (int i = 1; i <= 5; i++)
    {
        string test_path = test_dir + to_string(i) + ".txt";
        Knapsack knapsack;
        knapsack.fromFile(test_path);

        cout << knapsack.getCapacity() << endl << knapsack.getItemsSize();
    }

    return 0;
}