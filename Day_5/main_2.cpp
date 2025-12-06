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
            pair<ll, ll> new_range = make_pair(
                stoll(input.substr(0, delimiter_pos)),
                stoll(input.substr(delimiter_pos+1, input.size() - delimiter_pos-1))
            );

            for (int i = 0; i < ranges.size(); i++)
            {
                // If range intercepts the left side of another range
                /*
                *            |----|      |-----|            |------|          |----------|
                *         |--------|         |-----|             |-----|        |-----|
                * */
                if ((new_range.first <= ranges[i].second && new_range.second >= ranges[i].first) || 
                    (new_range.second >= ranges[i].first && new_range.first <= ranges[i].second))
                {
                    new_range.first = min(ranges[i].first, new_range.first);
                    new_range.second = max(ranges[i].second, new_range.second);

                    // Hacking this, but it works. Make them so their difference is -1 so later in the calculation it comes out to 0.
                    ranges[i].first = -1;
                    ranges[i].second = -2;
                    
                    // Reset loop to fix missed ranges:
                    i = -1;
                }
            }

            ranges.push_back(new_range);
        }
    }

    for (auto range : ranges)
    {
        // cout << range.first << " " << range.second << "\t" << (range.second - range.first + 1) << endl;
        num_of_fresh_ingrediants += (range.second - range.first + 1);
    }

    cout << num_of_fresh_ingrediants << endl;

    return 0;
}
