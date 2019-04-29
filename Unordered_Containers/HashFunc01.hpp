#ifndef _HASHFUNC01_H
#define _HASHFUNC01_H

#include <functional>

// hash_combine function from Boost and STL Book example;
template<typename T>
inline void hash_combine(std::size_t& seed, const T&val) 
{    
    seed ^=std::hash<T>()(val) + 0x9e37779b9 + (seed<<6) + (seed>>2);
}

// generic hash_val using a seed
template<typename T>
inline void hash_val(std::size_t& seed, const T& val)
{
    hash_combine(seed, val);
}

// hash_val function with heterrogenous list of arguments (list of arguments of same type)
template<typename T, typename...Types>
inline void hash_val(std::size_t& seed, const T& val, const Types&...args)
{
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template<typename...Types>
inline std::size_t hash_val(const Types&...args)
{
    std::size_t seed{0};
    hash_val(seed, args...);
    return seed;
}


#endif // _HASHFUNC01_H