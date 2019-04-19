#ifndef _ITEM_H_
#define _ITEM_H_

#include <iostream>
#include <string>
#include <vector>

template<typename T>
class Item {
private:
    std::string name;
    T value;
public:
    Item(const std::string& name, const T& value):name{name}, value{value} { }
    
    std::string get_name() const {return name;}
    T           get_value() const {return value;}  
};
// Item(const char*)->Item<std::string>;

template<typename T1, typename T2>
struct My_Pair {
  T1 first;  
  T2 second;
    
};
// MyPair(const char*, const char*)->Mypair<std::string, std::string>;

#endif // _ITEM_H_