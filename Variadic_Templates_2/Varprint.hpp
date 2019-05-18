#ifndef _VARPRINT_H
#define _VARPRINT_H

#include <iostream>


/* void print()                             // overloaded print function to end the recursion 
{
    
}
*/
template<typename T>
void print(T firstArg)                      // if one argument overloaded is provided the void print() above
{                                           // is not needed to end the recursion; this function will do it
    std::cout<<firstArg<<'\n';
}
    
template<typename T, typename... Types>     // the variadic identifier ... must come right after typename...
void print(T firstArg, Types... Args)       // the variadic identifier ... must come right after type identifier Types...
{
  // std::cout<<firstArg<<'\n';             // alternative way to print first argument; this can be also written as a seperate function
  // std::cout<<sizeof...(Args)<<'\n';      // print number of remaining arguments
    print(firstArg);
  // std::cout<<sizeof...(Args)<<'\n';
    print(Args...);                       // prints the remaining arguments;
                                            // 
                                            // when there is no argument overloaded void print function above 
}                                           // will be called to end the recursion

#endif // _VARPRINT_H