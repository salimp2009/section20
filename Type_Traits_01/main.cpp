#include <iostream>

// Example for Type Traits
// std::is_pointer<T>::value returns true or false value
// std::is_pointer<T>(); returns std::true_type or std::false_type

template<typename T>
void foo_impl(const T& val, std::true_type) 
{
    std::cout<<"\nfoo() is called for a pointer: "<<*val<<'\n';    
}

template<typename T>
void foo_impl(const T& val, std::false_type)
{
    std::cout<<"\nfo() is called for value to: "<<val<<'\n';
    
}

template<typename T>
void foo(const T& val)
{
    return foo_impl(val, std::is_pointer<T>());
    
}


int main()
{
    
 int n{20};
 int y{30};
 int* ptr{&y};
 
 
 foo(n);
 foo(ptr);
 
 
 return 0;
}