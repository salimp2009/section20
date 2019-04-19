#include <iostream>
#include "Stack4.hpp"
#include <deque>
#include <iterator>
#include <algorithm>


//enum class Test: uint16_t   // enum types can be any int or char; no double or string allowed
//{
//    test1=5,
//    test2=8
//};

int main()
{  
    // Enum class test; enum types can be any int or char; no double or string allowed
//    Test t{Test::test1};
//    
//    std::cout<<"Enum Test::test2 : "<<static_cast<int>(Test::test2)<<'\n';
//    
//    std::cout<<"Enum Test t: "<<static_cast<int>(t)<<'\n';
    
    Stack<int, std::vector<int>> stack1{1,2,3,4,5, 6,7};
    
    for(const auto& s:stack1.get_vec())
        std::cout<<"Stack 1: "<<s<<'\n';
    std::cout<<'\n';
    
    Stack<int, std::vector<int>> stack2{100};
    
    for(const auto& s:stack2.get_vec())
        std::cout<<"Stack 2: "<<s<<'\n';
    std::cout<<'\n';
    
    Stack<double, std::deque<double>>stack3{1.2, 1.4, 1.5};
     for(const auto& s:stack3.get_vec())
        std::cout<<"Stack 3: "<<s<<'\n';
    std::cout<<'\n';
    
    std::copy(stack3.get_vec().cbegin(), stack3.get_vec().cend(),
              std::ostream_iterator<double>(std::cout<<"\nStack3 with deque:\n", " ") );
    std::cout<<'\n';
    
    typedef Stack<int, std::vector<int>> IntVecStack;    // typedef for type alias; 
 // using IntVecStack = Stack<int, std::vector<int>>;    // 'using' for type alias; alternative
   
    IntVecStack stack4{21, 22,23, 34,45};
    
    
    for(const auto& s:stack4.get_vec())
        std::cout<<"\nstack4: "<<s<<'\n';
 
 return 0;
}