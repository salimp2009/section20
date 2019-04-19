#include <iostream>
#include "Item.hpp"


int main()
{
    Item<int>item1{"Salim", 46};
    std::cout<<item1.get_name()<<" "<<item1.get_value()<<'\n';
    
    Item<std::string>item2{"Salim", "Programmer"};
    std::cout<<item2.get_name()<<" "<<item2.get_value()<<'\n';
    
    Item<Item<std::string>>item3{"Salim", {"C++", "Programmer"}};
    std::cout<<item3.get_name()<<" "
             <<item3.get_value().get_name()<<" "
             <<item3.get_value().get_value()<<'\n';
             
    std::cout<<"\n=============Vector of Items============\n";
    
    std::vector<Item<double>>vec;
    
    vec.push_back(Item<double>{"Salim", 50.6});
    vec.push_back(Item<double>{"Sema", 500.12});
    vec.push_back({"Didem", 1000.23});
    
    for(const auto& v:vec) 
        std::cout<<v.get_name()<<" "<<v.get_value()<<'\n';
    std::cout<<'\n';
    
    std::cout<<"\n=============Pairs============\n";
    
    My_Pair<std::string, int>p1{"Salim", 50};
    My_Pair<int, double>p2{100, 250.34};
    
    std::cout<<p1.first<<" "<<p1.second<<'\n';
    std::cout<<p2.first<<" "<<p2.second<<'\n';

 
 return 0;
}