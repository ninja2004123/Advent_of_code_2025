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
    int z;

    point() {}

    point(int a, int b, int c)
    {
        x = a;
        y = b;
        z = c;
    }

    bool operator<(const point& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }   

    bool operator==(const point& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }

    string toString()
    {
        return (to_string(x) + " " + to_string(y) + " " + to_string(z));
    }
};

struct relation {
    point A;
    point B;
    float distance;

    relation(point a, point b, float d)
    {
        A = a;
        B = b;
        distance = d;
    }
    
    string toString()
    {
        return (A.toString() + " <-> " + B.toString() + " = " + to_string(distance));
    }
};

vector<point> process_input(vector<string> rawInput, char delimiter);
vector<int> get_all_circuits(map<point, vector<point>> &graph);
float get_distance(point A, point B);

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
            relation new_relation(points[i], points[j], get_distance(points[i], points[j]));
            point_to_point_distances.push_back(new_relation);
        }
    }

    // Sort by distance in ascending
    sort(point_to_point_distances.begin(), point_to_point_distances.end(), [](relation a, relation b) {
        return a.distance < b.distance;
    });
    
    // Create graph of the shortest distances:
    map<point, vector<point>> graph;
    for (auto p : point_to_point_distances)
    {
        graph[p.A] = vector<point> ();
    }

    int next_shortest_index = 0;
    vector<int> circuits = get_all_circuits(graph);
    while (circuits.size() != 1)
    {
        graph[point_to_point_distances[next_shortest_index].A].push_back(point_to_point_distances[next_shortest_index].B);
        graph[point_to_point_distances[next_shortest_index].B].push_back(point_to_point_distances[next_shortest_index].A);
        next_shortest_index++;

        circuits = get_all_circuits(graph);
    }
    
    int x_product = point_to_point_distances[next_shortest_index-1].A.x *
                    point_to_point_distances[next_shortest_index-1].B.x;
    cout << x_product << endl;

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

        point new_point(stoi(coordinates[0]), stoi(coordinates[1]), stoi(coordinates[2]));
        points.push_back(new_point);
    }

    return points;
}

float get_distance(point A, point B)
{
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2) + pow(A.z - B.z, 2));
}


vector<int> get_all_circuits(map<point, vector<point>> &graph)
{
    vector<int> circuits;
    vector<point> visited;
    for (pair<point, vector<point>> p : graph)
    {
        if (find(visited.begin(), visited.end(), p.first) != visited.end()) 
            continue;

        stack<point> S;
        S.push(p.first);

        int length_of_circuit = 0;
        while (!S.empty())
        {
            point current = S.top();
            S.pop();

            if (find(visited.begin(), visited.end(), current) == visited.end())
            {
                length_of_circuit++;
                visited.push_back(current);

                for (point next : graph[current])
                    S.push(next);
            }
        }
        
        if (length_of_circuit > 0)
            circuits.push_back(length_of_circuit);
    }

    return circuits;
}