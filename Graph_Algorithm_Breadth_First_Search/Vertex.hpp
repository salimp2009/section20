#ifndef _MY_VERTEX_H_
#define _MY_VERTEX_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>


// every node represented by a Vertex
// with a name, a boolean visited or not, and a list of neighbours in a container
class Vertex
{
private:
    std::string name;
    // will be set to false as initial value
    bool visited;
    std::vector<std::shared_ptr<Vertex>>neighbours;
public:
    Vertex(std::string _name);

    const std::string& getName() const&;
    void setName(std::string name);
    
    bool isVisited() const;
    void setVisited(bool visited);

    void addNeighbour(std::shared_ptr<Vertex> neighbour);
    const std::vector<std::shared_ptr<Vertex>>& getNeighbourList() const&;
    
    friend std::ostream& operator<<(std::ostream& os, const Vertex& obj);
};

#endif // _MY_VERTEX_H_
