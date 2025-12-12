#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <stack>

using namespace std;

#define ll long long
#define DELIMITER ','
#define INPUT_FILE "input"

struct point {
    int x;
    int y;

    point() {}

    point(int a, int b)
    {
        x = a;
        y = b;
    }

    bool operator<(const point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }   

    bool operator==(const point& other) const {
        return (x == other.x && y == other.y);
    }

    string toString()
    {
        return (to_string(x) + " " + to_string(y));
    }
};

struct relation {
    point A;
    point B;
    ll area;

    relation(point a, point b, ll ar)
    {
        A = a;
        B = b;
        area = ar;
    }
    
    string toString()
    {
        return (A.toString() + " <-> " + B.toString() + " = " + to_string(area));
    }
};

vector<point> process_input(vector<string> rawInput, char delimiter);
ll get_area(point A, point B);

int main()
{
    ifstream inputFile;
    inputFile.open(INPUT_FILE);

    vector<string> lines;
    string line;
    while (getline(inputFile, line))
    {
        line;
        lines.push_back(line);
    }

    vector<point> points = process_input(lines, DELIMITER);

    // All distances:
    vector<relation> point_to_point_distances;
    
    // Find all Distances:
    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i+1; j < points.size(); j++)
        {
            relation new_relation(points[i], points[j], get_area(points[i], points[j]));
            point_to_point_distances.push_back(new_relation);
        }
    }

    // Sort by distance in ascending
    sort(point_to_point_distances.begin(), point_to_point_distances.end(), [](relation a, relation b) {
        return a.area >= b.area;
    });

    cout << point_to_point_distances[0].A.toString() << " <-> " << point_to_point_distances[0].B.toString() << " = " << point_to_point_distances[0].area << endl;

    int last = point_to_point_distances.size()-1;
    cout << point_to_point_distances[last].A.toString() << " <-> " << point_to_point_distances[last].B.toString() << " = " << point_to_point_distances[last].area << endl;

    return 0;
}

vector<point> process_input(vector<string> rawInput, char delimiter) {
    vector<point> points;

    for (string line : rawInput)
    {
        stringstream input(line);
        string segment;
        vector<string> coordinates;

        while (getline(input, segment, delimiter))
        {
            coordinates.push_back(segment);
        }

        point new_point(stoi(coordinates[0]), stoi(coordinates[1]));
        points.push_back(new_point);
    }

    return points;
}

ll get_area(point A, point B)
{
    return ((ll) abs(A.x - B.x)+1) * (ll) (abs(A.y - B.y)+1);
}