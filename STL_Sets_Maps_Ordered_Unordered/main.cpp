#include <iostream>
#include <algorithm>
#include <list>
#include <forward_list>
#include <vector>
#include <numeric>
#include <iterator>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <functional>
#include <numeric>
#include <set>
#include <map>
#include <utility>

template<typename T, class Cont=std::vector<int>>
void display(const Cont& elem)
{
   for(const T& i:elem)
        std::cout<<i<<" ";
    std::cout<<'\n';
}

// second version of display for any container
// No need to pass type info; auto deduces the type from passed container
// this is more efficient that the previous one
template<typename Cont>
void display2(const Cont& elem)
{
    for(const typename Cont::value_type & i: elem)  // alternative wat determining the Container type by using type_traits
    //for(const auto& i:elem)                       // using auto to create a iterator & determine the type of container 
        std::cout<<i<<" ";
    std::cout<<'\n';
}


template<typename T1, typename T2>
void display3(const std::map<T1, T2>& cont) 
{
    for(auto& elem: cont)
        std::cout<<"Key: "<<elem.first<<", Value: "<<elem.second<<'\n';
    std::cout<<'\n';
}

template<typename Cont>
void display4(const Cont& cont) {
    // alternative to for the auto version
    typename Cont::const_iterator pos=cont.cbegin();
    for(;pos!=cont.cend();++pos)
        std::cout<<pos->first<<", "<<pos->second<<'\n';
    std::cout<<'\n';
}


template<typename InputIterator, typename Pred>
InputIterator find_before_if(InputIterator first, InputIterator last, Pred pred)
{
    if(first==last) return first;
    InputIterator next{first};
    ++next;
    while(next!=last && !pred(*next)) {
        ++next;
        ++first;
    }   
    return first;
}

class Person
{
public:
    
    Person():first_name{}, last_name{} {}
    Person(std::string name, std::string lastname):first_name{std::move(name)}, last_name{std::move(lastname)}{}
    
    // string is a heavy container everytime we use get it will make an expensive copy
    // instead we can return by cont& which is safer; 
    // (although if auto is used const specifiers are decayed !!!)
    const std::string& firstname() const& {return first_name;}
    const std::string& lastname() const& {return last_name;}
    
    bool operator<(const Person& other) const {
        return last_name<other.last_name ||
                (last_name==other.last_name &&
                first_name<other.first_name);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Person& p1) {
        return os<<"["<<p1.firstname()<<", "<<p1.lastname()<<"] ";
    }

private:  
    std::string first_name;
    std::string last_name;  
};

// this function object will be used as a sort criteria in set example
// set can get custom sort criterias 
// operator() return whether a person is less than other person
class PersonSort
{
public:
    
  bool operator()(const Person& p1, const Person& p2 ) const {
      return p1.lastname()<p2.lastname() || 
            (p1.lastname()==p2.lastname() && 
             p1.firstname()<p2.firstname());
  }      
};

// example for Runtime Comparision; you can change the value of comparision method
class RuntimeCmp{
public:
    // two comparision modes defined as public to be able select during runtime 
    enum cmp_mode { normal, reverse};

    // constructor
    RuntimeCmp(cmp_mode mode=normal): mode{mode} { }

    // if the comparision object's mode is normal
    // it will use obj1<obj2 otherwise obj2<obj1
    template<typename T>
    bool operator()(const T& obj1, const T& obj2) const {
        return mode==normal ? obj1<obj2 : obj2<obj1;
    }
    
    bool operator==(const RuntimeCmp& other_rcomp) const {
            return this->mode==other_rcomp.mode; }

private:
 cmp_mode mode;
};

void STL_Set_MultiSet()
{
    std::cout<<"-------------------STL Set_MultiSet-------------------------\n";
    // all elements in a set & multiset are sorted either with the default less than criteria
    // or any passed criteria as a type in set<type,criteria>
    // set does not allow duplicates but multiset allows duplicates
    // sets & multisets dont provide direct access to element
    // cannot change value of element directly 
    // implement as balanced binary tree(red-black tree); seraching is fast; logarithmic
    // 
    std::set<Person, PersonSort>set1{ {"Salim", "Pamukcu"}, {"Didem", "Pamukcu"},
                                        {"Sema", "Pamukcu"}, {"Demir", "Kızıloglu"}
                                        };
    display2(set1);
    
  //  std::set<Person, std::less<Person>>set2(set1);            // the type of two containers have to match exactly
     
                                                                // in order to copy from one set to another
   std::set<int>set2{1,2,3,4,4,5,7,9,9,9};
   display2(set2);
   auto it=set1.begin();                                        // sets use birectional iterators which like forward iterators but can go back as well
   std::advance(it,2);
   
    std::set<Person, PersonSort>set3{set1.begin(),it};
    display2(set3);
    auto [pos, result]=set3.insert({"Salim", "Pamukcu"});       // insert(val) returns the position and whether operation succeeded
                                                                // [pos, result] is key binding C++17 feature
    std::cout<<*pos<<", result="<<std::boolalpha<<result<<'\n';
    display2(set3);
    
    auto status=set3.insert({"Salim", "Pamukcu"});                                           // insert returns std::pair<iterator, bool>
    std::cout<<*std::get<0>(status)<<", result="<<std::boolalpha<<std::get<1>(status)<<'\n'; // using std::pair interface std:get<0>(name_of_pair)

    it=set3.insert(--it, {"sema", "Pamukcu"});
    std::cout<<*it<<'\n';
    display2(set3);
    std::cout<<std::boolalpha<<(bool)set3.erase({"Salim", "Pamukcu"})<<'\n';                // erase(val); erases the value and returns number of elements erased
                                                                                            // for set it is either zero or one but multiset will be total numbers erased
    std::set<Person, RuntimeCmp>set4{set1.begin(), set1.end()};    
    display2(set4);

    // using an alias for the specific type to avoid long typing
    typedef std::set<Person, RuntimeCmp> PersonRuntime;
    
    // create a new set and pass a new comparision as an argument 
    PersonRuntime set5(RuntimeCmp{RuntimeCmp::reverse});
    
    // fill in the new set
    set5.insert(set1.begin(), set1.end());                                                                                    
    display2(set5);
    
    // in order to compare the comparision criteria they have to same type but can have different value
    // the comparision criteria for set1 is PersonSort and set4 or set has RuntimeComps therefore
    // key_comp() or value_comp() member functions wont work but it can be checked first they have the same type
    // using type traits or decltype()
    std::cout<<"set5 comparision==set5 comparision: "<<std::boolalpha<<(set5.key_comp()==set4.key_comp())<<'\n';
    
}                                                               
    

void STL_Map_MultiMap()
{
    std::cout<<"-------------------STL Map_MultiMap()-------------------------\n";
    std::map<float, std::string>map1{{48, "Salim"}, {47, "Didem"}, {15, "Demir"}, {67, "Semos"}};
    display3(map1);
    
    // map used std::pair to store elements; the first element (key) is const
    // second element (value) can be changed but not the first element!!!
    // to modify key, the element with this key has to be removed
    // maps donot provide direct access, it used a bidirectional 
    

    // if you use algorithms and lambdas, the type of map should be specified as a pair and the 
    // first element has to be specified as const . Alternatively you can use auto
    std::for_each(map1.begin(), map1.end(), [](std::pair<const float, std::string>& elem){ elem.second+=" Pamukcu";} );
    
    // Altenative to use auto in lambdas to identify the iterators type passed into lambda!!
//    std::for_each(map1.begin(), map1.end(), [](auto& elem){ elem.second+=" Pamukcu";} );

    display3(map1);
    display4(map1);
    
    if(map1.insert({78,"Semsi"}).second)                // insert returns a pair<position, bool>
        std::cout<<"insert successfull..\n";            // using { } list to deduce the type might cause problem or auto since it might decay constantness
    else
        std::cout<<"insert unsuccesfull..\n";
    
    display3(map1);                                 // map[key]=value tries to insert a new element if it does not exist
 
    map1.insert(std::map<float, std::string>::value_type(45, "NoOne")); // value_type is an alias used by all STL containers
    map1.insert(std::pair<const float, std::string>(46, "NoOne"));      // alternative way; std::map used pair to store the values
    map1.insert(std::make_pair(47, "NoOne"));                           // another way from pair interface    
    display3(map1);
    
    // C++17 if initialization and new function insert_or_assign
    if(auto [pos, success]=map1.insert_or_assign(78, "Semsi_Great"); !success)
        std::cout<<"element already exists : "<<std::boolalpha<<success
        <<", age: "<<pos->first<<", name: "<<pos->second<<'\n';
    
    map1.erase(45);
    map1.erase(46);
    display3(map1);
    
    map1[78]="Dinousorrrr";                         // if the key exists, it returns a reference to the value
                                                    // by assigning a new value to existing you can update the value
    display3(map1);                                 // this property can used to indirectly change the key
    map1[80]="Dinousorrrr";                       // first add the new key with the old value
    display3(map1);
    
    map1.erase(78);                                 // erase(key) returns the number of elements removed, both key or value can be used
    display3(map1);                                 // you can also delete by position or range  
                                                    // erase(pos) deletes the element and return the next position
                                                    
    auto pos=map1.find(80);                         // find return the position of key
    if(pos!=map1.end())
        std::cout<<pos->second<<'\n';              // find is a member function and looks for the key and it is fast
                                                   // to find a specific value use std::find() which will be slow 

    std::map<std::string,int> map2{{"salim", 47}, {"demir", 15} };      

[[maybe_unused]]    std::pair mypair{2.2, 45};                                          // since C++17 it is possible to deduce the type of container from values
    
    display3(map2);
    std::for_each(map2.begin(), map2.end(), 
                            [](std::pair<const std::string, int>& elem){elem.second*=elem.second;});
    
    for(const auto& [key, value]:map2)
        std::cout<<"key: "<<key<<", "<<"value: "<<value<<'\n';
    
    // alternative way of passing type info into lamba; using value_type alias for STL containers
    std::for_each(map2.begin(), map2.end(), 
            [](const std::map<std::string, int>::value_type& elem)               
              {std::cout<<"key: "<<elem.first<<", "<<"value: "<<elem.second<<'\n';});    

    // multimaps allow same key values
 std::multimap<std::string, std::string>family{{"Salim", "Pamukcu"},{"Demir", "Kiziloglu"},
                                                {"Salim", "Pamukcu"}, {"Didem", "Pamukcu"},
                                                {"Sema", "Pamukcu"},{"Salim", "Pamukcu"}};    
                                                
    display4(family);
    
    std::string family_member("Salim");
    for(const auto& [name, lastname]:family) {
        if(name==family_member) {
            std::cout<<"name: "<<name<<", last name: "<<lastname<<'\n';
        }
    }
    std::cout<<'\n';
    
    
}
    

int main()
{
//    STL_Set_MultiSet();
    STL_Map_MultiMap();

    return 0;
}
