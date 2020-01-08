#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

// Assign a value to a type
template<auto X>
inline constexpr std::integral_constant<decltype(X), X>c{ };  // this is as same as c<10>->std::integral_constant<decltype(10), 10>


// this is the base of the data structure called ct_set
// since 'this2 pointer is not available during compile time
// define self() function to create an instance of the current item
template<typename... Items>
struct ct_set
{
    static constexpr auto self()noexcept
    {
        return ct_set<Items...>{ }; 
    }
    
    // Contains function checks any passed type T with the other Items type
    // std::disjunction does a logical on any type traits passed
    // so we check every Items in the set with if they are the same type  
    template<typename T>
    constexpr bool contains(T x) const noexcept
    {
        return std::disjunction<std::is_same<T,Items>...>{};
    }
    
    // Add Items
    template<typename T>
    constexpr auto add(T x) const noexcept
    {
        if constexpr(self().contains(x))            // if it exist return self()
            return self();
        else 
            return ct_set<T, Items...>{};           // if the Items dont exist construct a new 
    }                                               // a new ct_set of Items
    
    // remove items
    template<typename T>
    constexpr auto remove(T x) const noexcept       
    {
        if constexpr (!self().contains(x))              // if it does not exist return self()
            return self();
        
        else {
            // Create an empty tuple and move the matching Items into empty tuple (erase),
            // create another tuple for the other Items
            // use std::apply to create a new ct_set from the other Items tuple (filtered)
            constexpr auto filtered=std::tuple_cat(
            std::conditional_t<
                            std::is_same_v<T, Items>,       // alternative way; std::is_same<T, Items>::value
                            std::tuple<>,                   // any Items that matches T will be into empty tuple<>
                            std::tuple<Items>               // if it does not match create a filtered Tuple from Items
                            >{}...);
            return std::apply([](auto ... xs) 
                    { return ct_set<decltype(xs)...>{};},   // std::apply will apply an given function f to the elements of a tupple
                    filtered);                              // the f function here is the lambda which creates a new ct_set instance
        }                                                   // from Items that are filtered
    }
};

int main()
{
    constexpr auto s0 = ct_set{};
    static_assert(!s0.contains(c<42>));
    
    constexpr auto s1=s0.add(c<42>);
    static_assert(s1.contains(c<42>));
    
    constexpr auto s2=s1.add(c<100>);
    static_assert(s2.contains(c<100>));
    static_assert(s2.contains(c<42>));
    
    constexpr auto s3=s2.remove(c<100>);
    static_assert(!s3.contains(c<100>));
    
 return 0;
}