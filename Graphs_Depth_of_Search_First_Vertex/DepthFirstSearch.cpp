#include "DepthFirstSearch.hpp"

    
// std::vector<std::shared_ptr<Vertex>> vertexList;

DepthFirstSearch::DepthFirstSearch(std::vector<std::shared_ptr<Vertex>> const& _vertexList)
                  :vertexList{_vertexList}  { }
                  
void DepthFirstSearch::operator()()
{
    for(auto& vertex : vertexList)  // go thru the list of Vertexes
    {
        if(!vertex->isVisited())  // if the Vertex is not visited
            dfs(vertex.get());
    // go to dfs() to go thru the neighbours; vertex.get() return a raw pointer
    }
    
    std::cout<<'\n';
}


void DepthFirstSearch::PrintVertices() const
{
    for(const auto& vertex: vertexList) 
    {
        std::cout<<*vertex<<'\n';
    }

}

void DepthFirstSearch::dfs(Vertex* vertex)
{
        std::cout<<*vertex<<'\n';
        
        for(Vertex* v : vertex->getNeighbourList()) 
        {
            if(!v->isVisited())
                v->setVisited(true);
                dfs(v);
        }

}


