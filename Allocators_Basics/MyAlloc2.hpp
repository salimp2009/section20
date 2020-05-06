#pragma once

// typicall C++ standart allocator; minimum implemantation
// if you want to use custom memory pool or arena with STL containers
// these requirements are needed

#include <cstddef>       // for std::size_t

template<typename T>
class MyAlloc2
{
public:
    // type definitions
    typedef T value_type;
    
    // constructors; allocator has no state
    MyAlloc2() noexcept {}
    
    // copy constructor from a convertible type
    template<typename U>
    MyAlloc2(const MyAlloc2<U>& ) noexcept {} // both allocators has no state and does not throw
    
    // allocate memory for the given num of elements * sizeof type
    // but does not initialize
    T* allocate(std::size_t num) 
    {
        printf("Allocating: %lu\n", num * sizeof(T) );              // %lu is for long unsigned if %d is used compiler gives warning
        return static_cast<T*>(::operator new(num * sizeof(T)));
    }
    
    // deallocate storage p of given number of deleted elements
    void deallocate(T* p, std::size_t num) 
    {
        printf("De-allocating: %lu\n", num * sizeof(T) );           // %lu is for long unsigned if %d is used compiler gives warning
        ::operator delete(p);
    }
};

    template<typename T1, typename T2>
    bool operator==(const MyAlloc2<T1>&, const MyAlloc2<T2>&) noexcept {return true;}

    template<typename T1, typename T2>
    bool operator!=(const MyAlloc2<T1>&, const MyAlloc2<T2>&) noexcept {return false;}