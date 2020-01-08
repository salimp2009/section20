#ifndef _TUPLE_PRINT_H
#define _TUPLE_PRINT_H

#include <iostream>
#include <tuple>


// helper function: print element with index IDX of tuple with MAX elements
template<int IDX, int MAX, typename...Args>
struct PRINT_TUPLE {
    static void print(std::ostream& os, const std::tuple<Args...>& t)
    {
        os<<std::get<IDX>(t)<<(IDX+1==MAX ? "":",");
        PRINT_TUPLE<IDX+1, MAX, Args...>::print(os, t);
    }
};

// partial specialization to end the recursion when IDX==MAX

template<int MAX, typename...Args>
struct PRINT_TUPLE<MAX, MAX , Args...>
{           
    static void print(std::ostream& os, const std::tuple<Args...>& t){}    // no action; just to end recursion  
};

// overloaded output operator

template<typename...Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& t)
{
    os<<"[";
    PRINT_TUPLE<0, sizeof...(Args), Args...>::print(os, t);  // keep printing until MAX(not including because recursion starts from Zero)
    return os<<"]"<<'\n';                                    // then return the os with closing bracket   
}


#endif // _TUPLE_PRINT_H