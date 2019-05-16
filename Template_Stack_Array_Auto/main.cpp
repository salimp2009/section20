#include <iostream>
#include "StackArrayAuto.hpp"
#include <string>

// Note that nontype template parameters carry some restrictions. 
// only constant integral values (including enumerations), 
// pointers to objects/functions/members, 
// lvalue references to objects or functions, 
// or std::nullptr_t (the type of nullptr)

template<auto T>                // auto can be used to determine the type either from  value or variable
class Message                   // typename rules apply; Floating-point numbers, doubles, string literals and 
{                               // class-type objects are not allowed as nontype template parameters: 
                              
public:
    void print() {
        std::cout<<T<<'\n';
    }
};



int main()
{
    Message<40> msg1;                     // the type will be determined from 40 and will print 40
    msg1.print();
    
   // Message<int>msg2;                   // this will give error since auto is used to determine from the value/variable
                                          // template<decltype(auto)N> can be used which allows instantiation of N as a reference

                                                
    
    static const char  s[]="Salim";      // static has to be declared to be able to use with auto template parameter
    
    Message<s>msg3;
    msg3.print();
    
    Stack<int, 3u>stack1;                  // stack of 3 unsigned integers
   // Stack<int, 3>stack2={10,20,30};      // initiliazer list did not work ; std::array did not accept
    Stack<std::string, 40> stringstack;    // stack up to 40 strings
    
    
    stringstack.push("Salim");
    stack1.push(3);
    stack1.push(5);
    
    std::cout<<"\nPop(): "<<stack1.pop()<<'\n';
    std::cout<<"\nSize(): "<<stack1.size()<<'\n';
    std::cout<<"\nTop(): "<<stack1.top()<<'\n';
    
    auto size1=stack1.size();
    auto size2=stringstack.size();
    
 //   if(!std::is_same_v<decltype(size1), decltype(size2)>)         // std::is_same_v< > is similar to std::is_same< >::value 
    if(!std::is_same<decltype(size1), decltype(size2)>::value)      // std::is_same< >::value  ; is a type trait compares two given variable 
          std::cout<<"\nSize types are different...\n";             // we use decltype() to determine the type of each container size
    std::cout<<'\n';
    
 return 0;
}