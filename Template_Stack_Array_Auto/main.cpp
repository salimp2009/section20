#include <iostream>
#include "StackArrayAuto.hpp"


int main()
{
    Stack<int, 3>stack1;
    Stack<int, 3>stack2{10,20,30};
    
    stack1.push(3);
    stack1.push(5);
    
    std::cout<<"\nPop(): "<<stack1.pop()<<'\n';
    std::cout<<"\nSize(): "<<stack1.size()<<'\n';
    std::cout<<"\nTop(): "<<stack1.top()<<'\n';

    std::cout<<'\n';
    
 return 0;
}