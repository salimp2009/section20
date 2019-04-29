#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include "HashFunc01.hpp"
#include "Bucket.hpp"

class Customer {
private:
    std::string fname;
    std::string lname;
    long no;
public:
    Customer(const std::string& fn, const std::string& ln, long n) 
        : fname{fn}, lname{ln}, no{n} { }
    
    std::string firstname() const {return fname;}
    std::string lastname() const {return lname;}
    long number() const {return no;}
    
friend std::ostream& operator<<(std::ostream& os, const Customer& c) {
    return os<<"["<<c.fname<<", "<<c.lname<<": "<<c.no<<"]";
}

friend class CustomerHash;
friend class CustomerEqual;
   
};

class CustomerHash {
public:    
    std::size_t operator()(const Customer& c) const {
        return hash_val(c.fname, c.lname, c.no);
    }
};

class CustomerEqual {
public:
    bool operator()(const Customer& c1, const Customer& c2) const {
        return c1.no==c2.no;
    }
};



template<typename T>
void display(const std::unordered_set<T>& u_set) {
    std::cout<<"\n[";
    for(const auto& elem:u_set) {
        std::cout<<elem<<" ";
    }
    std::cout<<"]\n";
}

template<typename T1, typename T2>
void display(const std::unordered_map<T1, T2>& u_map) {
    std::cout<<"\n[";
    for(const auto& elem:u_map) {
        std::cout<<elem.first<<": "<<elem.sec<<" ";
    }
    std::cout<<"]\n";
}

template<typename T1, typename T2, typename T3>
void display(const std::unordered_set<T1, T2, T3>& u_set) {
    for(const auto& elem:u_set) {
        std::cout<<elem<<" ";
    }
    std::cout<<'\n';
}

void test1() {
    std::cout<<"\n===========Test1================\n";
    std::unordered_set<int> coll{1,2,3,5,7,1,1, 3,17,19,77};  // elements are in arbitrary order; duplicates not allowed
    display(coll);
    
    coll.insert({-13, 15,-77, 99, -99});
    display(coll);
    
    coll.erase(-99);   // erase a specific value
    display(coll);
    
    // inserts returns a std::pair<iterator, bool>
    auto pos=coll.insert(std::accumulate(coll.begin(), coll.end(), 0)); // insert sum of all elements
    display(coll);
    
    if(pos.first!=coll.end())
        std::cout<<(*pos.first)<<'\n';
        std::cout<<"\nPosition no: "<<std::distance(coll.begin(), pos.first)+1<<'\n';
        
    // initialization in if statement is possible with C++17
    // find() returns std::iterator
    if(auto it=coll.find(-13); it!=coll.end())
        std::cout<<"\n-13 is found at "<<std::distance(coll.begin(), it)+1<<'\n';
}

void test2() {
    std::cout<<"\n===========Test2================\n";
    
    // hash function using lambda
    auto hash=[](const Customer& c) {
        return hash_val(c.firstname(), c.lastname(), c.number());
    };
    
    // equality function using lamba
    auto eq=[](const Customer& c1, const Customer& c2) {
        return c1.number()==c2.number();
    };
    
    // create an unordered set types; Customer, hash and eq with 10 elements 
    std::unordered_set<Customer, decltype(hash), decltype(eq)> cust_set(10, hash, eq);
    
    cust_set.emplace("Salim", "Pamukcu", 46);
    cust_set.insert(Customer{"Sema", "Pamukcu", 65}); 
    display(cust_set);
    
    std::unordered_set<Customer, CustomerHash, CustomerEqual>cust_set2(20);
    cust_set2.emplace("Didem", "Pamukcu Laane", 45);
    cust_set2.insert(Customer{"Demir", "Kızıloglu Pamukcu", 12});
    display(cust_set2);
    
    printHashTable(cust_set);
    printHashTable(cust_set2);
}

void test3() {
    std::cout<<"\n===========Test3================\n";
    std::unordered_set<int>cust_set{1, 3, 17, 5, 29, 55};
    display(cust_set);
    printHashTable(cust_set);
    
    cust_set.insert({-12, 24, 35, -55});
    display(cust_set);
    printHashTable(cust_set);
    
}
int main()
{
    test1();
    test2(); 
    test3();

 return 0;
}