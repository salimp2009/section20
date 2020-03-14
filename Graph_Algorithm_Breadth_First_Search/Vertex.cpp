#include "Vertex.hpp"

Vertex::Vertex(std::string _name): name{std::move(_name)}, visited{false}, neighbours{} 
                                 { neighbours.reserve(100); }
    
const std::string& Vertex::getName() const& { return name;}
    
void Vertex::setName(std::string name) {this->name=std::move(name);}
    
bool Vertex::isVisited() const { return visited;}

void Vertex::setVisited(bool visited) {this->visited=visited;}

void Vertex::addNeighbour(std::shared_ptr<Vertex> neighbour) {
    neighbours.push_back(neighbour);
}

const std::vector<std::shared_ptr<Vertex>>& Vertex::getNeighbourList() const& {
    return neighbours; 
 }
    
std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
    return os<<"Node: "<<vertex.name;
}

