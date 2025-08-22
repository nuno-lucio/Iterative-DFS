/**********
 * Iterative Depth-First-Search (DFS)
 * Author: Nuno Lucio
 **********/

#include <iostream>
#include <vector>
#include <stack>
#include <limits>

using Vertex = unsigned int;
using Index = unsigned int;

constexpr unsigned int START_VERTEX = 0;
constexpr unsigned int NOT_VISITED = 0;
constexpr unsigned int START_INDEX = 0;
constexpr unsigned int NO_PARENT = std::numeric_limits<Vertex>::max();

struct DFSframe
{
    Vertex vertex;
    Index nextNeighborIndex;
};

using Graph = std::vector<std::vector<unsigned int>>;
using Times = std::vector<unsigned int>;
using Parents = std::vector<Vertex>;
using Stack = std::stack<DFSframe>;

struct DFScontext
{
    unsigned int nVertices, nAdjacencyList;
    Graph graph;
    Times visited_times, final_times;
    Parents parents;
};

void DFS_Visit(DFScontext &dfs, Stack &stack, unsigned int &current_time)
{
    while(!stack.empty())
    {
        unsigned int vertex = stack.top().vertex;
        unsigned int nextNeighborIndex = stack.top().nextNeighborIndex;
        stack.pop();
        
        if(dfs.visited_times[vertex] == NOT_VISITED)
        {
            current_time++;
            dfs.visited_times[vertex] = current_time;
        }

        if(nextNeighborIndex < dfs.graph[vertex].size())
        {
            // Push current vertex to stack to continue to next neighbor
            DFSframe frame;
            frame.vertex = vertex;
            frame.nextNeighborIndex = nextNeighborIndex + 1;
            stack.push(frame);

            int neighbor = dfs.graph[vertex][nextNeighborIndex];

            if(dfs.visited_times[neighbor] == 0)
            {
                // Visit current neighbor
                dfs.parents[neighbor] = vertex;
                frame.vertex = neighbor;
                frame.nextNeighborIndex = START_INDEX;
                stack.push(frame);
            }
        }
        else
        {
            current_time++;
            dfs.final_times[vertex] = current_time;
        }
    }
}

void DFS(DFScontext &dfs, unsigned int startVertex)
{
    Stack stack;
    DFSframe frame;
    unsigned int current_time = 0;
    
    // Initiliaze
    dfs.visited_times.assign(dfs.nVertices, NOT_VISITED);
    dfs.final_times.assign(dfs.nVertices, NOT_VISITED);
    dfs.parents.assign(dfs.nVertices, NO_PARENT);
    
    // Start at initial vertex
    frame.vertex = startVertex;
    frame.nextNeighborIndex = START_INDEX;
    stack.push(frame);

    DFS_Visit(dfs, stack, current_time);

    // Check unexplored vertices
    for (size_t v = 0; v < dfs.nVertices; v++)
    {
        if(dfs.visited_times[v] == 0)
        {
            frame.vertex = v;
            frame.nextNeighborIndex = START_INDEX;
            stack.push(frame);
            DFS_Visit(dfs, stack, current_time);
        }
    }
}

/**
 * Reads 0 indexed graphs from stdin with the adjacency list format:
 * First Line -> "numberOfVertices numberOfVerticesWithAdjacencies
 * Second Line -> "VertexID Degree"
 * Third Line -> "Neighbor1 Neighbor2 Neighbor3 ..."
 * Second and third lines repeat for each vertex with adjacencies on the graph until EOF.
 */
void readGraph(DFScontext &dfs)
{
    std::cin >> dfs.nVertices >> dfs.nAdjacencyList;
    dfs.graph.resize(dfs.nVertices, std::vector<unsigned int>());
    
    for (size_t i = 0; i < dfs.nAdjacencyList; i++)
    {
        unsigned int current_vertex, vertex_degree;
        std::cin >> current_vertex >> vertex_degree;

        for (size_t j = 0; j < vertex_degree; j++)
        {
            unsigned int current_edge;
            std::cin >> current_edge;
            dfs.graph[current_vertex].push_back(current_edge);
        }   
    }
}

/**
 * Print results to stdout.
 */
void results(DFScontext &dfs)
{
    std::cout << "Discovery Times: " << std::endl;
    for (size_t i = 0; i < dfs.nVertices; i++)
    {
        std::cout << i << " ---> " << dfs.visited_times[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Final Times: " << std::endl;
    for (size_t i = 0; i < dfs.nVertices; i++)
    {
        std::cout << i << " ---> " << dfs.final_times[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Parents: " << std::endl;
    for (size_t i = 0; i < dfs.nVertices; i++)
    {
        if(dfs.parents[i] == NO_PARENT)
        {
            std::cout << i << " ---> " << "None" << std::endl;
        }
        else
        {
            std::cout << i << " ---> " << dfs.parents[i] << std::endl;
        }        
    }
}

int main(int argc, char const *argv[])
{
    DFScontext dfs;

    readGraph(dfs);
    DFS(dfs, START_VERTEX);
    results(dfs);

    return 0;
}
