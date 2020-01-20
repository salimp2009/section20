#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <chrono>
#include <iostream>
#include <iomanip>

// Function to print properties the passed type of different clocks 
template<typename C>                // different types of clocks require templated function or overloaded funct.
void print_clockData()
{
   std::cout<<"-precision: ";

// check if time unit is less or equal to one millisecond 
    typedef typename C::period P;         // alias for the clock time unit
    if (std::ratio_less_equal<P, std::milli>::value) {      // period is expressed in terms ratio and milli is a predefined ratio =1 /1000

// convert to milli seconds 
        typedef typename std::ratio_multiply<P, std::kilo>::type TT;  // alias for the converted time unit type
        std::cout<<std::fixed<<double(TT::num)/TT::den
                 <<" milliseconds"<<'\n';
             
    } else {
// print as seconds
        std::cout<<double(P::num)/P::den<<" seconds"<<'\n';
    }

    std::cout<<"-is_steady: "<<std::boolalpha<<C::is_steady<<'\n';
}


#endif // _CLOCK_H_