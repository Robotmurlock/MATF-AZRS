#include "voronoi.hpp"
#include <fstream>

int randrange(int start, int end)
{
    return start + (rand() % (end-start));
}

std::pair<Point, std::vector<Point> > Specification::generate() const
{
    srand(m_seed);

    int n_points = randrange(3, 27);
    int xdim = randrange(10, 100);
    int ydim = std::min(std::max(xdim/2, randrange(10, 100)), 2*xdim);
    auto dim = Point(xdim, ydim);

    std::vector<Point> points;

    for(int i=0; i<n_points; i++)
        points.emplace_back(randrange(0, xdim), randrange(0, ydim), 'a'+i);

    return std::make_pair(dim, points);
}

void voronoi(Specification &specification)
{
    auto[dim, points] = specification.generate();

    std::vector<std::vector<char> > diagram(dim.x, std::vector<char>(dim.y, '.'));
    std::string file_name = "output" + std::to_string(specification.id);
    auto out = std::ofstream(file_name);

    for(int x=0; x<dim.x; x++)
    {
        for(int y=0; y<dim.y; y++)
        {
            Point curr_point(x, y);
            char best_label;
            double best_dist = MAX_DIST;
            for(auto& p: points)
            {
                double dist = curr_point.distance(p);
                if(dist <= best_dist)
                {
                    best_dist = dist;
                    best_label = curr_point.label;
                }
            }
            diagram[x][y] = best_label;
            out << best_label;
        }
        out << std::endl;
    }
}

