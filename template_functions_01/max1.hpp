#ifndef _MAX1_HPP_
#define _MAX1_HPP_


// typename or class can be used to define the template parameters; types
// struct cannot be used

template<typename T>
T max(T a, T b)
{
    return a > b ? a:b;
}


#endif // _MAX1_HPP_