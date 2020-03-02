#include <iostream>
#include "My_Stack1.hpp"
#include <tuple>



int main()
{
    int i{88};
    Stack<int> stack1{1,3,5,7,i};
    std::cout<<"stack1: "<<stack1<<'\n';
    
    Stack<int> stack2{};
    stack2.push(i);
    stack2.top();
    
    Stack<std::pair<int, int>>stack_pair{std::make_pair(1,3), std::make_pair(1,4)};
    std::cout<<"Stack_pair top element: "<<stack_pair.top().first<<", "
                                         <<stack_pair.top().second<<'\n';

    
    std::cout<<stack1.top()<<'\n';
    
    
    stack1.push(i);
    std::cout<<stack1.top()<<'\n';
    
    stack1.push(3);
    stack1.push(5);
    std::cout<<stack1.top()<<'\n';
   
 stack1.pop();
    std::cout<<stack1.top()<<'\n';
//    
//    for(const auto& elem:stack1) 
//        std::cout<<elem<<'\n';
    return 0;
}
