#include <iostream>
#include <type_traits>
#include <string>
#include <cstddef>
#include <limits>
#include <alloca.h>



// Example for if constexpr use;
// if we use only if statement and invoke foo with an integer 
// it will return x but since both bracnhes of the if statement will be instantiated 
// during compile time it will also try to invoke x.length() and it will give runtime error 
// if we pass x as an integer but if we use if constexpr and 
// if we pass int or string only one of the branches 
// will be instantiated so it will run correctly

template<typename T>
int foo_constexpr(const T& x)
{
    if constexpr(std::is_same_v<T, std::string>)
    {
        return x.length();
    }
    else
        return x;
}

template<typename T>
int foo(const T& x)
{
    if (std::is_same_v<T, std::string>)
    {
        return x.length();
    }
    else
        return x;
}

constexpr long long factorial(int x)
{
    long long result{1};
    for(int i{1}; i<=x; ++i) {
        result*=i;
    }
    return result;
}


int main()
{
   // foo(20);                      // compile time error; both bracnhes of if instantiated x.length() not valid for integer
   // foo(std::string("Salim"));    // compile time error; both branches ibstantiated; the false statement tries to return x;
                                    // but the return type is integer and return x tries to return a string so gives an error
    
    foo_constexpr(15);                      // works OK; only one of the conditions will be returned  
    foo_constexpr(std::string("Sema"));     // works OK; only one of the conditions will be returned
    
    constexpr long long n=factorial(20);
    std::cout<<n<<'\n';
    
    // Stuff below not related to compile time !!;
    std::cout<<alignof(::max_align_t)<<'\n';                    // prints the default alignment of the max number; typically 16
    std::cout<<std::numeric_limits<float>::epsilon()<<'\n';     // print the machine epsilon; will different from system to system
                                                                // machine epsilon is smallest floating number that will satisfy x + epsilon() > x
                                                                // so anything smaller than epsilon() will not change the value of x since the machine will not be able compute
   
 return 0;
}