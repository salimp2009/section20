#ifndef _PAIRPRINT_H_
#define _PAIRPRINT_H_

#include <iostream>
#include <utility>

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1,T2>& p )
{
    return os<<"["<<p.first<<", "<<std::get<1>(p)<<"]\n";            // get<0>(p) is equivalent to p.first
}                                                                    // get<1>(p) is equivalent to p.second


#endif // _PAIRPRINT_H_