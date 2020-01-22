#include <iostream>
#include "data.hpp"
#include <vector>
#include <string>
#include <algorithm>

// example to test linking external data

// foo is referred as extern in header file "data" and implemented in data.cpp
// therefore foo has to be defined in global space of this file; if it is defined
// in main() then the linker cannot link and gives error during runtime

int foo{35};

void print(const std::vector<std::string>& vs)
{
    for(const auto& s:vs)
        std::cout<<s<<" ";
    std::cout<<'\n';
}

void print_array(const int arr[], std::size_t size)
{
    
}
    

int main()
{
    // foo=34;              // foo is declared as extern in header file therefore it has to be 
    print_foo();            // declared here either in global space or in main() so the implemantation
                            // of print_foo() can use in data.cpp; 
    print(55);
    print(my_data);         // my_data is constant number defined and initialized in header file
                            // therefore we can use it directly here 
    std::cout<<'\n';

    std::vector<std::string>friends{"Demir", "Didem", "Sema"};
    print(friends);
    
    // example for passing a C-style array to STL algorithms
    // name of array is the address of the first array elements; works like a pointer
    // by using pointer arithmetic we determine the last of element of the array
    // by dividing sizeof(arr)/sizeof(int); better to use std::array<> much safer and zero overhead
    int arr[]={1,2,3,4};
    std::copy(arr, arr+(sizeof arr/sizeof(int)), 
                std::ostream_iterator<int>(std::cout," "));
    std::cout<<'\n';
    
    print_array(arr, sizeof arr/sizeof(int));
    return 0;
}
