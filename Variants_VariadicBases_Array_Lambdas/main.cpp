#include <iostream>
#include <variant>
#include <array>
#include <string>
#include <algorithm>
#include <type_traits>

template<typename... Bases>
struct Visitor:Bases...
{
    template<typename... T>
    Visitor(T&&... fs):Bases(std::forward<T>(fs))...
    {
    }
    
    using Bases::operator()...;  
};

template<typename... T>
Visitor(T...)->Visitor<T...>;


int main()
{
    std::array<std::variant<double, int, char, std::string>, 4>arr1{3.45, 50, 'c', "Salim"};
    std::array<std::variant<double, int>, 2>arr2{3.45, 50};
    
    
    int     intTotal{0};
    double  doubleTotal{0};
    std::common_type_t<decltype(intTotal), decltype(doubleTotal)> grandTotal{0};
    
    Visitor visitor{[&intTotal](const int x)    {  intTotal+=x;},
                    [&doubleTotal](const double x) {  doubleTotal+=x;},
                    [](const std::string& s)    { std::cout<<"string: "<<s<<'\n';},
                    [](const char c)            { std::cout<<"char: "<<c<<'\n';}
                    };
       
   std::for_each(arr1.begin(), arr1.end(), 
                  [&visitor](const auto& v){std::visit(visitor, v);} );
                  
    std::cout<<"double total: "<<doubleTotal<<'\n';
    std::cout<<"int total: "<<intTotal<<'\n';
 
    // this example from Jason Turner web tutorials but somehow the values are always converted to int
    // even if the double is passed 
    auto generic_visitor=[&intTotal, &doubleTotal, &grandTotal](const auto v){
                            grandTotal+=v;
                            std::cout<<"grand_total (generic visitor): "<<grandTotal<<'\n';
                            
                            if constexpr (std::is_same<double, decltype(v)>{}) {
                                doubleTotal+=v;
                                std::cout<<"double total: "<<doubleTotal<<'\n';
                            }
                            else {
                                intTotal+=v;
                                std::cout<<"int total: "<<intTotal<<'\n';
                            } };
        
    std::for_each(arr2.begin(), arr2.end(), 
                  [&generic_visitor](const auto& v){std::visit(generic_visitor, v);} );
                  
    std::cout<<"double total: "<<doubleTotal<<'\n';
    std::cout<<"int total: "<<intTotal<<'\n';
    
    return 0;
}
