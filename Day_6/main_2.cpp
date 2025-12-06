#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

#define ll long long

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

    ll grand_total = 0;
    ll section_total = 0;
    vector<ll> column;
    for (int col = 0; col < lines[0].size(); col++)
    {
        char operation;
        ll row_number = 0;
        for (int row = 0; row < lines.size(); row++)
        {
            if (lines[row][col] >= '0' && lines[row][col] <= '9')
            {
                row_number = row_number * 10 + (lines[row][col] - '0');
            }
            else if (lines[row][col] == '*' || lines[row][col] == '+')
            {
                operation = lines[row][col];
            }
        }
        
        if (row_number > 0)
            column.push_back(row_number);
        
        // Set of numbers has finished, add to grand total (This is why we added a space earlier)
        if (row_number == 0)
        {
            ll result = operation == '*' ? 1 : 0;
            for (auto number : column)
            {
                if (operation == '+')
                    result += number;
                else
                    result *= number;
            }

            grand_total += result;
            column.clear();
        }
    }

    cout << grand_total << endl;

    return 0;
}