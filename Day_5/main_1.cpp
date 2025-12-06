#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#define ll long long
#define DELIMITER '-'

int main() {
    ifstream inputFile;
    inputFile.open("input");

    ll num_of_fresh_ingrediants = 0;

    vector<pair<ll, ll>> ranges;

    string input;
    while (inputFile >> input)
    {
        // If it's a range
        int delimiter_pos = input.find(DELIMITER);
        if (delimiter_pos != string::npos)
        {
            ranges.push_back(make_pair(
                stol(input.substr(0, delimiter_pos)),
                stol(input.substr(delimiter_pos+1, input.size() - delimiter_pos-1))
            ));
        }
        else if (input.size() > 0)
        {
            ll ingredant_id = stol(input);    
            for (auto range : ranges)
            {
                if (range.second - ingredant_id >= 0 && ingredant_id - range.first >= 0)
                {
                    num_of_fresh_ingrediants++;
                    // cout << range.first << " " << ingredant_id << " " << range.second << endl;
                    break;
                }
            }
        }
    }

    cout << num_of_fresh_ingrediants << endl;

    return 0;
}