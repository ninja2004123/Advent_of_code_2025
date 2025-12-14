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

void create_graph_from_input(map<string, vector<string>> &graph);
ll number_of_paths(map<string, vector<string>> &graph, map<string, ll> &num_paths, string current, string end);

int main()
{
    map<string, vector<string>> graph;
    create_graph_from_input(graph);

    map<string, ll> num_paths = map<string, ll>();
    ll dac_to_out = number_of_paths(graph, num_paths, "dac", "out");

    num_paths = map<string, ll>();
    ll fft_to_dac = number_of_paths(graph, num_paths, "fft", "dac");

    num_paths = map<string, ll>();
    ll svr_to_fft = number_of_paths(graph, num_paths, "svr", "fft");

    cout << dac_to_out * fft_to_dac * svr_to_fft << endl;

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

ll number_of_paths(map<string, vector<string>> &graph, map<string, ll> &num_paths, string current, string end)
{
    if (current == end)
        return 1;

    if (num_paths.find(current) != num_paths.end())
        return num_paths[current];

    ll sum = 0;
    for (string next : graph[current])
    {
        sum += number_of_paths(graph, num_paths, next, end);
    }

    num_paths[current] = sum;
    return num_paths[current];
}