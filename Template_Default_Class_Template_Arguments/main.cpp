#include <iostream>
#include <MyStack2.hpp>
#include <deque>

int main()
{
    Stack<int>st1{1,2,3,4,5};
    std::cout<<st1<<'\n';
    
    Stack<double, std::deque<double>>st2{1.1, 1.2, 1.3};
    std::cout<<st2<<'\n';
    
    st2.push(20.5);
    std::cout<<st2<<'\n';
    
    st2.pop();
    std::cout<<st2<<'\n';
    std::cout<<st2.top()<<'\n';
    return 0;
}
