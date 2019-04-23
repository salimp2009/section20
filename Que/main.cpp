#include <iostream>
#include <queue>

// Queue Example
// Queue is used std::deque as the default container type
// Iterators are not supported therefore algorithms cannot be used
// the container has to support push_back, pop_front, back(), front()
// OnLy std::deque and std::list can be used a container type 
// mainly used for scheduling, job/task scheduling  
// Stacks are used mainly in compiling; calculate expressions..etc

template<typename T>
void display(std::queue<T> q) {
    std::cout<<"\n[";
    while(!q.empty()) {
        std::cout<<q.front()<<" ";
        q.pop();
    }
    std::cout<<"]\n";
}

int main()
{
    std::queue<int>q;
   

    for(int i:{1,2,3,4,5})
        q.push(i);
    display(q);
    
  
    std::cout<<"\nFront: "<<q.front()<<'\n';
    std::cout<<"\nBack: "<<q.back()<<'\n';
    
    q.push(100);
    display(q);
    
    q.pop();
    q.pop();
    display(q);
    
    while(!q.empty())
        q.pop();
    display(q);
    
    std::cout<<"\nSize: "<<q.size()<<'\n';
    
    q.push(100);
    q.push(150);
    q.push(2000);
    display(q);
    
    q.front()=500;    //q.front() returns a reference to the first element
                      // therefore assignment changes the value
    q.back()=30;      // q.back() returns a reference to last element
                      // therefore assignment changes the value
    display(q);
    
    std::cout<<'\n';
    
 return 0;
}