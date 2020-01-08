#include <iostream>
#include "Vertex.hpp"
#include "BreadFirstSearch.hpp"


int main()
{
    
    BreadFirstSearch breadfirstsearch;
    
    std::shared_ptr<Vertex> vertex1 = std::make_shared<Vertex>("A");
    std::shared_ptr<Vertex> vertex2 = std::make_shared<Vertex>("B");
    std::shared_ptr<Vertex> vertex3 = std::make_shared<Vertex>("C");
    std::shared_ptr<Vertex> vertex4 = std::make_shared<Vertex>("D");
    std::shared_ptr<Vertex> vertex5 = std::make_shared<Vertex>("E");
    std::shared_ptr<Vertex> vertex6 = std::make_shared<Vertex>("F");
    std::shared_ptr<Vertex> vertex7 = std::make_shared<Vertex>("G");
    std::shared_ptr<Vertex> vertex8 = std::make_shared<Vertex>("H");
    
    vertex1->addNeighbour(vertex2.get());
    vertex1->addNeighbour(vertex6.get());
    vertex1->addNeighbour(vertex7.get());
    
    vertex7->addNeighbour(vertex8.get());
    
    vertex2->addNeighbour(vertex3.get());
    vertex2->addNeighbour(vertex4.get());
    
    vertex4->addNeighbour(vertex5.get());
    
   breadfirstsearch(vertex1);
 
 return 0;
}