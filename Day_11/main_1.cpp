#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <queue>

using namespace std;

#define ll long long
#define INPUT_FILE "input"
#define START "you"
#define END "out"

void create_graph_from_input(map<string, vector<string>> &graph);

int main()
{
    map<string, vector<string>> graph;
    create_graph_from_input(graph);

    stack<string> S;
    S.push(START);

    ll all_possible_paths = 0;
    while (!S.empty())
    {
        string current = S.top();
        S.pop();

        if (current == END)
        {
            all_possible_paths++;
            continue;
        }

        for (string next : graph[current])
        {
            S.push(next);
        }
    }

    cout << "Total Possible Paths: " << all_possible_paths << endl;

    return 0;
}

void create_graph_from_input(map<string, vector<string>> &graph)
{
    ifstream inputFile;
    inputFile.open(INPUT_FILE);

    string line;
    while (getline(inputFile, line))
    {
        regex node_pattern("([a-z]+)");
        sregex_iterator it(line.begin(), line.end(), node_pattern);
        sregex_iterator end; // Default-constructed iterator marks the end of the sequence
       
        string from;
        if (it != end)
        {
            smatch match = *it; 
            from = match.str();
            it++;
        }
        
        vector<string> to;
        while (it != end) {
            smatch match = *it; 
            to.push_back(match.str());
            it++;
        }

        graph[from] = to;
    }

    inputFile.close();
}