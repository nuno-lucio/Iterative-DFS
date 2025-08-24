#include "GraphStdinFactory.hpp"

#include <iostream>

Graph GraphStdinFactory::createGraph()
{   
    return read(std::cin);
}
