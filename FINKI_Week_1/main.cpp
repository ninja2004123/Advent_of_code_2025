#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> process_input(string rawInput, char delimiter) {
    stringstream input(rawInput);
    string segment;
    vector<string> ranges;

    while (getline(input, segment, delimiter))
    {
        ranges.push_back(segment);
    }

    return ranges;
}

int main() {
    ifstream inputFile;
    inputFile.open("input");

    int K;
    inputFile >> K;

    string rawInput;
    inputFile >> rawInput;
    vector<string> friendliness_scores_string = process_input(rawInput, ',');

    vector<int> friendliness_scores;
    for (auto i : friendliness_scores_string)
        friendliness_scores.push_back(stoi(i));

    sort(friendliness_scores.begin(), friendliness_scores.end());

    long long max_size = 0;
    long long i = 0, j = 0;
    while (true) {
        // Passed the list:
        if (j >= friendliness_scores.size())
            break;

        // Has only one element:
        if (i == j)
        {
            j++;
            continue;
        }

        if (friendliness_scores[j] - friendliness_scores[i] <= K)
        {
            max_size = max(max_size, j - i + 1);
            j++;
        }
        else
        {
            i++;
        }
    }

    cout << max_size << endl;

    return 0;
}