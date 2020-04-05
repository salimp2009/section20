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
    
    // std::move does not work  for different containers; it can be used for the same type of container
    // to move another vector or array
    // std::vector<int>vec2=std::move(l);
    
    std::cout<<"list moved into vec2: ";
    for(const auto& elem:vec2)
        std::cout<<elem<<" ";
    std::cout<<'\n';
    
    // alternative way of creating a reverse iterator
    // rbegin() refers to the end of vector for iterator to start
    std::vector<int>::reverse_iterator posr=vec2.rbegin();           
    std::cout<<"reverse iterator rbegin for vec2: "<<*posr<<'\n';   
    
    // reverse iterator ++posr in algorithms will actually decrement --posr to start from the end to go begining
    std::cout<<"reverse iterator next element using ++posr: "<<*(++posr)<<'\n';
    
    // initialize from input stream
    // Note: in this specific case curly brackets { } are required 
    // if regular paranthesis () is used it, the dec becomes a function declaration
    // with return type of deque taking istream as as argument
    std::cout<<"Please enter integers(enter a different char to end the input):";
    std::deque<int>deq{std::istream_iterator<int>(std::cin), std::istream_iterator<int>()};
    
      std::cout<<"initialized from istream deq: ";
    for(const auto& elem:deq)
        std::cout<<elem<<" ";
    std::cout<<'\n';
    
    return 0;
}
