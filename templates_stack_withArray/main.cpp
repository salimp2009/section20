#include <iostream>
#include "StackArray.hpp"
#include <string>

int main()
{
    Stack<int, 5>stckArr1;
    
    stckArr1.push(20);
    stckArr1.push(50);
    stckArr1.push(60);
    stckArr1.push(70);
    stckArr1.push(88);
    
   Stack<int, 5>stckArr2(stckArr1);
   std::cout<<stckArr2<<'\n';
   
   stckArr1.pop();
   std::cout<<stckArr1.top()<<'\n';
   std::cout<<stckArr1<<'\n';
    
   Stack<std::string, 10> stringStack;
   stringStack.push("Salim");
   stringStack.push("Didem");
   stringStack.push("Demir");
   stringStack.push("Sema");
   
   std::cout<<stringStack<<'\n';
   std::cout<<stringStack.top()<<'\n';


    return 0;
}
