#include <iostream> 
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

#define ll long long
#define INPUT_FILE "input"

vector<vector<string>> load_shapes();
vector<vector<int>> load_tasks();

struct shape_info
{
    int points;
    int width;
    int height;

    shape_info() {}

    shape_info(vector<string> shape)
    {
        this->points = 0;
        for (string row : shape)
        {
            for (char row_col : row)
            {
                if (row_col == '#')
                    this->points++;
            }
        }
        
        this->height = shape.size();
        this->width = shape[0].size();
    }
};

int main()
{
    vector<vector<string>> shapes = load_shapes();
    vector<shape_info> shapes_info;
    for (auto shape : shapes)
        shapes_info.push_back(shape_info(shape));

    vector<vector<int>> tasks = load_tasks();

    ll num_of_fits = 0;
    for (auto task : tasks)
    {
        ll area = task[0];

        ll upper_area = 0;
        ll total_points = 0;
        for (int i = 1; i < task.size(); i++)
        {
            total_points += (shapes_info[i-1].points * task[i]);
            upper_area = (task[i] * shapes_info[i-1].height * shapes_info[i-1].width);
        }

        bool satisfies_lower_bound = total_points <= area;
        bool satisfies_upper_bound = upper_area <= area;


        if (satisfies_lower_bound && satisfies_upper_bound)
            num_of_fits++;
    } 

    cout << num_of_fits << endl;

    return 0;
}


vector<vector<string>> load_shapes()
{
    return vector<vector<string>> {
        {"#.#", "###", "#.#"},
        {"###", ".##", "..#"},
        {".##", "##.", "#.."},
        {"###", "..#", "###"},
        {".##", "###", "#.#"},
        {"###", "###", "#.."}
    };
}

vector<vector<int>> load_tasks()
{
    vector<vector<int>> tasks;

    ifstream inputFile(INPUT_FILE);

    string line;
    string input_file_as_string;
    while (getline(inputFile, line))
    {
        vector<int> task;
        
        regex digit_pattern("(\\d+)");
        sregex_iterator it(line.begin(), line.end(), digit_pattern);
        sregex_iterator end; // Default-constructed iterator marks the end of the sequence
        
        // Basically calculates the area of the field it gets the first match, converts it to an integer, goes the the next match, does the same
        // and multipleisthe result.
        task.push_back(stoi((*(it++)).str()) * stoi((*(it++)).str()));
        while (it != end)
        {
            task.push_back(stoi((*it).str()));
            it++;
        }

        tasks.push_back(task);
    }

    return tasks;
}