#include <iostream>
#include <type_traits>
#include <utility>

// Example for using Index Sequence with Integral Constant 
// to pass a value N to generate a sequence of integers from 0 to N-1
// and pass each index number to a function as an integral_constant to be able to
// pass it both as a type and value 
// so final result function f will be called for each integer created by index sequence
// and will execute what ever in the body of the function

// typical use of integral_constant;
// e.g; typedef std::integral_constant<int, 2> two_t;    // two_t is a constant integer and its value is 2
// e.g; typedef std::integral_constant<int, 4> four_t;  // four_t is a constant integer and its value is 4

template<typename F, std::size_t... Is>
void repeat_impl(F&&f, std::index_sequence<Is...>)  // taking a function f and integer sequence of numbers
{
    
    (f(std::integral_constant<std::size_t, Is>{}), ...);  // pass each IS as integral_constant to pass both as a type 
                                                          // and as a number;
}

template<std::size_t N, typename F>
void repeat(F&&f)
{
    repeat_impl(std::forward<F>(f), std::make_index_sequence<N>{});  // forward a function f and make integer sequence from 0 to N-1
}

int main()
{
    repeat<16>([](auto x)                           // the value 16 is passed as a template parameter N and repeat function
                                                    // will create a sequence of integers from 0 to 15 and pass both lamda function 
    { if constexpr (x%2==0)                         // and those sequence of numbers to repeat_impl as an argument
        std::cout<<"\nEven number: "<<x<<'\n';      // then repeat implemantation will take each sequence number as a variadic
      else                                          // pass it function f as an integral_constant 
        std::cout<<"\nOdd number: "<<x<<'\n';       // suchs as f(std::integral_const<int, 5>) and the function f will be called
                                                    // for each sequence of numbers from 0 to 15 
    });
    

 return 0;
}