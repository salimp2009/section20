//#include <iostream>
//#include <chrono>
#include "clock.hpp"
#include <chrono>

int main()
{
    std::cout<<"system_clock: "<<'\n';
    print_clockData<std::chrono::system_clock>();
    std::cout<<"\nhigh_resolution_clock: "<<'\n';
    print_clockData<std::chrono::high_resolution_clock>();
    std::cout<<"\nsteady_clock: "<<'\n';
    print_clockData<std::chrono::steady_clock>();

    std::cout<<'\n';
    return 0;
}
