#include <iostream>
#include <tuple>
#include <string>

// Decay Definition from cppreference.com
// Applies lvalue-to-rvalue, array-to-pointer, and 
// function-to-pointer implicit conversions to the type T, 
// removes cv-qualifiers, and 
// defines the resulting type as the member typedef type. 

// Formally:
// If T names the type "array of U" or "reference to array of U", 
// the member typedef type is U*.
// Otherwise, if T is a function type F or a reference thereto, 
// the member typedef type is std::add_pointer<F>::type.

// Using Decay to convert types and remove qualifiers
// it changes arrays to pointer (also removes elements in the array), 
// functions to function pointers
// it also removes references T& become T, T&& becomes T, const T& becomes T
// lvalues converted to rvalues
template<typename... Ts>
using decay_tuple= std::tuple<std::decay_t<Ts>...>;


// Converting C String literals to std::string

// create a create and define T as type either by typedef or using
template<typename T>
struct to_std_string { typedef T type; };

// create a specialized version for const char*
template<>
struct to_std_string<const char*> { using type = std::string; };

// create an alias to make it easier to define the struct type for user
template<typename T>
using to_std_string_t = typename to_std_string<T>::type;

// create a tuple interface that will create a tuple and convert
// C style strings(const char*) to std::string
template<typename... Ts>
auto make_my_tuple(Ts... xs)
{
    return std::tuple<to_std_string_t<Ts>...>{
        std::move(xs) ...};
}


int main()
{
    static_assert(std::is_same_v<
                decay_tuple<int[], const int>, 
                std::tuple<int*, int>
                >);
    static_assert(std::is_same_v
                <
                decltype(make_my_tuple("Salim", 20)),
                std::tuple<std::string, int> 
                >);
 
 return 0;
}