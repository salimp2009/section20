#ifndef _MY_DEPTH_FIRST_SEARCH_H
#define _MY_DEPTH_FIRST_SEARCH_H

#include "Vertex.hpp"

class DepthFirstSearch
{
private:
    std::vector<std::shared_ptr<Vertex>> vertexList;
    void dfs(std::shared_ptr<Vertex> vertex);
public:
    DepthFirstSearch()=default;
    DepthFirstSearch(const std::vector<std::shared_ptr<Vertex>>& _vertexList);
    void operator()();
    void PrintVertices() const;
};

#endif // _MY_DEPTH_FIRST_SEARCH_H
