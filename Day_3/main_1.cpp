#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile;
    inputFile.open("input");

    long long total_output_joltage = 0;

    string battery_bank;
    while (inputFile >> battery_bank)
    {
        int max_left_index = 0;
        char max_left_char = battery_bank[max_left_index]; 
        for (int i = 0; i < battery_bank.size()-1; i++)
        {
            if (battery_bank[i] > max_left_char)
            {
                max_left_index = i;
                max_left_char = battery_bank[i];
            }
        }

        int max_right_index = battery_bank.size() - 1; // Last Character
        char max_right_char = battery_bank[max_right_index];
        for (int i = max_left_index+1; i <= battery_bank.size(); i++)
        {
            if (battery_bank[i] > max_right_char)
            {
                max_right_index = i;
                max_right_char = battery_bank[i];
            }
        }

        total_output_joltage += 10 * (max_left_char - '0') + (max_right_char - '0');
    }

    cout << total_output_joltage << endl;

    return 0;
}