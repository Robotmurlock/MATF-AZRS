#ifndef VORONOI
#define VORONOI

#include <cmath>
#include <vector>

#define MAX_DIST 111*sqrt(2) // >> 100*sqrt(2)

int randrange(int start, int end);

struct Point {
    const int x, y;
    const char label;

    Point(int x, int y, char l = '-')
        : x(x), y(y), label((l == '-') ? ('a' + randrange(0, 26)) : l)
    {}

    inline double distance(const Point& other) const
    {
        return sqrt(pow(x-other.y, 2) + pow(y-other.x, 2));
    }
};

class Specification {
private:
    const int m_seed;
public:
    const int id;

    Specification(int id, int seed)
        : m_seed(seed), id(id)
    {}

    std::pair<Point, std::vector<Point> > generate() const;
};

void voronoi(Specification &specification);

#endif // VORONOI
