#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <numeric>
#include <iterator>
#include <deque>
#include <string>

// Basic operations of STL Containers

int main()
{
    // create a list with 10 elements
    std::list<int>l(10);
   
    // fill the list sequentially starting from 3
    std::iota(l.begin(), l.end(), 3);  
    
    //print the list with copy
    std::cout<<"original list: ";
    std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout," "));
    std::cout<<'\n';
    
     // initialize vector with another container
    std::vector<int>vec(l.begin(), l.end());  
    
    // print vector
    std::cout<<"vec initialized from list: ";
    for(const auto& elem:vec)
        std::cout<<elem<<" ";
    std::cout<<'\n';
    
    // move a container elements into another container by move_iterator
    std::vector<int>vec2(std::make_move_iterator(l.begin()), std::make_move_iterator(l.end()));
    
    // std::move does not work  for vector ; it can be used to move another vector or array
    // std::vector<int>vec2=std::move(l);
    
    std::cout<<"list moved into vec2: ";
    for(const auto& elem:vec2)
        std::cout<<elem<<" ";
    std::cout<<'\n';
    
    // initialize from input stream
    // Note: in this specific case curly brackets { } are required 
    // if regular paranthesis () is used it, the dec becomes a function declaration
    // with return type of deque taking istream as as argument
    std::deque<int>deq{std::istream_iterator<int>(std::cin), std::istream_iterator<int>()};
    
      std::cout<<"initialized from istream deq: ";
    for(const auto& elem:deq)
        std::cout<<elem<<" ";
    std::cout<<'\n';
    
    return 0;
}
