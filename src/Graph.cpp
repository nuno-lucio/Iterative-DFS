/**********
 * Graph representation
 * Author: Nuno Lucio
 **********/

#include "Graph.hpp"

unsigned int Graph::getNumberOfVertices() const
{
    return nVertices;
}

unsigned int Graph::getNumberOfEdges() const
{
    unsigned int nEdges = 0;

    for (auto adjacencies : adjacencyList)
    {
        nEdges += adjacencies.size();
    }

    return isDirected ? nEdges : (nEdges / 2);
}

const std::vector<Vertex>& Graph::getNeighbors(Vertex v) const
{
    return adjacencyList.at(v);
}

bool Graph::isDirectedGraph() const
{
    return isDirected;
}

void Graph::addEdge(Vertex from, Vertex to)
{
    adjacencyList[from].push_back(to);
    if(!isDirected) adjacencyList[to].push_back(from);
}

void Graph::removeEdge(Vertex from, Vertex to)
{
    for(std::vector<Vertex>::iterator it = adjacencyList[from].begin(); it != adjacencyList[from].end();)
    {
        if(*it == to)
        {
            it = adjacencyList[from].erase(it);
            continue;
        }

        it++;
    }

    if(!isDirected)
    {
        for(std::vector<Vertex>::iterator it = adjacencyList[to].begin(); it != adjacencyList[to].end();)
        {
            if(*it == from)
            {
                it = adjacencyList[to].erase(it);
                continue;
            }

            it++;
        }   
    }
}
