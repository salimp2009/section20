#ifndef _PRINTHASHTABLE_H_
#define _PRINTHASHTABLE_H_

#include <iostream>
#include <iomanip>
#include <utility>
#include <iterator>
#include <typeinfo>
#include <algorithm>

// this print function will print the bucket number and  
// all the elements within that buckets inside any unordered container;
// Also displays if the chaining style is doubly linked list or singly-linked list


template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1,T2>& p ) {
    return os<<"["<<p.first<<", "<<p.second<<"]";
}

template<typename T>
void printHashTableState(const T& cont) 
{
    // basic data 
    std::cout<<"size:           "<<cont.size()<<'\n';
    std::cout<<"buckets:        "<<cont.bucket_count()<<'\n';
    std::cout<<"load factor:        "<<cont.load_factor()<<'\n';
    std::cout<<"max load factor:        "<<cont.max_load_factor()<<'\n';
    
    // iterator category; check for chaining style
    if(typeid(typename std::iterator_traits<typename T::iterator>::iterator_category)
                        ==typeid(std::bidirectional_iterator_tag)) {
            std::cout<<"chaining style: doubly-linked list"<<'\n';
    } else {
        std::cout<<"chaining style: singly_linked list";
    }
    
    // elements in each bucket
    std::cout<<"data: "<<'\n';
    for(auto idx=0; idx!=cont.bucket_count(); ++idx) {              // first loop goes thru all the buckets in container
        std::cout<<"b ["<<std::setw(2)<<idx<<"]: ";
       for( auto pos=cont.begin(idx); pos!=cont.end(idx); ++pos) {  // second loops iterates thru specific bucket 
                                                                   // and print the elements of the bucket
           std::cout<<*pos<<" ";                                   // *pos will give us the underlying element if it is a map or multimap
       }                                                           // then the elements of pair<> will be printed
                                                                   // for set and multiset it will directly print (it can be a custom defined type
       std::cout<<'\n';                                            // in that case custom defined type should have overloaded function to print its elements
    }
    
}

#endif // _PRINTHASHTABLE_H_