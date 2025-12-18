#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
#include <cmath>
#include <string>
#include <stack>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>
#include <regex>

using namespace std;

#define ll long long
#define INPUT_FILE "input"

struct input_line {
    int light_indicator_diagram;
    vector<int> button_writing_schematics;
    vector<int> joltage_requirements;

    void set_light_indicator_diagram(string lid)
    {
        string indicators_as_str;

        smatch pattern_matches;
        regex digits_pattern("([.#]+)");
        if (regex_search(lid, pattern_matches, digits_pattern))
        {
            indicators_as_str = pattern_matches.str();
            reverse(indicators_as_str.begin(), indicators_as_str.end());
        }

        int indicator_as_binary = 0; 
        for (int i = 0; i < indicators_as_str.size(); i++)
        {
            indicator_as_binary <<= 1;
            indicator_as_binary = indicator_as_binary | (indicators_as_str[i] == '#' ? 1 : 0);
        }

        this->light_indicator_diagram = indicator_as_binary;
    }
    
    void set_button_writing_schematics(string bws)
    {
        regex button_pattern("(\\([\\d,]+\\))");
        sregex_iterator it(bws.begin(), bws.end(), button_pattern);
        sregex_iterator end; // Default-constructed iterator marks the end of the sequence

        while (it != end) {
            smatch match = *it; 
            string button = match.str();

            { // Abusing scopes to use existing variable names;
                int new_button_value = 0;

                regex digit_pattern("(\\d+)");
                sregex_iterator it(button.begin(), button.end(), digit_pattern);
                sregex_iterator end;
                while (it != end)
                {
                    smatch match = *it;
                    int digit = stoi(match.str());
                    
                    new_button_value |= (1 << digit); 

                    it++;
                }

                this->button_writing_schematics.push_back(new_button_value);
            }


            it++;
        }
    }
    
    void set_joltage_requirements(string jr)
    {
        int new_button_value = 0;

        regex digit_pattern("(\\d+)");
        sregex_iterator it(jr.begin(), jr.end(), digit_pattern);
        sregex_iterator end;
        while (it != end)
        {
            smatch match = *it;
            int digit = stoi(match.str());
            
            this->joltage_requirements.push_back(digit);

            it++;
        }
    }

    string toString()
    {
        string lid = "[" + to_string(light_indicator_diagram) + "]";

        string bws = "";
        for (int i = 0; i < button_writing_schematics.size(); i++)
        {
            bws += "(" + to_string(button_writing_schematics[i]) + ")";
            if (i != button_writing_schematics.size()-1)
                bws += " ";
        }

        string jr = "";
        jr += "{";
        for (int i = 0; i < joltage_requirements.size(); i++)
        {
            jr += to_string(joltage_requirements[i]); 
            if (i != joltage_requirements.size()-1)
                jr += ",";
        }
        jr += "}";

        return lid + " " + bws + " " + jr;
    }
};


int go_through_all_sets(vector<int> button_values, int n, int k, vector<int> picked, int target)
{
    if (k == 0)
    {
        int x = 0;
        for (auto i : picked)
            x ^= i;

        if (x == target)
            return picked.size();
    }
    else
    {
        for (int i = n; i <= button_values.size() - k; i++)
        {
            picked.push_back(button_values[i]);
            int res = go_through_all_sets(button_values, i+1, k-1, picked, target);
            if (res != INT32_MAX)
                return res;
            picked.pop_back();
        }
    }

    return INT32_MAX;
}


int main()
{
    ifstream inputFile;
    inputFile.open(INPUT_FILE);

    vector<input_line> lines;
    string l;
    while (getline(inputFile, l))
    {
        input_line line;

        smatch pattern_matches;

        // Process indicator:
        regex light_indicator_diagram_pattern("(\\[.+\\])");
        if (regex_search(l, pattern_matches, light_indicator_diagram_pattern))
        {
            line.set_light_indicator_diagram(pattern_matches[0]);
        }

        // Process buttons:
        regex button_writing_schematics_pattern("(\\(.+\\))");
        if (regex_search(l, pattern_matches, button_writing_schematics_pattern))
        {
            line.set_button_writing_schematics(pattern_matches[0]);
        }

        // Process Joltage:
        regex joltage_requirements_pattern("(\\{.+\\})");
        if (regex_search(l, pattern_matches, joltage_requirements_pattern))
        {
            line.set_joltage_requirements(pattern_matches[0]);
        }


        lines.push_back(line);
    }


    int min_total = 0;
    for (auto line : lines)
    {
        int res = INT32_MAX;
        for (int k = 1; k <= line.button_writing_schematics.size(); k++)
        {
            res = go_through_all_sets(line.button_writing_schematics, 0, k, vector<int>(), line.light_indicator_diagram);
            if (res != INT32_MAX)
            {
                min_total += res;
                break;
            }
        }

    }

    cout << min_total << endl;

    return 0;
}