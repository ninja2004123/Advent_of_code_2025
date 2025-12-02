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

bool isRepeating(long long i) {
    string number = to_string(i);
    if (number.size() % 2 == 1)
        return false;

    return number.substr(0, number.size() / 2) == number.substr(number.size()/2, number.size()/2);
}

int main() {
    ifstream inputFile;
    inputFile.open("input");

    string rawInput;
    inputFile >> rawInput;
    vector<string> ranges = process_input(rawInput, ',');

    unsigned long long invalid = 0;
    for (auto range : ranges)
    {
        vector<string> start_end = process_input(range, '-');
        for (long long i = stol(start_end[0]); i <= stol(start_end[1]); i++) 
        {
            if (isRepeating(i))
            {
                invalid += i;
                cout << i << endl;
            }
        }
    }

    cout << invalid << endl;

    return 0;
}