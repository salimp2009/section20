#include "HashTable.hpp"
#include <iostream>

HashTable::HashTable() {
    hashTable.resize(table_size);
}

// accessing to an items with a key or search
int HashTable::get(int key) {
    
    std::size_t generatedArrayIndex=hash(key);

    // if the value does not exits so we return
    if(hashTable[generatedArrayIndex].empty()) return -1;


    // check the vector with the index and acces to the list in the vector
    // it will return the list and we will check if there are any items with this index
    // we get it by reference so we dont get an unneccessary copy
    std::list<HashItem> &items=hashTable[generatedArrayIndex];
    
    
    // search for the item going thru list returned in the vector
    // if there is only one item the running time will be O(1)
    // but if there are more items stored because of collision 
    // then worst case scneario will be O(N)
    for(const HashItem& item:items)
        if(item.key==key)
            return item.value;
    
    return -1;
}

// inserting a new item
void HashTable::put(int key, int value) {
    // generate an index for the key using hash() function
    std::size_t hashArrayIndex=hash(key);
    
    std::list<HashItem>& items=hashTable[hashArrayIndex];
    
    if(items.empty()) {
            std::cout<<"No collision simple insert....\n";
    } else {
        // if the vector is not empty: there are already items with this hash 
        std::cout<<"Collision when inserting key: "<<key<<'\n';
        
        // check if the same key, value exists then we will just return
       for(const HashItem& item:items) {
            if( item.key==key) {
                std::cout<<"Item already exists/inserted...\n";
                return;
            }
       }
    }
        
    // insert the new item into this array index into the list
    items.push_back(HashItem{key, value});
    
    std::cout<<"Size of the list: "<<items.size()<<'\n';
}

std::size_t HashTable::hash(int key) {
    return key % table_size;        // simplest hash function; not effective; 
                                    // better use Boost::hash_value<> or any other one
}