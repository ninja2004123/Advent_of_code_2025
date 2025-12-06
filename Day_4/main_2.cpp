#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#define ll long long
#define NO_BOX '-'
#define BOX '@'
#define BEFORE_REMOVAL '#'
#define LIMIT 4

vector<vector<char>> get_grid_from_input(ifstream &inFile);
int get_number_of_accessible_boxes(vector<vector<char>> &grid);
void remove_boxes(vector<vector<char>> &grid);

int main() {
    ifstream inputFile;
    inputFile.open("input");

    ll num_of_boxes = 0;

    vector<vector<char>> grid = get_grid_from_input(inputFile);

    ll round_num_of_boxes = get_number_of_accessible_boxes(grid);
    while (round_num_of_boxes > 0)
    {
        num_of_boxes += round_num_of_boxes;
        round_num_of_boxes = get_number_of_accessible_boxes(grid);
        remove_boxes(grid);
    }

    cout << num_of_boxes << endl;

    return 0;
}

vector<vector<char>> get_grid_from_input(ifstream &inFile)
{
    vector<vector<char>> grid;

    string line;
    while (inFile >> line)
    {
        vector<char> row;
        for (auto character : line)
            row.push_back(character);

        grid.push_back(row);
    }
    
    return grid;
}

int get_number_of_accessible_boxes(vector<vector<char>> &grid)
{
    int num_of_boxes = 0;
    for (int row = 0; row < grid.size(); row++)
    {
        for (int col = 0; col < grid[0].size(); col++)
        {
            if (grid[row][col] == BOX)
            {
                int adjesent = 0;
                for (int i = row-1; i <= row+1; i++)
                {
                    for (int j = col-1; j <= col+1; j++)
                    {
                        if (i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size() && (i != row || j != col) && grid[i][j] == BOX)
                            adjesent++;
                    }
                }

                if (adjesent < LIMIT)
                {
                    grid[row][col] = BEFORE_REMOVAL;
                    num_of_boxes++;
                }
            }
        }
    }

    return num_of_boxes;
}

void remove_boxes(vector<vector<char>> &grid)
{
    for (int row = 0; row < grid.size(); row++)
    {
        for (int col = 0; col < grid[0].size(); col++)
        {
            if (grid[row][col] == BEFORE_REMOVAL)
                grid[row][col] = NO_BOX;
        }
    }
}