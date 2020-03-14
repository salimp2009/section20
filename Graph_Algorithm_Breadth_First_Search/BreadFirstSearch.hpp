#ifndef _MY_BREADTH_FIRST_SEARCH_H_
#define _MY_BREADTH_FIRST_SEARCH_H_

#include "Vertex.hpp"
#include <deque>



class BreadFirstSearch
{
public:
void operator()(std::shared_ptr<Vertex>root) const;

};

#endif // _MY_BREADTH_FIRST_SEARCH_H_
