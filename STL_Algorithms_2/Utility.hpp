#ifndef _MY_UTILITY_H
#define _MY_UTILITY_H

#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iterator>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <functional>
#include <utility>
#include <array>

template<typename Cont>
void display(const Cont& elem)
{
   for(const typename Cont::value_type& i:elem)
        std::cout<<i<<" ";
    std::cout<<'\n';
}

// second version of display for any container
// No need to pass type info; auto deduces the type from passed container
// this is more efficient that the previous one

// use for unordered sets & multisets
template<typename Cont>
void display2(const Cont& elem)
{
    for(const typename Cont::value_type& i: elem)  // alternative way to determine the Container type by using type_traits
    //for(const auto& i:elem)                       // using auto to create a iterator & determine the type of container 
        std::cout<<i<<" ";
    std::cout<<'\n';
    std::cout<<"Bucket Count: "<<elem.bucket_count()<<'\n';            // returns the current num of buckets
    std::cout<<"Max Bucket Count: "<<elem.max_bucket_count()<<'\n';                                            
    std::cout<<"Max_load_factor: "<<elem.max_load_factor()<<'\n';      // if no value passed it return the current number       
    std::cout<<"load_factor: "<<elem.load_factor()<<'\n';       
    std::cout<<'\n';
}

// use for unordered map, multimaps
template<typename T1, typename T2>
void display3(const std::unordered_map<T1, T2>& cont) 
{
    for(auto& elem: cont)
        std::cout<<"Key: "<<elem.first<<", Value: "<<elem.second<<'\n';
    std::cout<<'\n';
}


// use for any map, multimaps
template<typename Cont>
void display4(const Cont& cont) {
    // alternative to for the auto version
    typename Cont::const_iterator pos=cont.cbegin();
    for(;pos!=cont.cend();++pos)
        std::cout<<pos->first<<", "<<pos->second<<'\n';
    std::cout<<'\n';
}

#endif //_MY_UTILITY_H