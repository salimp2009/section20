#include "BreadFirstSearch.hpp"

void BreadFirstSearch::operator()(std::shared_ptr<Vertex>root) const
{
    // BFO needs a FIFO type structure; queue used std::deque as a default container
    std::deque<Vertex*>queue;
    
    // start with the root node;
    root->setVisited(true);
    
    // add the root node into queue ; root.get() return the raw pointer that shared_ptr manages
    queue.push_back(root.get());
    
    while(!queue.empty())
    {
        // get the first item inserted into queue;
        Vertex* actualVertex=queue.front();
        queue.pop_front();
        std::cout<<"\nVisited Node: "<<*actualVertex<<'\n';
        
        //  visit the neighbours of visited node
        for(Vertex* v : actualVertex->getNeighbourList()) {
           // if the neighbour vertex is not visited
            if(!v->isVisited()) {
                // set the visited check to true and add it to the queue
               v->setVisited(true);
               queue.push_back(v);
           }
        }
    }
}