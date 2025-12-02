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
    // 1010
    string number = to_string(i);
    for (int i = 1; i <= number.size() / 2; i++) {
        if (number.size() % i != 0)
            continue;

        bool is_invalid = true;
        string base = number.substr(0, i); // 10
        for (int j = 0; j <= number.size() - i; j += i)
        {
            if (number.substr(j, i) != base)
            {
                is_invalid = false;
                break;
            }
        }

        if (is_invalid)
            return true;
    }

    return false;
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