#include "BreadFirstSearch.hpp"

void BreadFirstSearch::operator()(std::shared_ptr<Vertex>root) const {
    // create a queue container for a FIFO (First_In_First_Out) data structure
    std::deque<std::shared_ptr<Vertex>>queue;
    // set the root to visited
    root->setVisited(true);
    // add the root to queue
    queue.push_back(root);
    
    // if the queue is not empty it means we have not gone through all the nodes
    while(!queue.empty()) {
        // pop.front() the first node from the Queue and go thru its neighbours
        // if any node is not visited; set it to visited and 
        // add it to queue (will go thru its neighbours later) 
        auto actualVertex=queue.front();
        queue.pop_front();
        std::cout<<"Visit node: "<<*actualVertex<<'\n';
        
        for(auto& v: actualVertex->getNeighbourList()) {
            if(!v->isVisited()) {
                v->setVisited(true);
                queue.push_back(v);
            } 
        }  
    }
}

