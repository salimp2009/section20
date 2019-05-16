#include <iostream>
#include "my_unique_ptr.hpp"

// BASIC UNIQUE_PTR implementation
// std::unique_ptr has more interface option but the main frame is same


int main()
{
    int* n{new int(100)};
    
   
    my_unique_ptr<int> my_ptr{new int(42)};
    my_unique_ptr<int> my_ptr2{n};
    
    std::cout<<(*my_ptr)<<'\n';
    std::cout<<(*my_ptr2)<<'\n';
 
    
    if(*my_ptr) {
        std::cout<<"\nNot empty....\n";
    }
    
    if(my_ptr2) {
        std::cout<<"\nNot empty....\n";
    }
    else {
        std::cout<<"\nempty....\n";
    }
    
   

 return 0;
}