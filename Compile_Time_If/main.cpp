#include <iostream>
#include <type_traits>


//template<typename TArgs>
//auto sum2(TArgs a, TArgs b)
//{
//    if constexpr(std::is_integral_v<TArgs>)
//        return (a+b);
//    
//    else if constexpr(std::is_floating_point_v<TArgs>)
//        return (a+b);
//    else
//        std::cout<<"not a valid entry..!!!!\n";
//}

template<typename... TArgs>
decltype(auto) sum2(TArgs...args)
{
    if ((std::is_integral_v<TArgs> && ...)) {
            std::cout<<std::boolalpha<<"integer: ";
            return (args+ ...);
            
    } else if ((std::is_floating_point_v<TArgs> || ...)) {
            std::cout<<"floating point: ";
            return (args+ ...);
            
    } else
            std::cout<<"not a valid entry..!!!!\n";
}

int main()
{
    std::cout<<"sum2: "<<sum2(3, 3.2)<<'\n';
    std::cout<<"sum2: "<<sum2(4, true)<<'\n';
   // std::cout<<"sum2: "<<sum2(std::string("42"), true)<<'\n';

    return 0;
}
