#include <iostream>
#include <map>
#include <set>


void display(const std::map<std::string, std::set<int>>& m) {
    std::cout<<"[";
    for(const auto& elem:m) {
        std::cout<<elem.first<<":[";
        for(const auto set_elem:elem.second) {
            std::cout<<set_elem<<" ";
        }
        std::cout<<"] ";
    }
    std::cout<<"]\n";
}

template<typename T1, typename T2>
void display(const std::map<T1,T2>& m) {
    std::cout<<"[";
    for(const auto& elem:m)
        std::cout<<elem.first<<": "<<elem.second<<" ";
    std::cout<<"]\n";
}

void test1() {
    std::cout<<"\n===============Test1==================\n";
    
    std::map<std::string, int>m{
        {"Demir", 3}, 
        {"Didem",1}, 
        {"Sema", 2} 
    };
    display(m);
    
    m.insert(std::pair<std::string, int>{"Salim", 5});
    display(m);
    
    m.insert(std::make_pair("Semsi", 8));
    display(m);
    
    m["Rob"]=45;            // if key does not exist, it inserts and returns a reference to the value
    m["Rob"]+=10;           // if the key does exist, the value is updated and returns a reference to the value
    m.at("Salim")=15;       // same as []operator but checks the range; throws an out_of range execption 
    display(m);
    
    m.erase("Rob");         // erase method used the key to erase; dont use the value Only key
    display(m);             // if value is used then use find_if algorithm and erase 
                            // if erase it used by value with algorithm
                            // either update iterator if used after, or use m.erase(it++)
   std::cout<<"\nCount for Salim: "<<m.count("Salim")<<'\n';
   std::cout<<"\nCount for Rob: "<<m.count("Rob")<<'\n';
   
   auto it=m.find("Demir");    // search with the key value;
   if(it!=m.end())
       std::cout<<"\nFound "<<it->first<<": "<<it->second<<'\n';

    m.clear();              // erases all elements 
    display(m);         
}

void test2() {
    std::cout<<"\n===============Test2==================\n";
    
    std::map<std::string, std::set<int>>grades{
        {"Demir", {100,90,80}},
        {"Salim", {95}},
        {"Sema", {95,99,100}}
    };
    
    display(grades);
    
    grades["Salim"].insert(98);  // [key] return reference to the value and value is a set
                                 // using sets insert() method to add to the set
    
    auto it=grades.find("Sema");            // search for the key; returns an iterator
    if(it!=grades.end())
        it->second.insert({1000, 12}); // dereference iterator to get second element; 
                                            // it->first=key and it->second=value
                                            // second element is a set; use insert for set to add value
                                            // to the set
   display(grades);                                         
   
}

int main()
{
    test1();
    test2();
    
 
 
 return 0;
}