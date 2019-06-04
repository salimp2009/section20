#include <iostream>
#include "Allocator_Linear.h"
#include <new>                      // to use C++17 aligned memory allocation;

// define a custom new & delete for a custom Memory Management
// Example from http://www.swedishcoding.com/2008/08/31/are-we-out-of-memory/


class MyClass {
    int n{0};
    char c{};
    std::string name[4];
};

int main()
{
    // using a custom new with no alignment
    MyClass* myclass_ptr2=new MyClass();
    std::cout<<"\nmyclass_ptr2: "<<sizeof *myclass_ptr2<<'\n';
    delete myclass_ptr2;
    
    // using custom new with alignment class
    // this example did not work because std::align_alloc() did not work; it is C++11 feature 
    // either clang does not support !!!
    // so it is not aligned
    MyClass* myclass_ptr=new(Align(32)) MyClass();
    std::cout<<"ptr size: "<<sizeof(*myclass_ptr)<<'\n';
    delete myclass_ptr;
    
    // C++17 had extra overloads for alignment using header <new>
    // new(std::align_val_t{ }) should be aligned version but did not work
    // however, using alignas(32) works if it is declared in the class or structure definition
    // then using regular takes into accout the specified alignment value; before C++17 
    // even if the class or struct is defined, operator new did not take into account
    MyClass* myclass_ptr3=new(std::align_val_t{16}) MyClass();
    std::cout<<"ptr3 size: "<<sizeof(*myclass_ptr3)<<'\n';
    delete myclass_ptr3;
    
    
    // using custom new with no alignment
    int* ptr=new int(42);
    std::cout<<"\nptr= "<<*ptr<<'\n';
    delete ptr;
    
    // using array version of custom new;
    int* ptr2=new int[4];
    ptr2[0]=20;
    ptr2[1]=10;
    std::cout<<"ptr2[]= "<<*ptr2<<", "<<*(ptr2+1)<<'\n';
    delete [] ptr2;
    
    float* ptr3=new float(45.6f);
    std::cout<<"float: "<<*ptr3<<'\n';
    delete ptr3;
    
    double* ptr4=new double(45.65);
    std::cout<<"float: "<<*ptr4<<'\n';
    delete ptr4;
    
    // using custom placement version of new; this one assigns the value
    // inside the paranthesis to the pointer; similar to using new int(5)
    // however placement can also be used to use pre-allocated memory for creating the new
    // instead of heap but there is no way to define a matching delete 
    // there if a preallocated area is used regular delete will not delete the pointer
    int* ptr5=new(5)int;
    std::cout<<"ptr5: "<<*ptr5<<'\n';
    
    
    std::cout<<"\nsize of char: "<<sizeof(char)<<'\n';

 return 0;
}