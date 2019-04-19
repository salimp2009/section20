#include <iostream>
#include <map>
#include <set>


void display(const std::map<std::string, std::set<int>>& m) {
    std::cout<<"[";
    for(const auto& elem:m) {
        std::cout<<elem.first<<", [";
        for(const auto set_elem:elem.second) {
            std::cout<<set_elem<<" ";
        }
        std::cout<<"]";
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
   
   

    m.clear();              // erases all elements 
    display(m);         
    
}

int main()
{
    test1();
    
 
 
 return 0;
}