#include <iostream>
#include <iostream>
#include <type_traits>
#include <string>

template<typename... TArgs>
decltype(auto) sum2(TArgs...args)
{
    if constexpr ((std::is_integral_v<TArgs> && ...)) {
            std::cout<<std::boolalpha<<"integer: ";
            return (args+ ...);
            
    } else if constexpr ((std::is_floating_point_v<TArgs> || ...)) {
            std::cout<<"floating point: ";
            return (args+ ...);
            
    } else {
        std::cout<<"not an integral or floating point= ";
        return (args+ ...);
    }
}

template<typename T>
std::string asString(T x) 
{
    if constexpr(std::is_same_v<T, std::string>)  // if a runtime if () is used it gives compiler error
        return x;
    else if constexpr(std::is_arithmetic_v<T>)
        return std::to_string(x);
    else 
        return std::string(x);
}

template<typename T>
constexpr auto foo(const T& val)
{
    
    if constexpr (std::is_integral<T>::value)
    {
        if constexpr (T{} < 10) return val*2;
    }
    return val;
}

int main()
{
    constexpr auto x1=foo(42);
    constexpr auto x2=foo("hello");
    
    std::cout<<"x1: "<<x1<<", x2: "<<x2<<'\n';
    
    asString(42);
    
    std::cout<<"sum2: "<<sum2(3, 3.2)<<'\n';
    std::cout<<"sum2: "<<sum2(4, true)<<'\n';
    std::cout<<"sum2: "<<sum2(std::string("42"), std::string("salim"))<<'\n';

    return 0;
}