#include <iostream>
#include <vector>
#include "MyAllocator.hpp"
#include "MyAlloc.hpp"
#include "StackMemoryPool.hpp"


std::size_t gAllocatedSize;

struct Foo 
{
    int num{};
};


int main()
{
//    std::vector<Foo, MyAlloc<Foo>> vec;
//    vec.resize(20, Foo{10});
//    
//    std::cout<<"\nAllocated size: "<<gAllocatedSize<<'\n';
    
    
    std::vector<int, MyAllocator<int>> vec2{1,4,6,7,8,9,10,45};
    std::cout<<"\nAllocated size: "<<gAllocatedSize<<'\n';

 
 return 0;
}