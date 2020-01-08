#ifndef _BREADTHFIRSTSEARCH_H
#define _BREADTHFIRSTSEARCH_H

#include "Vertex.hpp"
#include <deque>
#include <memory>

class BreadFirstSearch
{
public:
    void operator()(std::shared_ptr<Vertex>root) const;
    
};

#endif // _BREADTHFIRSTSEARCH_H