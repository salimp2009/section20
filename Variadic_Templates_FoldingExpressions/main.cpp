#include <iostream>
#include <string>

// Example for a Folding Sum using Variadic Templates
// almost all binary operators can be used for fold expressions
// If the parameter pack is empty, the expression is usually ill-formed ;
// With the exception that for operator && the value is true,
// for operator || the value is false, 
// for the comma , operator the value for an empty parameter pack is void())

template<typename... T>
auto foldsum_right(T... s)
{
    return (... +s);          // this will perform the sum from right to left; ((s1+s2)+s3)+...
}

template<typename...  T>
auto foldsum_left(T... s)
{
    return (s+ ...);          // this will perform the sum from leftt to right; (s+...+(s3+...+(s1+s2))
}

int main()
{
    
    auto sum_right=foldsum_right(2, 3, 5, 70.45f);
    
    std::cout<<sum_right<<'\n';
    
    auto sum_left=foldsum_left(std::string("Salim"), " ", "Didem", " ", std::string("Sema"));
    
    std::cout<<sum_left<<'\n';
 
 return 0;
}