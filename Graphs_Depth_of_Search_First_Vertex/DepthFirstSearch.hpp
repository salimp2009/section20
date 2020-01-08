#ifndef _DEPTH_FIRST_SEARCH_H
#define _DEPTH_FIRST_SEARCH_H

#include "Vertex.hpp"
#include <memory>
#include <vector>

class DepthFirstSearch
{
    std::vector<std::shared_ptr<Vertex>> vertexList;
public:
    DepthFirstSearch(std::vector<std::shared_ptr<Vertex>> const& _vertexList);
    void operator()();
    void PrintVertices() const;
private:
    void dfs(Vertex* vertex);
    
};

#endif