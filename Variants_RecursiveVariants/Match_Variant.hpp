#ifndef _MATCH_VARIANT_H
#define _MATCH_VARIANT_H

#include <iostream>
#include <variant>

// From the Example for Lambda, Variadics, Variants, Visit
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
    return overload_set<std::remove_reference_t<TFs>...>(std::forward<TFs>(fs)...);
}

template<typename...TVariants>
constexpr auto match(TVariants&&... vs)
{
    return [&vs...](auto&&... fs)->decltype(auto)
            {
                auto visitor=overload(std::forward<decltype(fs)>(fs)...);
                return std::visit(visitor, std::forward<TVariants>(vs)...);
            };
} 

#endif // _MATCH_VARIANT_H