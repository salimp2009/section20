#include <iostream>
#include "StackArray.hpp"
#include <initializer_list>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>


// Non type template parameters;
// Floating-point numbers and class-type objects 
// are not allowed as nontype template parameters:

// nontype template parameters carry some restrictions. 
// In general, they can be only constant integral values (including enumerations), 
// pointers to objects/functions/members, lvalue references to objects or functions, 
// or std::nullptr_t (the type of nullptr).


 template<auto N, typename T=decltype(N)>  // the value of first parameter is deduced from the value and
                                               //  second parameter is deduced from the first parameter    
                                               // only in C++17
//template<typename T, int N>                  // regular way
T addValue(T x)
{
    return x + N;
}

int main()
{
    Stack<int, 20>stack1;
    stack1.push(15);
    stack1.push(20);
    std::cout<<stack1.top()<<'\n';
    std::cout<<stack1.size()<<'\n';
    
    for(const auto& s:stack1.get_array())
        std::cout<<s<<" ";
    std::cout<<'\n';
    
    stack1.pop();
    std::cout<<stack1.top()<<'\n';
    
    std::transform(stack1.get_array().begin(), stack1.get_array().end(),   // source range
                   stack1.get_array().begin(),                            // destination
                   addValue<200, int> );                                  // operation; each value in source container will be added
                                                                // added the number passed in addValue<int, 200>
    for(const auto& s:stack1.get_array())
        std::cout<<s<<" ";
    std::cout<<'\n';
    
    std::vector<int>coll{1,2,3,4};
    
    auto sum1=std::accumulate(coll.begin(), coll.end(), 0); // begin, end and initial value
                                                                                       // initValue = initValue + elem   
                             
    
    auto sum2=std::accumulate(coll.begin(), coll.end(),         // begin, end, initial value, predicate
                             0, [](int initial, int elem){ return initial+=elem*elem;});    //
    std::cout<<"\nSum1 and Sum2 : "<<sum1<<" "<<sum2<<'\n';
    
 return 0;
}