#include <string>

#define ll long long

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

    std::string toString()
    {
        return (std::to_string(x) + "," + std::to_string(y));
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
    
    std::string toString()
    {
        return (A.toString() + " <-> " + B.toString() + " = " + std::to_string(area));
    }
};

// Custom hash function for point
struct point_hash {
    size_t operator()(const point &p) const {
        // Combine hashes of first and second
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};