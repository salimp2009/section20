#include <iostream>
#include "data.hpp"


//int foo{34};                  

// foo is declared in data.hpp
// therefore it has to be either defined here if it is not extern
// it can be either in global space or in a function with static keyword


void print_foo()
{
    // static int foo{36};
    std::cout<<"printing foo: "<<foo<<'\n';
}

void print(int n)
{
    std::cout<<"printing the number: "<<n<<'\n';
}