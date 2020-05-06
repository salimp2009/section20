#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include "MyAlloc2.hpp"
#include <experimental/memory_resource>


int main()
{
    // std::allocator<T> defines the C++ default allocator for a given type
    
    auto alloc_check=std::uses_allocator<std::vector<int>, std::allocator<int>>::value;

    std::cout<<std::boolalpha<<"Allocator check= "<<alloc_check<<'\n';
    
    std::allocator<std::string> s1;     // s1 is the allocator
    
    // allocate memory for a given number of elements but does not construct
    // it allocates a memory of size for the given amount of value * sizeof
    // and returns a pointer to the start of storage; pointer to the array reserved
    // similar to T* storage = ::operator new(num * sizeof(T)); 
    // as an additional argument we can pass a pointer if we want it
    // storage next to another known storage area
    std::string *storage= s1.allocate(5);
    
    // construct the int on the given storage
    s1.construct(storage, "salim");        // construct is deprecated in c++17 and wiil be romved in c++20
    
    std::cout<<"storage[0]= "<<storage[0]<<'\n';
    std::cout<<"*storage= "<<*storage<<'\n';            // to access the value use aarray subscript of the pointer
    
    // construct another string on  the given storage
    // but iterator the memory using pointer arithmetic
    s1.construct(&storage[1], "didem");
    std::cout<<"storage[1]= "<<storage[1]<<'\n';
    
    s1.construct(storage+2, "demir");
    std::cout<<"storage[2]= "<<storage[2]<<'\n';
    
    // call the destructor of the type
    // same as T* storage->~T();
    s1.destroy(storage);             // destroy is deprecated in c++17 and wiil be romeved in c++20; but detroy is redefined to destroy a range 
    s1.destroy(storage+1);
    
    std::cout<<storage[1]<<'\n';    // you can access to the storage the value is still valid until a new one overrides but still resever
    
    
    s1.deallocate(storage, 5);      // deallocate calls delete p for the given storage and the size
    
    std::cout<<"storage[1] after deallocate "<<storage[1]<<'\n';   // you can access to the storage value but another program can use  the area so it is undefined behaviour
    std::cout<<"using pointer arithmetic= "<<*(storage+1)<<'\n';

    std::vector<int, MyAlloc2<int>>myVec1;   // if you just number arguments it still copies when push back elements and reallocation
    myVec1.reserve(5);                      // if you use reserve and if the amount is not exceeded than no copying & reallocation is done
    
    myVec1.push_back(20);
    myVec1.push_back(10);
    myVec1.push_back(30);
    myVec1.push_back(40);
    myVec1.push_back(50);
    
    
    return 0;
}
