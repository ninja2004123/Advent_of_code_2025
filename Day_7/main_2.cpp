#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

#define ll long long
#define SPLIT '^'

ll simulate_splits(vector<string> &lines, map<pair<int, int>, ll> &splits, pair<int, int> current);

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
    
    map<pair<int, int>, ll> splits;
    ll number_of_timelines = simulate_splits(lines, splits, S);

    cout << number_of_timelines << endl;
    
    // cout << splits.size() << endl; For finding part one it's just as easy :)

    return 0;
}

ll simulate_splits(vector<string> &lines, map<pair<int, int>, ll> &splits, pair<int, int> current)
{
    // If reached the end, one path has been found.
    if (current.first >= lines.size())
        return 1;

    // if already visited, return the number of possibilities downwards.
    if (splits.find(current) != splits.end())
        return splits[current];

    // If invalid range, don't count it.
    if (current.second < 0 || current.second >= lines[current.first].size())
        return 0;

    // If a split, that's the sum of possibilities of the children.
    if (lines[current.first][current.second] == SPLIT)
    {
        splits[current] = simulate_splits(lines, splits, make_pair(current.first, current.second-1)) +
                            simulate_splits(lines, splits, make_pair(current.first, current.second+1));
        
        return splits[current];
    }
   
    // Just flow down.
    return simulate_splits(lines, splits, make_pair(current.first+1, current.second));
}