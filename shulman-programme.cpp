#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <string>
#include <unordered_map>
#include <functional>
#include "Knapsack.h"
#include "selskov-fullsearch.h"
#include "goncharov-branches.h"
#include "pluzhnikov-greedy.h"
#include "vorontsov-dp.h"

using namespace std;

static void generateTestCases() 
{
    auto now = chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto seconds = chrono::duration_cast<chrono::seconds>(duration).count();

    srand(seconds);

    system("mkdir test_cases 2>nul");

    string filepath = "test_cases/test_";
    vector<int> sizes = { 5, 10, 15, 20, 30 };

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

    unordered_map < string, function<vector<vector<int>>(Knapsack)>> funcs;
    string test_dir = "test_cases/test_";

    funcs["dp_method"] = dp_method;
    funcs["greedy_method"] = greedy_method;
    funcs["bb_method"] = bb_method;    
    funcs["fulsearch_method"] = fullsearch_method;

    cout << "====================================" << endl;
    cout << "KNAPSACK PACKING METHODS COMPETITION" << endl;
    cout << "====================================" << endl;

    for (int i = 1; i <= 5; i++)
    {
        string test_path = test_dir + to_string(i) + ".txt";
        Knapsack knapsack;
        knapsack.fromFile(test_path);

        cout << endl
        << "########################" << endl
        << "Filename: " << test_path << endl
        << "Number of elements: " << knapsack.getItemsSize() << endl
        << "Knapsack capacity: " << knapsack.getCapacity() << endl
        << "-------------------------" << endl;

        for (const auto pair : funcs)
        {
            cout << "Method's name: " << pair.first << endl << endl;

            auto start = chrono::high_resolution_clock::now();

            vector<vector<int>> result = pair.second(knapsack);

            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

            cout << "Algorithm duration: " << duration.count() << endl << endl;

            cout << "* Packed knapsack *" << endl;
            cout << "  Weight | Price  " << endl;

            int total_weight = 0;
            int total_price = 0;

            for (vector<int> el : result)
            {
                total_weight += el[0];
                total_price += el[1];

                string weight = to_string(el[0]);
                string price = to_string(el[1]);
                char pad_char = ' ';

                int fw = 6 - weight.size();
                int rfw = fw / 2;   
                int lfw = fw - rfw;

                int fp = 5 - price.size();
                int rfp = fp / 2;
                int lfp = fp - rfp;

                cout << string(lfw + 2, pad_char) + weight + string(rfw + 2, pad_char) + string(lfp + 1, pad_char) 
                + price + string(rfp + 2, pad_char) << endl;
            }
            
            cout << endl << "Total weight: " << total_weight << endl;
            cout << "Total price: " << total_price << endl;
            cout << "-------------------------" << endl;
        
        }

        cout << "########################" << endl;

    }

    return 0;
}