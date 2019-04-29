#ifndef BUCKET_H
#define BUCKET_H

#include <iostream>
#include <iomanip>
#include <utility>
#include <iterator>
#include <typeinfo>

template<typename T>
void printHashTable(const T& cont) {
    // basic bucket data;
    std::cout<<std::setw(18)<<std::left<<"\nSize:"<<cont.size()<<'\n';
    std::cout<<std::setw(18)<<std::left<<"Buckets:"<<cont.bucket_count()<<'\n';
    std::cout<<std::setw(18)<<std::left<<"Load Factor:"<<cont.load_factor()<<'\n';
    std::cout<<std::setw(18)<<std::left<<"Max Load Factor:"<<cont.max_load_factor()<<'\n';
    
    // iterator category; checking type of iterator by using iterator_traits
    // if birectional iterator the it is doubly linked otherwise it is a singly-linked list
    if(typeid(typename std::iterator_traits<typename T::iterator>::iterator_category)
                        ==typeid(std::bidirectional_iterator_tag)) {
      
        std::cout<<"\nchaining style: doubly-linked\n";
    } else {
        std::cout<<"\nchaining style: singly-linked\n";
    }
    
    // elements for buckets
    std::cout<<"\ndata: \n";
    for(std::size_t idx{0}; idx!=cont.bucket_count(); ++idx) {           // loop through each bucket
        std::cout<<"b["<<std::setw(2)<<idx<<"]: ";                 // print bucket ID
        for(auto it=cont.begin(idx); it!=cont.end(idx); ++it) {    // print data in each bucket
            std::cout<<*it<<" ";
        }
        std::cout<<'\n';
    }
 
}


#endif // BUCKET_H