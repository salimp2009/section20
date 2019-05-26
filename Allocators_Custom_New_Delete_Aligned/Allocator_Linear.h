#ifndef _ALLOCATOR_LINEAR_H
#define _ALLOCATOR_LINEAR_H

#include <iostream>
#include <cstdlib>
#include <stdlib.h>


// define a custom new & delete for a custom Memory Management
// Example from http://www.swedishcoding.com/2008/08/31/are-we-out-of-memory
// Some features did not work
// next project will be to write my own custom alignment function; sample from 
// Game Engine Architecture Book

void* operator new(std::size_t size)
{
    std::cout<<"\nusing my custom new:"<<size<<'\n';
    return std::malloc(size*sizeof(char));
}

void* operator new(std::size_t size, int val)
{
    std::cout<<"\nusing my custom new with val:"<<size<<'\n';
    void* p=malloc(size*sizeof(char));
    if(p!=nullptr) {
        *static_cast<int*>(p)=val;
    }
    return p;
}

void* operator new[](std::size_t size)
{
    std::cout<<"\nusing my custom array new:"<<size<<'\n';
    return std::malloc(size*sizeof(char));
}

void operator delete (void* mem) noexcept
{
    std::cout<<"\nusing my custom delete...\n";
    std::free(mem);
}

void operator delete (void* mem, int val) noexcept
{
    std::cout<<"\nusing my custom delete...\n";
    std::free(mem);
}

void operator delete [] (void* mem) noexcept
{
    std::cout<<"\nusing my custom array delete...\n";
    std::free(mem);
}

// custom Alignment class; to be able to define alignment during heap allocation 
// with operator new;
class Align {
public:
    explicit Align(int value): m_value{value} { }
    
    int GetValue() const {return m_value;}
    
private:
    int m_value;
};

// using custom new with alignment class
// this example did not work because std::align_alloc() did not work; it is C++11 feature 
// it should be either in the <cstdlib> or <stdlib.h> libraries but not working.!!!!
// might be because clang does not support !!!
// so it is not aligned as intentended !!!!
void* operator new(std::size_t size, Align alignment)
{
    std::cout<<"\nusing my custom aligned new: "<<size<<", "<<sizeof(alignment)<<'\n';
    
   // return std::aligned_alloc(static_cast<std::size_t>(alignment.GetValue()), size);
    return std::malloc(size*sizeof(char));
}

void* operator new[](std::size_t size, Align alignment)
{
    std::cout<<"\nusing my custom array aligned new: "<<size<<", "<<sizeof(alignment)<<'\n';
   // return std::aligned_alloc(static_cast<std::size_t>(alignment.GetValue()), size);
    return std::malloc(size*sizeof(char));
}

void operator delete (void* mem, Align alignment) noexcept
{
    std::cout<<"\nusing my custom aligned delete: \n";
    std::free(mem);
}

void operator delete [] (void* mem, Align alignment) noexcept
{
    std::cout<<"\nusing my custom array aligned delete...\n";
     std::free(mem);
}

#endif // _ALLOCATOR_LINEAR_H