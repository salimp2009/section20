#include <iostream>
#include "My_Stack1.hpp"
#include <tuple>
#include <string>

class Person {
private:
    std::string name;
    int age;
public:
    Person()=default;
    Person(std::string nm, int ag):name{std::move(nm)}, age{ag} {std::cout<<"constructor: "<<name<<", age: "<<age<<'\n';}

friend std::ostream& operator<<(std::ostream& os, const Person& obj) {
    return os<<"name: "<<obj.name<<", age: "<<obj.age<<'\n';
}

};

template<int* p> struct A { };

int num;

constexpr int* pNum() 
{
    return &num;
} 


int main()
{
    std::vector<&num> vec1;
    
   [[maybe_unused]] A<&num> a1;
   
   [[maybe_unused]] A<pNum()> a2;
    
    static int num1{0};
   [[maybe_unused]]A<&num1> a3;
   
    Person p1{"Salim", 48};
    int i{88};
    Stack<Person>personlist{ Person{"Salim", 48}, Person{"Didem", 47} };
    std::cout<<personlist<<'\n';
    
    personlist.push(p1);
    std::cout<<personlist<<'\n';
    
    Stack<int> stack1{1,3,5,7,i};
    std::cout<<"stack1: "<<stack1<<'\n';
    
    Stack<int> stack2{};
    stack2.push(i);
    stack2.top();
    
    Stack<std::pair<int, int>>stack_pair{std::make_pair(1,3), std::make_pair(1,4)};
    std::cout<<"Stack_pair top element: "<<stack_pair.top().first<<", "
                                         <<stack_pair.top().second<<'\n';

    
    std::cout<<stack1.top()<<'\n';
    
    
    stack1.push(i);
    std::cout<<stack1.top()<<'\n';
    
    stack1.push(3);
    stack1.push(5);
    std::cout<<stack1.top()<<'\n';
   
 stack1.pop();
    std::cout<<stack1.top()<<'\n';
//    
//    for(const auto& elem:stack1) 
//        std::cout<<elem<<'\n';
    return 0;
}
