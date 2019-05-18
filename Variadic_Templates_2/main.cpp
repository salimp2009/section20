#include <iostream>
#include "Varprint.hpp"


// Example for Using Variadic templates
// See Varprint.hpp for the implementation of print(T firstArg, Types...Args)
// See also Pair-Tuple project for Tuple Print implemantation using variadic template


int main()
{
    print("Salim");                                                         // Overloaded print with one argument is used
    print(20, std::string("Sema"), 45, 'c', 100.23);                        // print(T...Args) will be used
    print<int, char const*, float>(20, "Didem & Demir & Sema", 30.45f);     // Predefine the types of argument of print template instead of auto deduction
    
    const char* s{"School day"};
    print(s);
 
 return 0;
}