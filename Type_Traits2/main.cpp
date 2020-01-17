#include <iostream>
#include <type_traits>

// A type trait provides a way to deal with the properties of a type. 
// It is a template, which at compile time yields a specific type or 
// value based on one or more passed template arguments, which are usually types

//template<typename T>
//void foo(const T& val)
//{
//    if(std::is_pointer<T>::value)
//        std::cout<<" foo() called pointer...\n";
//    else
//        std::cout<<" foo() called a value...\n"; 
//}


//template<typename T>
//void foo(const T& val)
//{
//    std::cout<<(std::is_pointer<T>::value ? *val:val);        // Compiler error because *v
//}                                                             // the code generate false for both types
                                                                // therefore *v becomes invalid
     
template<typename T>
void foo_impl(const T& val, std::true_type)
{
        std::cout<<"foo() called for pointer: "<<*val<<'\n';
}

template<typename T>
void foo_impl(const T& val, std::false_type)
{
    std::cout<<"foo() called for value: "<<val<<'\n';
}                                                      

template<typename T>
void foo(const T& val)
{
    foo_impl(val, std::is_pointer<T>());            // std::is_pointer<>() is a member function
}                                                   // and the return type is std::true_type or
                                                    // std::false_type; so we use two overloads for each type
                                                    // the alternative is to overload  foo() and foo<T*>()
// Overloading for integral types;
// if we have too many options to overload such as 
// float, double long double, short, unsigned short, int
// then providing an overloaded function for each type; too much work :)
// type_trait std::is_integral can be used to create two overloads


template<typename T>
void g_impl(T val, std::true_type)          // integral type; short, int, long, long long, bool, char, char8_t...
{
    std::cout<<"integral type: "<<val<<'\n';
}

template<typename T>
void g_impl(T val, std::false_type)         // non-integral type; floating, double, long double...
{
    std::cout<<"Non-integral: "<<val<<'\n';
}

template<typename T>
void g(T val)
{
    g_impl(val, std::is_integral<T>());
} 

int main()
{
//    int n{5};
//    int* p=&n;
//    foo(5);                  // calls a value   
//    foo(n);                  //
//    foo(p);                 // calls a pointer    
//    foo(new int(5));        // calls a pointer
    
    g(4.24242);              // return non_integral type   
    g(5);                    // return integral type 
    g('c');                  // returns integral type
    g("salim");              // non_integral; literal
    g(std::string("salim")); // non_integral    

    return 0;
}
