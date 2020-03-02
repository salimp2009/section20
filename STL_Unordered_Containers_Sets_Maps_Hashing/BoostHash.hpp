#ifndef _MY_BOOSTHASH_H
#define _MY_BOOSTHASH_H

#include <functional>
#include <utility>

// hash generator from Boost library and STL Book
// that takes seed by reference and one value from the args
// it creates by using a combination of std::hash<> and some bitwise operations

template<typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
    seed^=std::hash<T>{}(val)+0x9e3779b9 + (seed<<6)+(seed>>2);
//    std::cout<<"seed: "<<seed<<'\n';
}

// overloaded forwarding function for the last value out of the args to be sent into hash generator
template<typename T>
inline void hash_val(std::size_t& seed, const T& val)
{
    hash_combine(seed, val);            // forward the last value out of args into hash generator to end the recursion
}



// function forwarding the args one by one into generator and call itself until all the args are sent
// for last argument there is overloaded version since it will receive only one value 
template<typename T, typename...Types>
inline void hash_val(std::size_t& seed, const T& val, const Types&...args)
{
    hash_combine(seed, val);            // forward one value out of args into hash generator
    hash_val(seed,args...);             // forward the remaining args into itself recursively until all the args are done
    
}

// function that returns a hash value out of any type and any amount of input
template<typename... Types>
inline std::size_t hash_val(const Types&... args)
{
    std::size_t seed=0;
    hash_val(seed, args...);         // function forwards the seed (where the hash value will be stored)    
//    std::cout<<"seed: "<<seed<<'\n';
    return seed;                      // and args into the function that will send args and seed 
                                      // one by one into another generator function
}

#endif // _MY_BOOSTHASH_H