#include <iostream>
#include <variant>


// Example for Variadic Baes for multiple Bases in class, structs
// we can overload the operators to be able to use different types
struct foo_float { constexpr float operator()(float x) const {  return x; } };

struct foo_char { constexpr char operator()(char x) const { return x;} };

template<typename... Bases>
struct overloader:Bases...
{
    using Bases::operator()...;     //OK in C++17 but does not work C++14 or c++11
};

// alternative overloader with variadic bases & recursion
template<typename TF, typename... TFs>
struct overloader2: TF, overloader2<TFs...>
{
    using TF::operator();
    using overloader2<TFs...>::operator();
};

// specialization if there is one type TF other
template<typename TF>
struct overloader2<TF>:TF
{
    using TF::operator();
};

// Example for Lambda, Variadics, Variants, Visit
template<typename TF, typename... TFs>
struct overload_set: TF, overload_set<TFs...>
{
    using TF::operator();
    using overload_set<TFs...>::operator();
    
    template<typename TFFwd, typename...TRest>
    overload_set(TFFwd&& f, TRest&&...rest): 
                        TF{std::forward<TFFwd>(f)}, 
                        overload_set<TFs...>{std::forward<TRest>(rest)...} {}
};

template<typename TF>
struct overload_set<TF>:TF
{
    using TF::operator();
    
    template<typename TFFwd>
    overload_set(TFFwd&& f):TF{std::forward<TFFwd>(f)} { 
        }
};

template<typename...TFs>
auto overload(TFs&&... fs) 
{
    return overload_set<std::decay_t<TFs>...>(std::forward<TFs>(fs)...);
}

//template<typename...TFs>
//constexpr auto overload_forwd(TFs&&... fs) 
//{
//    auto visitor=overload(std::forward<TFs>(fs)...);
//}

template<typename...TVariants>
 constexpr auto match(TVariants&&... vs)
{
    return [&vs...](auto&&... fs)->decltype(auto)
            {
                auto visitor=overload(std::forward<decltype(fs)>(fs)...);
                return std::visit(visitor, std::forward<TVariants>(vs)...);
            };
} 


int main() 
{
    using my_variant2=std::variant<int, float, double>;
   [[maybe_unused]] my_variant2 v1{20.34f};
    my_variant2 v2{45};
    
    match(v2)([](int x){std::cout<<x<<"i\n";}, 
                 [](float x){std::cout<<x<<"f\n";},
                 [](double x){std::cout<<x<<"d\n";});
    
    
    std::cout<<"\n.........Example with Lambdas..................\n";
    auto o=overload([](float x) { return x;},
                    [](char x) { return x;} );
                    
    static_assert(o(267.598f)==267.598f);
    static_assert(o('j')=='j');
    
    auto xf=o(345.67f);
    auto xc=o('k');
    std::cout<<"xf: "<<xf<<'\n';
    std::cout<<"xc: "<<xc<<'\n';
    
    using my_variant=std::variant<int, float>;
    my_variant var0{345.67f};
    std::cout<<"var0.index(): "<<var0.index()<<'\n';
    std::size_t ind=var0.index();
    std::cout<<ind<<'\n';
    
    
    auto i=std::get<1>(var0);
    std::cout<<"i: "<<i<<'\n';
    std::cout<<std::get<1>(var0)<<'\n';
    
    auto printvar=[](const auto& x){ std::cout<<"printing from lambda:"<<x<<'\n';};
    std::visit(printvar, var0);
    
   
    std::cout<<"\n.........Example with Structs..................\n";
    using foo=overloader<foo_float, foo_char>;
    auto xx=foo{}(23.5f);
    auto yy=foo{}('c');
    std::cout<<"float: "<<xx<<", char: "<<yy<<'\n';

    overloader2<foo_float, foo_char> overld2;
    static_assert(overld2(23.5f)==23.5f);
    static_assert(overld2('b')=='b');
    std::cout<<"overloader2 float: "<<overld2(55.666f)<<", overloader2 char: "<<overld2('h')<<'\n';


    return 0;
}
