#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

pair<int, char> max_digit_in_range(string battery_bank, int start_index, int batteries_left)
{
    int max_index = start_index;
    char max_char = battery_bank[max_index];
    for (int i = max_index+1; i < battery_bank.size()-batteries_left; i++)
    {
        if (battery_bank[i] > max_char)
        {
            max_index = i;
            max_char = battery_bank[i];
        }
    }
    
    return make_pair(max_index+1, max_char);
}

int main() {
    ifstream inputFile;
    inputFile.open("input");

    long long total_output_joltage = 0;

    string battery_bank;
    while (inputFile >> battery_bank)
    {
        long long current_joltage = 0;
        pair<int, char> max_index_max_char = make_pair(0, '0');
        for (int i = 11; i >= 0; i--)
        {
            max_index_max_char = max_digit_in_range(battery_bank, max_index_max_char.first, i);
            current_joltage = current_joltage * 10 + (max_index_max_char.second - '0');
        }

        cout << current_joltage << endl;
        total_output_joltage += current_joltage;
    }

    cout << total_output_joltage << endl;

    return 0;
}