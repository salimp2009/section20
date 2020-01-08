#include "Vertex.hpp"

    Vertex::Vertex(const std::string & _name): name{_name}, visited{false} { }
    //Vertex::~Vertex() {std::cout<<"Vertex destructor called\n";}
    
    const std::string& Vertex::getName() const { return name;}
    
    void Vertex::setName(const std::string& _name) {this->name=_name;}
    
    // check whether visited or not
    bool Vertex::isVisited() const
    {
        return visited;
    }
    // change the status to visited
    void Vertex::setVisited(bool visited)
    {
        this->visited=visited;
    }
    
    void Vertex::addNeighbour(Vertex* neighbour)
    {
        neighbours.push_back(neighbour);
    }
    
    const std::vector<Vertex*>& Vertex::getNeighbourList() const
    {
        return neighbours;
    }
    
    // print the name of each vertex; we can add to print the neıghbour or any other data
    std::ostream& operator<<(std::ostream& ost, const Vertex& vertex)
    {
        ost<<vertex.name<<'\n';
        return ost;
    }
    