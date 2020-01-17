#include <iostream>
#include <algorithm>
#include <tuple>

/* min, max, minmax can get either two values or initializers list
// when two values are compared it returns a reference and when initializer list is 
// passed to function, it returns a copy
// Capturing the result of std::min by reference if one of the parameters is  rvalue
// it produces a dangling reference if that parameter is returned:
// minmax return a pair;
*/  

// comparision function to be used in std::max

//template<typename T>              // the std::max function does not accept a templated comparision function
bool pntr_int_less(int* a, int* b)
{
    return *a<*b;
}

int main()
{
    /* example to show passing rvalue (n-1 or n+1 or 4, 3..etc)
    // and capturing by reference is supposed to cause a dangling reference
    // cause rvalue is stored temporarily and function takes it by reference to return a 
    // a reference that is temporary so capturing it by reference will cause
    // referring to temp address that might be invalid ?????
    */ 
    int n=1;
    [[maybe_unused]]const int& r=std::min(n-1, n+1);
    
    std::cout<<"r: "<<r<<'\n';                  // r print the correct value but there is no address

                                                
    int x{3};
    int y{5};
    int z{7};
    
    int* px=&x;
    int* py=&y;
    int* pz=&z;
    
    // call max() with special comparison function
    // comparision function return if the first argument is less;
    // if not (false) then function return first argument, 
    // if true then function returns the second argument..

    int* pmax=std::max(px, py, pntr_int_less);
    
    std::cout<<"max("<<x<<", "<<y<<")= "<<*pmax<<'\n';
    
    // example for minmax; returns the minimum and maximum of given list
    // minmax return a pair therefore we capture with  a pair
    // !!! Note;if one of the parameters is an rvalue, 
    // the reference returned becomes a dangling reference !!!!!
    
    std::pair<int*, int*>pmax_list=std::minmax({px, py, pz}, pntr_int_less);
    
    // alternative is to use auto to deduce the returned types
    // auto pmax_list=std::minmax({px, py, pz}, pntr_int_less);         
    
    std::cout<<"min: "<<*(pmax_list.first)<<", max: "<<*std::get<1>(pmax_list)<<'\n';
    
    // [u,v] is structured bindings in C++17
    auto [u, v]=std::minmax({px, py, pz}, [](int* x, int* y){ return *x<*y;});
    std::cout<<"min: "<<*u<<", max: "<<*v<<'\n';
    
    // min() and max() requires same type of values are passed
    // if the types are differenet quafy the type explicitly
    // by using std::max<>()
    int i{3};
    long double l{3.344444};
    std::cout<<"different types: "<<std::max<long double>(i, l)<<'\n';
    
    return 0;
}
