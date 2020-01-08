#include <iostream>
#include <type_traits>
#include <array>
#include <cassert>
#include <utility>

// this example works on Compiler Explorer but not on Mac
// due to compiler version; 

template<typename F, typename Array, std::size_t... Is>
decltype(auto) apply_array_impl(F&& f, Array&& a, std::index_sequence<Is ... >)
{
    return std::forward<F>(f)(a[Is]...);
}

template<typename F, typename Array>
decltype(auto) apply_array(F&& f, Array&& a)
{
    
    return apply_array_impl(std::forward<F>(f),
                            std::forward<Array>(a),
                            std::make_index_sequence<a.size()>{}
                            );
}



int main()
{
     std::array<int, 5>array1{3,6,1,2,4};
    
    
    auto sum =apply_array([](auto... x) { return (x + ...);}, array1);
    
    assert(sum ==3+6+1+2+4);
    
    std::cout<<"\nSum of array elements: "<<sum<<'\n';

 
 return 0;
}