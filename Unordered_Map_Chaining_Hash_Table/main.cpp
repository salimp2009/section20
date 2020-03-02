#include <iostream>
#include "HashTable.hpp"

int main()
{
    HashTable hashtable{};
    hashtable.put(1,1);
    hashtable.put(11,10);
    hashtable.put(21,100);
    
    
//    std::cout<<hashtable.get(1)<<'\n';
//    std::cout<<hashtable.get(11)<<'\n';
//    std::cout<<hashtable.get(21)<<'\n';
    
    return 0;
}
