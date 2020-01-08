#ifndef _VERTEX_H
#define _VERTEX_H

#include <iostream>
#include <vector>
#include <string>

class Vertex
{
private:
    // every node has a name as data 
    std::string name;
    
    // track whether the node is visited or not; for searching and traversing
    bool visited{false};
    std::vector<Vertex*>neighbours;
public:
    Vertex(const std::string &name);
    //~Vertex();
    
    const std::string& getName() const;
    void setName(const std::string& name);
    
    // check whether visited or not
    bool isVisited() const;
    // change the status to visited
    void setVisited(bool visited);
    
    // add neighbours
    void addNeighbour(Vertex* neighbour);
    // get the Neighbourlist
    
    const std::vector<Vertex*>& getNeighbourList() const;
    
     friend std::ostream& operator<<(std::ostream& ost, const Vertex& vertex);
    
};

#endif // _VERTEX_H