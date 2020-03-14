#include <iostream>
#include <MyStack2.hpp>
#include <deque>

    template<typename T>
    using DequeStack =Stack<T, std::deque<T>>;
    
    template<typename T>
    struct ValuewithComment {
        T value;
        std::string comment;
    };
    
    // type deduction guide ; const char* will be converted to std::string
    ValuewithComment(const char*, const char*)->ValuewithComment<std::string>;
    
    

int main()
{
    // example for type deduction guide for the struct; works OK
    ValuewithComment vc2={"hello", "initial value"};
    std::cout<<std::is_same_v<decltype(vc2), ValuewithComment<std::string>><<'\n';
    
    Stack<int>st1{1,2,3,4,5};
    std::cout<<st1<<'\n';
    
    // creating an alias
    using StackDoubleDeq =Stack<double, std::deque<double>>;
    Stack<double, std::deque<double>>st2{1.1, 1.2, 1.3};
    std::cout<<"st2: "<<st2<<'\n';
    
    StackDoubleDeq st3{st2};
    std::cout<<"st3: "<<st3<<'\n';
    
    // Since C++17 template argument deduction is also used for deducing type
    // for initialization
    Stack st4{st3};
    std::cout<<"st4: "<<st4<<'\n';
    
//    Stack stringStack="bottom";               // type is deduced as std::string 
//    Stack stringStack{"bottom"};              // type is deduced as const char*
    Stack<std::string> stringStack ="bottom";   // type is explicitly specified as std::string
    
    
    // check the type deduction works OK or not
    std::cout<<std::is_same_v<decltype(stringStack), Stack<std::string>><<'\n';
    
    DequeStack<double> st5{st4};
    
    st2.push(20.5);
    std::cout<<st2<<'\n';
    
    st2.pop();
    std::cout<<st2<<'\n';
    std::cout<<st2.top()<<'\n';
    return 0;
}
