#ifndef GRAPH_FILE_FACTORY_HPP
#define GRAPH_FILE_FACTORY_HPP

#include "GraphFactory.hpp"
#include <string>

class GraphFileFactory : public GraphFactory
{
    private:
    std::string filename;

    public:
    explicit GraphFileFactory(const std::string &filename) : filename(std::move(filename)) {}
    Graph createGraph() override;
};

#endif // GRAPH_FILE_FACTORY_HPP
