#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<string> process_input(string rawInput, char delimiter) {
    stringstream input(rawInput);
    string segment;
    vector<string> parts;

    while (getline(input, segment, delimiter))
    {
        parts.push_back(segment);
    }

    return parts;
}

int main() {
    ifstream inputFile;
    inputFile.open("input");

    string rawInput;
    inputFile >> rawInput;
    vector<string> dm_parts = process_input(rawInput, ',');

    map<int, vector<int>> dms;
    map<int, bool> visited; 
    for (string dm : dm_parts)
    {
        vector<string> from_to = process_input(dm, '-');
        int from = stoi(from_to[0]);
        int to = stoi(from_to[1]);

        if (dms.find(from) == dms.end())
            dms[from] = vector<int>();
        dms[from].push_back(to); 
        visited[from] = false;
        
        // Because is undirected graph
        if (dms.find(to) == dms.end())
            dms[to] = vector<int>();
        dms[to].push_back(from); 
        visited[to] = false;
    }

    
    int max_graph = 0; 
    for (pair<int, bool> node : visited)
    {
        if (node.second == true)
            continue;

        int max_current = 0;
        queue<int> queue;
        queue.push(node.first);

        while (!queue.empty())
        {
            int current = queue.front();
            queue.pop();

            if (visited[current])
                continue;
            
            max_current++;
            visited[current] = true;

            for (int next : dms[current])
            {
                queue.push(next);
            }
        }

        max_graph = max(max_graph, max_current);
    }

    cout << "Max DMs: " << max_graph << endl;

    return 0;
}