#include <iostream>
#include "data.hpp"

// example to test linking external data

// foo is referred as extern in header file "data" and implemented in data.cpp
// therefore foo has to be defined in global space of this file; if it is defined
// in main() then the linker cannot link and gives error during runtime

int foo{35};


int main()
{
    // foo=34;              // foo is declared as extern in header file therefore it has to be 
    print_foo();            // declared here either in global space or in main() so the implemantation
                            // of print_foo() can use in data.cpp; 
    print(55);
    print(my_data);         // my_data is constant number defined and initialized in header file
                            // therefore we can use it directly here 
    std::cout<<'\n';

    return 0;
}
