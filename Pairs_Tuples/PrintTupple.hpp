#ifndef _PRINTUUPLE_H
#define _PRINTUUPLE_H

#include <tuple>
#include <iostream>

// helper: print element with IDX of tuple with MAX elements
template<int IDX, int MAX, typename...Args>
struct PRINT_TUPLE {
    static void print(std::ostream& strm, const std::tuple<Args...>& t) {
            strm<<std::get<IDX>(t)<<(IDX+1==MAX ? "":",");
            PRINT_TUPLE<IDX+1, MAX, Args...>::print(strm, t);               // print the next element until IDX==MAX
    }
};

// partial specialization to end the recursion
template<int MAX, typename...Args>
struct PRINT_TUPLE<MAX, MAX, Args...> {
    static void print(std::ostream& os, const std::tuple<Args...>& t) {     // when IDX == MAX, the recursion will end; zero elements
    }
};


//overloadec output operator for tuples
template<typename...Args>
std::ostream& operator<<(std::ostream& strm, const std::tuple <Args...>&t) 
{
    strm<<"\n[";
    PRINT_TUPLE<0, sizeof...(Args),Args...>::print(strm, t);               // print first element at a time and calls
                                                                           // recursion will start in PRINT_TUPLE::print() function
                                                              
    return strm<<"]\n";
    
}


#endif // _PRINTUUPLE_H