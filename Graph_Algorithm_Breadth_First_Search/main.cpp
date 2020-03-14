#include <iostream>
#include "Vertex.hpp"
#include "BreadFirstSearch.hpp"

int main()
{
    auto vertex1=std::make_shared<Vertex>("A");
    auto vertex2=std::make_shared<Vertex>("B");
    auto vertex3=std::make_shared<Vertex>("C");
    auto vertex4=std::make_shared<Vertex>("D");
    auto vertex5=std::make_shared<Vertex>("E");
    auto vertex6=std::make_shared<Vertex>("F");
    auto vertex7=std::make_shared<Vertex>("G");
    auto vertex8=std::make_shared<Vertex>("H");
    
    vertex1->addNeighbour(vertex2);
    vertex1->addNeighbour(vertex6);
    vertex1->addNeighbour(vertex7);
    
    vertex7->addNeighbour(vertex8);
    
    vertex2->addNeighbour(vertex3);
    vertex2->addNeighbour(vertex4);
    
    vertex4->addNeighbour(vertex5);
    
    BreadFirstSearch bdfSearch;
    bdfSearch(vertex1);
    
    
    return 0;
}
