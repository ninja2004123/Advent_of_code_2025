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
#include <unordered_set>
#include <queue>
#include "point.hpp"

using namespace std;

#define ll long long
#define DELIMITER ','
#define INPUT_FILE "input"

vector<point> process_input();
vector<point> compress_points(vector<point> &points);
unordered_set<point, point_hash> connect_points(vector<point> &points);
ll get_area(point A, point B);
void fill_in_pollygon(unordered_set<point, point_hash> &points);
point get_first_inside_point(unordered_set<point, point_hash> &points);
vector<relation> find_valid_rectangles(vector<point> &points, unordered_set<point, point_hash> &all_points);
bool is_point_inside(unordered_set<point, point_hash> &points, point p);

int main(int argc, char *argv[])
{
    vector<point> points = process_input();

    vector<point> compressed_points = compress_points(points);

    unordered_set<point, point_hash> connected_compressed_points = connect_points(compressed_points);

    fill_in_pollygon(connected_compressed_points);

    vector<relation> point_to_point_distances = find_valid_rectangles(compressed_points, connected_compressed_points);

    ll max_area = INT64_MIN;
    for (auto r : point_to_point_distances)
    {
        relation biggest_rectangle = r;
        point original_A, original_B;
        for (int i = 0; i < compressed_points.size(); i++)
        {
            if (biggest_rectangle.A == compressed_points[i])
                original_A = points[i];
            else if (biggest_rectangle.B == compressed_points[i])
                original_B = points[i];
        }

        max_area = max(max_area, get_area(original_A, original_B));
    }

    cout << "Max Area: " << max_area << endl;
    return 0;
}

vector<point> process_input() {
    vector<point> points;

    ifstream inputFile;
    inputFile.open(INPUT_FILE);

    vector<string> lines;
    string line;
    while (getline(inputFile, line))
    {
        stringstream input(line);
        string segment;

        vector<string> coordinates;
        while (getline(input, segment, ','))
        {
            coordinates.push_back(segment);
        }

        point new_point(stoi(coordinates[0]), stoi(coordinates[1]));
        points.push_back(new_point);
    }

    return points;
}

vector<point> compress_points(vector<point> &points)
{
    set<int> compressed_x_set;
    set<int> compressed_y_set;
    for (auto p : points)
    {
        compressed_x_set.insert(p.x);
        compressed_y_set.insert(p.y);
    }

    map<int, int> compressed_x_map;
    for (int i = 0; int x : compressed_x_set)
    {
        compressed_x_map[x] = i;
        i++;
    }
    
    map<int, int> compressed_y_map;
    for (int i = 0; int y : compressed_y_set)
    {
        compressed_y_map[y] = i;
        i++;
    }

    vector<point> compressed_points;
    for (auto p : points)
    {
        point compressed_point = point(compressed_x_map[p.x], compressed_y_map[p.y]);
        compressed_points.push_back(compressed_point);
    }

    return compressed_points;
}

// Gipster helped here. Had some small bug, but it's 5 am, I couldn't deal with it anymore lol.
unordered_set<point, point_hash> connect_points(vector<point> &points)
{
    unordered_set<point, point_hash> connected_points;

    // Insert original points
    for (auto &p : points)
        connected_points.insert(p);

    // Group points by X (columns)
    unordered_map<int, vector<int>> by_x;
    // Group points by Y (rows)
    unordered_map<int, vector<int>> by_y;

    for (auto &p : points) {
        by_x[p.x].push_back(p.y);
        by_y[p.y].push_back(p.x);
    }

    // Fill vertical gaps (same x, varying y)
    for (auto &[x, ys] : by_x) {
        sort(ys.begin(), ys.end());
        for (int i = 1; i < ys.size(); i++) {
            for (int y = ys[i - 1] + 1; y < ys[i]; y++) {
                connected_points.insert(point(x, y));
            }
        }
    }

    // Fill horizontal gaps (same y, varying x)
    for (auto &[y, xs] : by_y) {
        sort(xs.begin(), xs.end());
        for (int i = 1; i < xs.size(); i++) {
            for (int x = xs[i - 1] + 1; x < xs[i]; x++) {
                connected_points.insert(point(x, y));
            }
        }
    }

    return connected_points;
}

ll get_area(point A, point B)
{
    return ((ll) abs(A.x - B.x)+1) * (ll) (abs(A.y - B.y)+1);
}

void fill_in_pollygon(unordered_set<point, point_hash> &points)
{
    queue<point> queue;
    queue.push(get_first_inside_point(points));
    
    while (!queue.empty())
    {
        point current = queue.front();
        queue.pop();

        if (points.find(current) != points.end())
            continue;
        
        points.insert(current);

        vector<point> neighbourds = {
            point(current.x+1, current.y),
            point(current.x-1, current.y),
            point(current.x, current.y+1),
            point(current.x, current.y-1),
        };

        for (point next : neighbourds)
        {
            queue.push(next);
        }
    }
}

point get_first_inside_point(unordered_set<point, point_hash> &points)
{
    auto min_it_x = min_element(points.begin(), points.end(), [](point a, point b){ return a.x < b.x; });

    point inside_point = *min_it_x;
    while (points.find(inside_point) != points.end())
    {
        inside_point.x++;
    }
    
    return inside_point;
}

vector<relation> find_valid_rectangles(vector<point> &points, unordered_set<point, point_hash> &all_points)
{
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

            if (!is_inside)
                continue;

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

    return point_to_point_distances;
}

bool is_point_inside(unordered_set<point, point_hash> &points, point p)
{
    if (points.find(p) != points.end())
        return true;
    return false;
}