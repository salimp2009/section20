#include "DepthFirstSearch.hpp"

DepthFirstSearch::DepthFirstSearch(const std::vector<std::shared_ptr<Vertex>>& _vertexList)
                    : vertexList(_vertexList) { }
                    
void DepthFirstSearch::operator()() {
    // go thru list of vertex to check the neighbours of each vertex if visited or not
    // if the vertex is not visited we have to go thru the neighbours of that vertex
    // and check/set their Visited status
    
    for(auto& vertex :vertexList) {
        if(!vertex->isVisited())
        dfs(vertex);
    }
    
}

void DepthFirstSearch::dfs(std::shared_ptr<Vertex> vertex) {
    // display the visited vertex
    std::cout<<*vertex<<'\n';
    
    // go thru the neighbours of the visited vertex
    for(auto& v: vertex->getNeighbourList()) {
        if(!v->isVisited()) {           
            v->setVisited(true);            // if not visited, set it to visited
            dfs(v);                         // and thru its neighbours
        }
    }
}
    
void DepthFirstSearch::PrintVertices() const {
    for(const auto& vertex:vertexList) {
        std::cout<<*vertex<<'\n';
    }
    std::cout<<'\n';
}

