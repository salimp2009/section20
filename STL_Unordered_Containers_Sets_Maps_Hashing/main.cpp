#include <iostream>
#include "Utility.hpp"
#include "Person.hpp"
#include "BoostHash.hpp"
#include "PrintHashTableState.hpp"



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

class PersonHashBoost
{
    public:
    std::size_t operator()(const Person& p) const {
        return hash_val(p.firstname(), p.lastname());
    }
};

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
    
    // example for using Boost hash function
    std::unordered_set<Person, PersonHashBoost>uset5(20);    // minimum bucket number set to 20
    uset5.max_load_factor(0.7);                                 
    uset5={{"Sema","Pamukcu"},{"Semsi","Pamukcu"}};
    display2(uset5);
    std::cout<<'\n';
    
    auto pos1=uset1.count(8);           // counts and returns the number of given values in the set
    std::cout<<pos1<<'\n';
    
    auto pos2=uset5.find({ "Semsi", "Pamukcu"});        
    if(pos2!=uset5.end())
        std::cout<<pos2->firstname()<<", "<<pos2->lastname()<<'\n'; //returns the position iterator of the element
                                                                    // searched    
    auto pos3=uset1.find(8);
    if(pos3!=uset1.end())
        std::cout<<*pos3<<'\n';
    
    // *pos3=45;   // you can not the value of the set since it is used in hash function 
                   // considered as const
    // the key of maps/multimaps are considered as constant
    // if the unordered map is used in algorithms and lambdas the 
    // type of the unordered map has to be declared explicitly
    // you have to declared the type underlying the unordered  map which is 
    // a pair<> ; if you just pass it as std::unordered_map<> then you get
    // compiler error
    std::unordered_map<std::string, int>umap1{ {
    "GARBNK", 100},{"YAPIKRDBANK", 800}, {"AKBNK", 100} };
    display4(umap1);
    
    std::vector unmap11x{46, 45};
   
    // example of maps using algorithms & lambdas
//    using PairStringInt =std::pair<const std::string, int>;
//    using PairStringInt2 = std::unordered_map<std::string, int>::value_type;
    using PairStringInt3 = decltype(umap1)::value_type;
    std::for_each(umap1.begin(), umap1.end(), 
                    [](PairStringInt3& elem){ elem.second+=10;});
    display4(umap1);
    
    umap1["ISBANK"]=1000;
    display4(umap1);
    
    // to change the KEY of a value we have to assign a new Key with the same value 
    // and delete the old "KEY"
    umap1["ISYATIRIM"]=umap1["ISBANK"];   // assign a new Key with the value of old kEY
    umap1.erase("ISBANK");
    display4(umap1);
    
    
    
    std::unordered_multimap<std::string, int>umulMap1{{"Otto",23}, {"Salim", 45},  {"Demir", 15}};
    display4(umulMap1);
   
    
    // different option to insert new elements
    // the type info can be auto deduced with a list or use std::pair<> interface and helper functions
    
    using UnorderedMulMap = std::unordered_multimap<std::string, int>::value_type;
    umulMap1.insert(std::make_pair("Salim", 25));
    umulMap1.insert(std::pair<const std::string, int>("Demir", 15));
    umulMap1.insert(decltype(umulMap1)::value_type{"Sema", 65});
    umulMap1.insert(decltype(umulMap1)::value_type{"Sema", 65});
    umulMap1.insert(UnorderedMulMap{"Otto",76});
    display4(umulMap1);
    
    umulMap1.erase("Otto");         // erase all element with the given value & return the next position
    display4(umulMap1);             // position can be passed also then it will delete only that element 
                                    // a range can be passed as well; all element within the range will be deleted
    // to delete only one of the duplicate elements
    // find the pos and erase
    auto pos4=umulMap1.find("Demir");
    if(pos4!=umulMap1.end())
        umulMap1.erase(pos4);
    display4(umulMap1);
    
    // another option to insert an element; 
    umulMap1.emplace(std::piecewise_construct, std::make_tuple("Otto"), std::make_tuple(45));
    display4(umulMap1);
    
    // passing a lambda function as a hash to create a unordered_multimap
    // lambda will get the key value as an input and return a hash value using boost hash
    // the type of the lambda function has to declared in the map type vy using decltype
    // because lambda function have anonymous types
    auto hash=[](std::string x){ return hash_val(x); };
    std::unordered_multimap<std::string, int, decltype(hash)>umulMap2(20, hash);
    umulMap2.max_load_factor(0.7);
    umulMap2.insert(std::make_pair("Salim", 25));
    umulMap2.insert(std::pair<const std::string, int>("Demir", 15));
    umulMap2.insert(decltype(umulMap1)::value_type{"Sema", 65});
    umulMap2.insert(decltype(umulMap1)::value_type{"Sema", 65});
    display4(umulMap2);
    
    std::unordered_set<int>intset{1,2,3,5,7,9,11,13,15,55,77,88,99};
    printHashTableState(intset);
    
    intset.insert({-76, 66,56,6, 45, 89, 6789, 56789, 5678904});  // checking if rehashing wil occur
    printHashTableState(intset);
    
    printHashTableState(umulMap2);

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
