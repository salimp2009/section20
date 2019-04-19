#include <iostream>
#include "Stack2.hpp"
#include <string>
#include "Stack3.hpp"
#include "MyAlloc1.hpp"
#include <map>

template<typename T>
struct ValuewithComment {
    std::string name{};
    T value;
};
ValuewithComment(const char*, const char*)->ValuewithComment<std::string>;  // type deduction guide

int main()
{
        ValuewithComment vc2 ={"salim", "sema"};
    
        std::vector<int, MyAlloc<int>>vecMyAlloc {1,2,3,4,5,6,7,8};
    
        vecMyAlloc.push_back(40);
    
        Stack<std::string> stack1{"Salim", "Didem", "Demir", "Sema"};
        
        std::cout<<stack1<<'\n';    // operator overload; returns stack.top()
        
        Stack<std::string> stack2{stack1};  // copy constructor
        
        std::cout<<stack2<<'\n'; 
        
        for(const auto& s:stack2.get_deque()) 
            std::cout<<"Stack 2: "<<s<<'\n';
        std::cout<<'\n';
        

        Stack stacknew{"experiment"};  // type deduction from string literals; by default it deduces const char*
                                       // need to use type deduction guide Stack(const char*)->Stack<std::string> 
                                       // right after the class definition
        //Stack stacknew2= "experiment2"; // this example gives an error ; could not fix it
        
        Stack<int*>stack3;
        
        Stack stack4=stack3;                        // Since C++17 argument deduction is OK; compiler
                                                    // determine the type stack4 based on stack3
                                                    // Only in C++17; prefer to use type for code readability

        int* ptr1=new int{42};                      // always delete raw pointer or use smart pointers
        int* ptr2=new int{50};                      // always delete raw pointer or use smart pointers
        
        stack3.push(ptr1);      
        stack3.push(ptr2);
        stack3.push(new int{65});                   // this element needs to be deleted at the end of program since it is on the heap
        
        stack4.push(ptr1);      
        stack4.push(ptr2);                         // use pop() to get it out of container and return it to main and delete
        
        for(const auto& s:stack3.get_vec())
            std::cout<<"Stack3: "<<*s<<'\n';
        std::cout<<'\n';
        
        std::cout<<*stack3.top()<<'\n';             // returns a copy of the top element; element still in container
        delete stack3.pop();                        // remove the last element, return a copy and delete the data on the heap
        
        delete ptr1;
        delete ptr2;
        
        for(const auto& s:stack1.get_deque())
            std::cout<<"\nStack1: "<<s<<" ";
        std::cout<<'\n';
        
        // Example for Map; test needed to Bjarne's Chapter 10 example
        // map stores values as pair<const T1, T2> first value is a constant key, second is the value
        
        std::map<std::string, int>month_input_tbl ={ {"jan", 0}, {"feb", 1}, {"mar", 2},
                                                    {"apr", 3}, {"may", 4}, {"jun", 5},
                                                    {"jul", 6}, {"aug", 7}, {"sep", 8},
                                                    {"oct", 9}, {"nov", 10}, {"dec",11},
                                                   };

        // accessing the value by using key using . at('key')
        std::cout<<month_input_tbl.at("jan")<<'\n';
        std::cout<<month_input_tbl.at("feb")<<'\n';

        // find returns a position index as a pointer and can be dereferenced to get the first (key) and second value
        auto poskey=month_input_tbl.find("jan");
        if(poskey!=month_input_tbl.end())
            std::cout<<"\nMonth: {"<<poskey->first<<", "<<poskey->second<<"}\n";
        std::cout<<'\n';
        
        int n {3};  // the value to be searched in the map as an example; it will be captured by lambda [&n](){  }
        
        // to search by using the value find_if needs to be used
        // lambda is used to define the search criteria; function objects or bind can be used as well
        // find_f returns a position pointer
        auto posval=find_if(month_input_tbl.begin(), month_input_tbl.end(), 
					[&n](const auto& m) { return m.second==n;}   // lambda captures n by reference
					);                                          // lambda also uses iterator value as m and checks
        if(posval!=month_input_tbl.end())
            std::cout<<"\nMonth: "<<posval->first<<'\n';
        
        // range based search is also possible;
        for(const auto& m:month_input_tbl)
            if(m.second==n) {
                std::cout<<"\nMonth: "<<m.first<<'\n';
            }
        
        std::cout<<'\n';
 
 return 0;
}
