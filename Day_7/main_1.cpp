#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

#define ll long long
#define SPLIT '^'

void simulate_splits(vector<string> &lines, set<pair<int, int>> &splits, pair<int, int> current);

int main()
{
    ifstream inputFile;
    inputFile.open("input");

    vector<string> lines;
    string line;
    while (getline(inputFile, line))
    {
        line += ' '; // Adding a space to avoid corner case
        lines.push_back(line);
    }

    // Finding S
    pair<int, int> S;
    for (int i = 0; i < lines[0].size(); i++)
    {
        if (lines[0][i] == 'S')
        {
            S.first = 0;
            S.second = i;
        }
    }
    
    set<pair<int, int>> splits;
    simulate_splits(lines, splits, S);
    
    cout << splits.size() << endl;

    return 0;
}

void simulate_splits(vector<string> &lines, set<pair<int, int>> &splits, pair<int, int> current)
{
    // If out of board or already visited, stop looking.
    if (current.first >= lines.size() || current.second < 0 || current.second >= lines[current.first].size() || splits.find(current) != splits.end())
        return;

    // If a split, move left and right.
    if (lines[current.first][current.second] == SPLIT)
    {
        splits.insert(current);
        simulate_splits(lines, splits, make_pair(current.first, current.second-1));
        simulate_splits(lines, splits, make_pair(current.first, current.second+1));
    }

    // If normal, just flow down.
    simulate_splits(lines, splits, make_pair(current.first+1, current.second));
}