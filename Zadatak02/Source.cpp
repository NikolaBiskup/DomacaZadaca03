#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <queue>
#include <iterator>
#include <limits> 
#include <thread>
#include <utility>
using namespace std;

const int ROW = 20;
typedef double Weight_T;
typedef int Vertex_T;

const Weight_T MAX_Weight = std::numeric_limits<double>::infinity();

struct Koordinata {

    int x, y;
};

struct Neighbor {
    Vertex_T target;
    Weight_T weight;
    Neighbor(Vertex_T arg_target, Weight_T arg_weight)
        : target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<Neighbor> > Adjacency_List_t;
typedef std::pair<Weight_T, Vertex_T> weight_vertex_pair_t;

void DijkstraComputePaths(Vertex_T source,
    const Adjacency_List_t& adjacency_list,
    std::vector<Weight_T>& min_distance,
    std::vector<Vertex_T>& previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, MAX_Weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);

    std::priority_queue<weight_vertex_pair_t,
        std::vector<weight_vertex_pair_t>,
        std::greater<weight_vertex_pair_t> > vertex_queue;
    vertex_queue.push(std::make_pair(min_distance[source], source));

    while (!vertex_queue.empty())
    {
        Weight_T dist = vertex_queue.top().first;
        Vertex_T u = vertex_queue.top().second;
        vertex_queue.pop();

        if (dist > min_distance[u])
            continue;

        const std::vector<Neighbor>& Neighbors = adjacency_list[u];
        for (std::vector<Neighbor>::const_iterator Neighbor_iter = Neighbors.begin();
            Neighbor_iter != Neighbors.end();
            Neighbor_iter++)
        {
            Vertex_T v = Neighbor_iter->target;
            Weight_T weight = Neighbor_iter->weight;
            Weight_T distance_through_u = dist + weight;
            if (distance_through_u < min_distance[v]) {
                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.push(std::make_pair(min_distance[v], v));

            }

        }
    }
}

void Arranging_Players(int path, char grid[ROW][ROW]) {

    int x = path;
    int y = path / 20;
    int initially = 0;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < ROW; j++)
        {
            if (x == initially && y == i)
            {
                cout << "*";
                initially++;

            }
            else
            {
                cout << grid[i][j] << " ";
                initially++;
            }
        }
        cout << endl;
    }
}

void Drawing(char grid[ROW][ROW]) {
    for (size_t i = 0; i < ROW; i++)
    {
        for (size_t j = 0; j < ROW; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

std::list<Vertex_T> DijkstraGetShortestPathTo(
    Vertex_T vertex, const std::vector<Vertex_T>& previous)
{
    std::list<Vertex_T> path;
    for (; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}


int main()
{
    Adjacency_List_t adjacency_list(ROW * ROW);

    int A[2];
    int B[2];

    std::cout << "Insert A (X): ";
    std::cin >> A[0];
    std::cout << "Insert A (Y): ";
    std::cin >> A[1];
    cout << endl;
    std::cout << "Insert B (X): ";
    std::cin >> B[0];
    std::cout << "Insert B (Y): ";
    std::cin >> B[1];

    char grid[ROW][ROW];

    for (int i = 0; i < ROW; i++)
    {

        for (int j = 0; j < ROW; j++)
        {
            if (A[0] - 1 == j && A[1] - 1 == i)
            {
                grid[i][j] = 'A';
            }
            else if (B[0] - 1 == j && B[1] - 1 == i)
            {
                grid[i][j] = 'B';
            }
            else if ((j == 9 && i == 0) || (j == 9 && i == 1) || (j == 9 && i == 2) || (j == 9 && i == 3) || (j == 9 && i == 4) || (j == 9 && i == 5))
            {
                grid[i][j] = '#';
            }
            else
            {
                grid[i][j] = '-';
            }
        }

    }

    Drawing(grid);

    std::cout << std::endl;

    for (size_t i = 0; i < adjacency_list.size(); i++)
    {
        if (i == 9 || i == 29 || i == 49 || i == 69 || i == 89 || i == 109)
        {
            adjacency_list[i].push_back(Neighbor(i, 99));
        }
        else
        {
            for (int j : { -1, 1 }) {

                if (i % ROW == 0)
                {
                    if (j == 1)
                    {
                        adjacency_list[i].push_back(Neighbor(i + j, 1));
                    }
                }
                else if (i % ROW == ROW - 1)
                {
                    if (j == -1)
                    {
                        adjacency_list[i].push_back(Neighbor(i + j, 1));
                    }
                }
                else
                {
                    adjacency_list[i].push_back(Neighbor(i + j, 1));

                }
                int v = j * ROW;

                if (v + i >= 0 && v + i < adjacency_list.size())
                {
                    adjacency_list[i].push_back(Neighbor(v + i, 1));
                }
            }
        }

    }

    int pathTo;
    int from;

    from = (((A[1] - 1) * ROW) + A[0] - 1);
    pathTo = (((B[1] - 1) * ROW) + B[0] - 1);

    std::vector<Weight_T> min_distance;
    std::vector<Vertex_T> previous;
    DijkstraComputePaths(from, adjacency_list, min_distance, previous);
    std::cout << "Distance from 0 to " << pathTo << ": " << min_distance[pathTo] << std::endl;
    std::list<Vertex_T> path = DijkstraGetShortestPathTo(pathTo, previous);
    std::cout << "Path : ";
    std::copy(path.begin(), path.end(), std::ostream_iterator<Vertex_T>(std::cout, " "));
    std::cout << std::endl;

    for (auto it = path.begin(); it != path.end(); ++it)
    {
        cout << endl << endl;
        this_thread::sleep_for(chrono::milliseconds(150));
        system("cls");
        int v = *it;
        Arranging_Players(v, grid);
    }

    return 0;
}