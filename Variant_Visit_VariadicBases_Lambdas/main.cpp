#include <iostream>
#include <variant>
#include <type_traits>
#include <cassert>

template<typename... Bases>
struct Visitor: Bases...
{
// Since C++17 agregate types(structs, std::array has default constructors therefore no need 
// to specify a constructor for a struct even it is using Variadic Base; and it can be used as constexpr content

//    template<typename... T>
//    constexpr Visitor(T&&...fs) noexcept(
//                    (std::is_nothrow_move_constructible_v<Bases> && ...) ) 
//                    :Bases{std::forward<T>(fs)}... { }
    
  using Bases::operator()...;          // OK since C++17  
    
};

template<typename... T> Visitor(T...)->Visitor<T...>;                     // no decay_t since we used T as value not T&&                
//template<typename... T> Visitor(T&&...)->Visitor<std::decay_t<T>...>;  // decay_t is used since we used T&& and a const expression is passed
                                                                         // it removes the constants; we only need the type


int main()
{
    constexpr Visitor visitor {
        [](double d)->int {return d +3.4;},
        [](int i)->int {return i+2;} 
    };

    constexpr auto v1=std::variant<int, double>{3.7};
    constexpr auto v2=std::variant<int, double>{9};
    
    static_assert(std::visit(visitor,v1)==7);
    static_assert(std::visit(visitor,v2)==11);
    
    std::cout<<std::visit(visitor, v1)<<'\n';

    return 0;
}
