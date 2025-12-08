#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<int> process_input(string rawInput, char delimiter) {
    stringstream input(rawInput);
    string segment;
    vector<int> ranges;

    while (getline(input, segment, delimiter))
    {
        ranges.push_back(stoi(segment));
    }

    return ranges;
}

int main() {
    ifstream inputFile;
    inputFile.open("input");

    string rawInput;
    inputFile >> rawInput;
    vector<int> vibe_scores = process_input(rawInput, ',');

    for (int i = 1; i < vibe_scores.size(); i++)
    {
        vibe_scores[i] = max(vibe_scores[i], vibe_scores[i] + vibe_scores[i-1]);
    }

    int max_vibe_score = INT32_MIN;
    for (int i = 0; i < vibe_scores.size(); i++)
        max_vibe_score = max(max_vibe_score, vibe_scores[i]);

    cout << max_vibe_score << endl;

    return 0;
}