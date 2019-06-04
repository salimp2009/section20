#include <iostream>
#include <vector>
#include "MyAllocator.hpp"
#include "MyAlloc.hpp"
#include "StackAllocator.hpp"
#include <string>
#include "StackMemoryPool.hpp"
#include "Aligned_Allocation.hpp"


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
    
    
//    std::vector<int, MyAllocator<int>> vec2{1,4,6,7,8,9,10,45};
//    std::cout<<"\nAllocated size: "<<gAllocatedSize<<'\n';
  
         //Test case for Memory Pool and Stack Allocator
        StackAllocator<char, false> alloc(128);
        typedef std::basic_string<char, std::char_traits<char>, StackAllocator<char, false>> Str;

        Str str(alloc);

        str="lalala";
        str="lalallalo";

        std::cout<<str<<'\n';

        StackAllocator<Foo> fooalloc(256);

        std::vector<Foo, StackAllocator<Foo>> vec3(fooalloc);

        for(int i{0}; i<10; ++i)
        {
            vec3.push_back(Foo{i});
            
        }
        
        // printing the total allocated size
        std::cout<<"\nTotal allocated size: "<<fooalloc.getMemoryPool().getAllocatedSize()<<'\n';
        

        StackAllocator<int> intalloc(128);

        std::vector<int, StackAllocator<int>> vec4(intalloc);

        for(int i{0}; i<3; ++i)
        {
            vec4.push_back(i);
        }
        
        for(const auto& v:vec4)
            std::cout<<"vec4 element:"<<v<<'\n';
    
 
 return 0;
}