#include <iostream>
#include "Utility.hpp"
#include "Person.hpp"


/*unordered containers contain all the elements in an arbitrary order 
//  That is, you can consider the container to be a bag: you can put in elements, 
//  but when you open the bag to do something with all the elements, 
//  you access them in a random order. So, in contrast with (multi)sets and (multi)maps, 
//  there is no sorting criterion; in contrast with sequence containers, 
//  there is no semantics to put an element into a specific position.
*/

/*All standardized unordered container classes are implemented as hash tables
//-   The hash tables use the “chaining” approach, whereby a hash code is associated with a linked list. 
//-   (This technique, also called “open hashing” or “closed addressing,” 
//    should not be confused with “open addressing” or “closed hashing.”)
//-   Whether these linked lists are singly or doubly linked is open to the implementers.
//    the standard guarantees only that the iterators are “at least” forward iterators.
*/    

/*-   Various implementation strategies are possible for rehashing:
//    – With the traditional approach, a complete reorganization of the internal data happens from
//    time to time as a result of a single insert or erase operation.
//    – With incremental hashing, a resizing of the number of bucket or slots is performed gradually,
//    which is especially useful in real-time environments, where the price of enlarging 
//    a hash table all at once can be too high.
//    Unordered containers allow both strategies and give no guarantee that conflicts with either of them.
*/    

/*  For each value to store, the hash function maps it to a bucket (slot) in the hash table. 
//  Each bucket manages a singly linked list containing all the elements 
//for which the hash function yields the same value. 
*/

// basic custom Hash Function object; not a very optimal one
// just as a sample 
class PersonHash
{
public:
    std::size_t operator()(const Person& p) const {
            return std::hash<std::string>{}(p.firstname()) +
                    std::hash<std::string>{}(p.lastname());
    }
    
};

std::size_t person_hash_funct(const Person& p)
{
    return std::hash<std::string>{}(p.firstname()) ^
           (std::hash<std::string>{}(p.lastname())<<1);
}

void Unordered_Set_MultiSet()
{
    std::cout<<"-------------------STL Unordered_Set_MultiSet-------------------------\n";

    std::unordered_set<int>uset1{1,5,6,7,8,9,10};
    uset1.max_load_factor(0.7);                  // max_load_factor determines how much data each will contain
                                                 // it has to be set right after the 
    display2(uset1);                             // max_load_factor has to be a float and maximum is 1;
                                                 // values between 0.7-0.8 is common; it determines speed & memory consumption 
                                                 // if speed is requested then set the max_load_factor to 1
    
//    std::cout<<"Bucket Count: "<<uset1.bucket_count()<<'\n';            // returns the current num of buckets
//    std::cout<<"Max Bucket Count: "<<uset1.max_bucket_count()<<'\n';                                            
//    std::cout<<"Max_load_factor: "<<uset1.max_load_factor()<<'\n';      // if no value passed it return the current number       
//    std::cout<<"load_factor: "<<uset1.load_factor()<<'\n';                                    

     uset1.rehash(10);                              // rehashes the container so it has a bucket size of at least  
                                                    // passed value; minimum bucket number
     uset1.reserve(10);                            // rehashes the container so it has space for at the least 
                                                    // passed number of elements;  
    display2(uset1);

    // we can pass a hash function or hash function object otherwise 
    // a default  has function hash<> is used in STL defined in header <functional>
    
    std::unordered_set<Person, PersonHash>uset2;
    uset2.max_load_factor(0.5); 
    uset2={ {"Salim", "Pamukcu"}, {"Demir", "Kızıloglu"}};
    
    display2(uset2);
    uset1.rehash(100);
    uset1.reserve(100); 
    
    // alternative way of proiving custom Hash function as a regular function
    // the 
    
    std::unordered_set<Person, std::size_t(*)(const Person&)>uset3(20, person_hash_funct);
    uset3.max_load_factor(0.7);
    uset3={ {"Didem", "Pamukcu"}, {"Sema", "Pamukcu"}};
    display2(uset3);
    
    // creating an alias for the long definition; 
    // it could also be done by 
    // using PersonSet_func_hash = std::unordered_set<Person, std::size_t(*)(const Person&)>;
     typedef std::unordered_set<Person, std::size_t(*)(const Person&)> PersonSet_func_hash;
    PersonSet_func_hash uset4{uset3};
    uset4.max_load_factor(0.8);
    display2(uset4);
    
    std::cout<<'\n';
}


void Unordered_Map_MultiMap()
{
    std::cout<<"-------------------STL Unordered_Map_MultiMap-------------------------\n";


    std::cout<<'\n';
}

int main()
{
    Unordered_Set_MultiSet();
    Unordered_Map_MultiMap();

    return 0;
}
