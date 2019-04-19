#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iterator>

class Person {
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
    std::string name;
    int age;
public:
    Person(): name{"Unknown"}, age{0} {}
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
void display(const std::list<T>& l) {
    std::cout<<"[";
    for(const auto& elem:l)
        std::cout<<elem<<" ";
    std::cout<<"]\n";

}

void test1(){
    std::cout<<"\n============Test1==============\n";
    std::list<int>l1{1,2,3,4,5};
    display(l1);
    
    std::list<std::string>l2;
    l2.push_back("Back");
    l2.push_front("Front");
    display(l2);
    
    std::list<int>l3;
    l3={10,20,30,40,50,60};
    display(l3);
    
    std::list<int>l4(10, 100);
    display(l4);
    
}

void test2() {
    std::cout<<"\n============Test2==============\n";
    std::list<int>l{1,2,3,4,5,6,7,8,9,10};
    display(l);
    
    std::cout<<"\nSize: "<<l.size()<<'\n';
    
    std::cout<<"\nFront: "<<l.front()<<'\n';
    std::cout<<"\nBack: "<<l.back()<<'\n';
    
    l.clear();
    display(l);
    std::cout<<"\nSize: "<<l.size()<<'\n';

}

void test3() {
    std::cout<<"\n============Test3==============\n";
    std::list<int>l{1,2,3,4,5,6,7,8,9,10};
    display(l);
    
    l.resize(5);
    display(l);
    
    l.resize(10, 100);  // increases the size to 10 and assigns 100 to the new element;
    display(l);
    
    std::list<Person>persons;
    persons.resize(5);      // default constructor will generate 5 elements with default values
    display(persons);
}

void test4() {
    std::cout<<"\n============Test4==============\n";
    std::list<int>l{1,2,3,4,5,6,7,8,9,10};
    display(l);
    
    auto it=std::find(l.begin(), l.end(), 5);
    l.insert(it,100);
    display(l);
    
    std::list<int>l2{1000,2000,3000};       // iterator is still valid because the element it refers to is not deleted
    l.insert(it,l2.begin(), l2.end());
    display(l);
    
    std::advance(it, -4);               // move the iterator 4 positions backwards (-4) from where it is
    std::cout<<*it<<'\n';
    
    auto itnew=l.erase(it);             // erases the element at position & return the position of next element  
    display(l);                         //  the position pointer it will be invalid after erase; dont use it again
    std::cout<<*itnew<<'\n';            // unless it is reset otherwise using it is undefined behaviour
 
}

void test5() {
    std::cout<<"\n============Test5==============\n";
    std::list<Person>friends {
        {"Demir", 12}, {"Sema", 65}, {"Didem", 45} };
        
    display(friends);
    std::string name{};
    int age{0};
    std::cout<<"\nPlease enter the name of person: ";
    std::getline(std::cin, name);
    std::cout<<"\nPlease enter the age of person: ";
    std::cin>>age;
    
    friends.emplace_back(name, age);  // will call default constructor to create a Person(name, age)
    display(friends);
    
    //insert "Salim" before "Sema"
    auto it=std::find(friends.begin(), friends.end(), Person{"Sema", 65});
    if(it!=friends.end())
        friends.emplace(it, "Salim", 46);  // dont use {} for the arguments; emplace uses a variadic arguments
    display(friends);                      // emplace(pos, args....)
}

void test6() {
    std::cout<<"\n============Test6==============\n";
    
    std::list<Person>friends {
        {"Demir", 12}, {"Sema", 65}, {"Didem", 45} };

    display(friends);
    friends.sort();
    display(friends);
    

}


int main()
{
    test1();
    test2();
    test3();
    test4();
    //test5();
    test6();
 return 0;
}