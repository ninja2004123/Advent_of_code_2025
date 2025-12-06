#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#define ll long long

int main() {
    ifstream inputFile;
    inputFile.open("input");

    ll grand_total = 0;

    vector<ll> numbers;
    vector<char> operations;

    string input;
    while (inputFile >> input)
    {
        try
        {
            numbers.push_back(stoll(input));
        }
        catch(std::invalid_argument)
        {
            operations.push_back(input[0]);
        }
    }

    for (int i = 0; i < operations.size(); i++)
    {
        ll result = operations[i] == '+' ? 0 : 1;
        for (int j = i; j < numbers.size(); j += operations.size())
        {
            if (operations[i] == '+')
                result += numbers[j]; 
            else
                result *= numbers[j];
        }

        grand_total += result;
    }

    cout << grand_total << endl;

    return 0;
}