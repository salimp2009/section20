#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <list>
#include <numeric>
#include <iterator>
#include <deque>
#include <tuple>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <functional>
#include <numeric>

/* Display for Stack Gets a copy of container display the top element
// pops the top element and continue display elements until container is empy
// since the function makes a copy original container is not affected 
// but not preferable since it makes a copy
// it is better to use a custom stack with the similar interface but adding
// a convenience function to acces to underlying container
*/

template<typename Cont>
void display(Cont cont)
{
    while(!cont.empty()) {
        std::cout<<cont.top()<<" ";
        cont.pop();
    }
    std::cout<<'\n';
}

template<typename T>
void display(std::queue<T> cont)
{
    while(!cont.empty()) {
        std::cout<<cont.front()<<" ";
        cont.pop();
    }
    std::cout<<'\n';   
    
}

void STL_Stack()
{   
    // Stack is LIFO Container : Last-In-First-Out
    // Default contianer is Deque but any container class that supports
    // back(), push_back(), pop_back()
    // list initialization is not supported
    // core interface top(), pop(), push()
    std::cout<<"-------------------STL Stack-------------------------\n";
    
  //   std::stack<int>stck1{1,3,5,7,9,10};   // compiler error; list initialization is not supported
    std::stack<int>stck1;
    stck1.push(1);
    stck1.push(3);
    stck1.push(5);
    stck1.push(7);
    
    std::cout<<stck1.top()<<'\n';       // if the container is empty using top() causes undefined behaviour
    stck1.pop();
    
    if(!stck1.empty())
        std::cout<<stck1.top()<<'\n';
        
    display(stck1);
    
     if(!stck1.empty())
        std::cout<<stck1.top()<<'\n';
    
    // when using heavy element types it is better to pass the elements 
    // with std::move() or use emplace to construct in place to avoid unncessary copies
    // and memory allocation
    typedef std::pair<std::string, std::string> PairString;
    std::stack<PairString> stck2;
    
    stck2.emplace("Salim", "Pamukcu");
    if(!stck2.empty())
        std::cout<<stck2.top().first<<'\n';
        
    auto p=std::make_pair<std::string, std::string>("Demir", "Kiziloglu");
    stck2.push(std::move(p));  // if the p is not needed any more , steal its value
    
    if(!stck2.empty())
        std::cout<<stck2.top().first<<'\n';
    std::stack<int>stck3;    
    for(int i:{5,7,9,13}) {
        stck3.push(i);
    }
    if(!stck2.empty())
    std::cout<<stck2.top().first<<'\n';
}

void STL_Queues()
{   
    // Queues are FIFO type(First in First Out) container adapters 
    // the default container is deque
    // front(), back(), push(), pop() are the core operations
    // if the container is empty the behaviour of the core operation are undefined
    // pop() removes the front() element which is the first inserted element
    // you can remove elements in the same order they were inserted
    // (first in, first out ) therefore Queue is a classis data buffer
    
    std::cout<<"-------------------STL Queues-------------------------\n";
    std::queue<std::string>q1;
    
    q1.push("Salim");
    q1.push("Sema");
    q1.push("more than one ");
    display(q1);
    if(!q1.empty()) {
    std::cout<<"front: "<<q1.front()<<'\n';
    std::cout<<"back: "<<q1.back()<<'\n';
    }
    
    q1.pop();
    if(!q1.empty()) {
    std::cout<<"front: "<<q1.front()<<'\n';
    std::cout<<"back: "<<q1.back()<<'\n';
    }

}

void STL_Priority_Queues()
{   
/* Priority_Queue ; elements are sorted according to priority .
// Core interface is same as Queue but front() and back() 
// are not neccessarily the first and last element, elements are sorted partially sorted
// top() has the lowest priority; custom sort criteria can be provided
// via lambda or function object as a sorting predicate that compares two elements
// the next element has always has lowest priorty and top() lowest the highest priority
// default sort is less; e.g. top() element has a greater value and next element has less value
// if more than one highest priority exist, which element is next or top() is undefined
// the default container is std::vector<>  
*/  
    std::cout<<"-------------------STL Priority_Queues-------------------------\n";
auto p_sort=[](float x, float y) { return x<y;}; // lambda function to use a sort predicate 
   
std::priority_queue<float>pbuffer;
std::priority_queue<float, std::deque<float>, decltype(p_sort)>pbuffer2(p_sort);
std::priority_queue<float, std::vector<float>, std::greater<float>>pbuffer3;

for(auto i: {1.3, 1.5, 5.6, 1.1, 2.0, 3.5} ) {
    pbuffer.push(i);
    pbuffer2.push(i);
    pbuffer3.push(i);
}

std::cout<<"pbuffer top: "<<pbuffer.top()<<'\n';
std::cout<<"pbuffer2 top: "<<pbuffer2.top()<<'\n';
std::cout<<"pbuffer3 top: "<<pbuffer3.top()<<'\n';

std::vector<int>vec{1,5,2,7,4,89, 20};
auto p_sort2=[](int x, int y) { return x<y;}; // lambda function to use a sort predicate 
std::priority_queue<int, std::vector<int>, decltype(p_sort2)>pbuff4(vec.begin(), vec.end(), p_sort2);

std::cout<<"pbuffer4 top: "<<pbuff4.top()<<'\n';
    
}

int main()
{
   STL_Stack();
   STL_Queues();
   STL_Priority_Queues();

    return 0;
}
