#include <iostream>
#include <set>
#include <algorithm>



class Person {
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
    std::string name;
    int age;
public:
    Person()=default;
    Person(std::string name, int age)
        : name{std::move(name)}, age{std::move(age)} { }
     bool operator<(const Person& rhs) const {
         return this->age<rhs.age;
     }
  
    bool operator==(const Person& rhs) const {
        return (this->name==rhs.name && this->age == rhs.age); 
    }
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os<<p.name<<":"<<p.age;
    return os;
}

template<typename T>
void display(const std::set<T>& s) {
    std::cout<<"[";
    for(const auto& elem:s)
        std::cout<<elem<<" ";
    std::cout<<"]\n";
}

void test1() {
    std::cout<<"\n==========Test 1=============\n";
    std::set<int>s1{1,4,3,5,2};
    display(s1);
    
    s1={1,2,3,1,1,1,2,2,5,5,4,3,5,1};
    display(s1);
    
    s1.insert(0);
    s1.insert(10);
    
    display(s1);
    
    auto [iter, b]=s1.insert(13);     // insert returns a pair<iterator, bool> and [it,b] are copies of those 
    std::cout<<"\nStructured binding: "
             <<*iter<<" "<<b<<'\n';   // auto [it,b]  is a structured binding; equals to the copies of returned variables
    
    if(s1.count(10))
        std::cout<<"\n10 is in the set\n";
    else
        std::cout<<"\n10 is not in the set\n";
        
    auto it=s1.find(5);         // for set use .find(); it works faster than STL algorithm std::find(....)
    
    if(it!=s1.end())
        std::cout<<"\nFound: "<<*it<<'\n';
        
    s1.clear();
    display(s1);
 
}

void test2() {
    std::cout<<"\n==========Test 2=============\n";
    std::set<Person>friends {
        {"Demir", 12}, 
        {"Sema", 65}, 
        {"Didem", 45}
    };
    
    display(friends);  // the elements are sorted by using < operator; it sorts by age
    
    friends.emplace("Salim", 46);
    display(friends);
    
    friends.emplace("Sema", 46);  // invalid entry because 46 already exists; < operator compares ages only
    display(friends);
    
    auto it=friends.find(Person{"Demir", 12});  // find uses ==operator; it is defined to check both name & age
    if(it!=friends.end())
        friends.erase(it);
    
    display(friends);
    
    it=friends.find(Person{"XXX", 46}); // finds the Person with age; operator < uses age only 

    if(it!=friends.end())
        friends.erase(it);              // erases the person with age 46 regardless of the name
    display(friends);

}

void test3() {
    std::cout<<"\n==========Test 3=============\n";
    
    std::set<std::string>s{"A", "B", "C"};
    display(s);
    
    auto result=s.insert("D");
    std::cout<<std::boolalpha;
    if(result.second)
        std::cout<<*(result.first)<<" "<<result.second<<'\n';
    else
        std::cout<<"\nValue already exists..\n";
        
    std::cout<<'\n';
    
    result=s.insert("A");
    display(s);
    
    std::cout<<"first: "<<*result.first<<'\n';
    std::cout<<"second: "<<result.second<<'\n';

}
 

int main()
{
    test1();
    test2();
    test3();    
 return 0;
}