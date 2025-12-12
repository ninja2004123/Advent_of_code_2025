#include <algorithm>
#include <chrono>
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
vector<point> connect_points(vector<point> &points);
ll get_area(point A, point B);
bool is_point_inside(vector<point> &points, point p);

int main(int argc, char *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();


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
    
    vector<point> all_points = connect_points(points);
   

    sort(points.begin(), points.end());
    
    if (argc > 1 && string(argv[1]) == "--debug")
    {
        for (auto point : points)
        {
            cout << point.x << " " << point.y;
            cout << endl;
        }
    }

    // Find all Distances:
    vector<relation> point_to_point_distances;
    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i+1; j < points.size(); j++)
        {
            relation new_relation(points[i], points[j], get_area(points[i], points[j]));

            bool is_inside = true;
            for (int x = min(points[i].x, points[j].x); x <= max(points[i].x, points[j].x); x++)
            {
                if (!is_point_inside(all_points, point(x, points[i].y)) || !is_point_inside(all_points, point(x, points[j].y)))
                {
                    is_inside = false;
                    break;
                }
            }

            for (int y = min(points[i].y, points[j].y); y <= max(points[i].y, points[j].y); y++)
            {
                if (!is_point_inside(all_points, point(points[i].x, y)) || !is_point_inside(all_points, point(points[j].x, y)))
                {
                    is_inside = false;
                    break;
                }
            }

            if (is_inside)
            {
                point_to_point_distances.push_back(new_relation);
            }
        }
    }

    // Sort by distance in ascending
    sort(point_to_point_distances.begin(), point_to_point_distances.end(), [](relation a, relation b) {
        return a.area >= b.area;
    });

    // for (auto ppd : point_to_point_distances)
    // {
    //     cout << ppd.area << endl;
    // }

    cout << point_to_point_distances[0].area << endl;

        auto end = std::chrono::high_resolution_clock::now();

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

vector<point> connect_points(vector<point> &points)
{
    vector<point> connected_points = points;

    // Connect Rows:
    sort(points.begin(), points.end(), [](point a, point b){ return a.y < b.y; });
    for (int x = 0; x < 100000; x++) {
        auto it = points.begin();
        int before = INT32_MAX-1;
        while ((it = find_if(it, points.end(), [x](point a){ return a.x == x; })) != points.end())
        {
            for (int y = before+1; y <= (*it).y-1; y++)
                connected_points.push_back(point(x, y));

            before = (*it).y;
            it++;
        }
    }

    // Connect Cols:
    sort(points.begin(), points.end(), [](point a, point b){ return a.x < b.x; });
    for (int y = 0; y < 100000; y++) {
        auto it = points.begin();
        int before = INT32_MAX-1;
        while ((it = find_if(it, points.end(), [y](point a){ return a.y == y; })) != points.end())
        {
            for (int x = before+1; x <= (*it).x-1; x++)
                connected_points.push_back(point(x, y));

            before = (*it).x;
            it++;
        }
    }

    return connected_points;
}

bool is_point_inside(vector<point> &points, point p)
{
    // if (find(points.begin(), points.end(), p) != points.end())
    //     return true;

    // auto min_it_x = min_element(points.begin(), points.end(), [](point a, point b){ return a.x < b.x; });

    // int count = 0;
    // for (int x = (*min_it_x).x; x < p.x; x++)
    // {
    //     if (find(points.begin(), points.end(), point(x, p.y)) != points.end())
    //     {
    //         count++;
    //     }
    // }

    // return count % 2 != 0;
    return true;
}