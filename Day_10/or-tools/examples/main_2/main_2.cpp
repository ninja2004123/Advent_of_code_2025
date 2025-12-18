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
#include <queue>

#include <cstdlib>
#include <memory>

#include "absl/base/log_severity.h"
#include "absl/log/globals.h"
#include "absl/log/log.h"
#include "ortools/base/init_google.h"
#include "ortools/init/init.h"
#include "ortools/linear_solver/linear_solver.h"

using namespace std;
using namespace operations_research;

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
        std::unique_ptr<operations_research::MPSolver> solver(operations_research::MPSolver::CreateSolver("SCIP"));
        if (!solver) {
            LOG(WARNING) << "SCIP solver unavailable.";
            return 1;
        }

        const double infinity = solver->infinity();
        map<char, operations_research::MPVariable*> variables;
        for (int i = 0; i < line.button_writing_schematics.size(); i++)
        {
            char name = 'A' + i;
            variables[name] = solver->MakeIntVar(0.0, infinity, to_string(name));
        }
        
        vector<operations_research::MPConstraint*> constraints;
        for (int i = 0; i < line.button_writing_schematics.size(); i++)
        {
            constraints.push_back(solver->MakeRowConstraint(0, infinity));
            char name = 'A' + i;
            constraints[constraints.size()-1]->SetCoefficient(variables[name], 1);
        }

        for (int i = line.joltage_requirements.size()-1; i >= 0; i--)
        {
            constraints.push_back(solver->MakeRowConstraint(line.joltage_requirements[i], line.joltage_requirements[i]));
            for (int j = 0; int button : line.button_writing_schematics)
            {
                char name = 'A' + j;
                constraints[constraints.size()-1]->SetCoefficient(variables[name], ((button >> i) & 1));
                j++;
            }
        }


        // // Objective function: 3x + 4y.
        operations_research::MPObjective* const objective = solver->MutableObjective();
        for (int i = 0; i < line.button_writing_schematics.size(); i++)
        {
            char name = 'A' + i;
            objective->SetCoefficient(variables[name], 1);
        }
        objective->SetMinimization();


        const operations_research::MPSolver::ResultStatus result_status = solver->Solve();
        // Check that the problem has an optimal solution.
        if (result_status != operations_research::MPSolver::OPTIMAL) {
            LOG(FATAL) << "The problem does not have an optimal solution!";
        }

        // cout << line.toString() << endl; 
        // LOG(INFO) << "Optimal objective value = " << objective->Value();
        min_total += objective->Value();
        for (int i = 0; i < line.button_writing_schematics.size(); i++)
        {
            char name = 'A' + i;
            objective->SetCoefficient(variables[name], 1);
        }

    }

    cout << min_total << endl;

    return 0;
}