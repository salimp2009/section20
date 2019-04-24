#include <iostream>
#include <queue>

class Person {
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
    std::string name;
    int age;
public:
    Person()=default;
    Person(std::string name, int age)
        : name{std::move(name)}, age{std::move(age)} { }
     bool operator<(const Person& rhs) const {
//         return this->age<rhs.age;
           return this->name<rhs.name;
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
void display(std::priority_queue<T> pq) {
    std::cout<<"[";
    while(!pq.empty()) {
        std::cout<<pq.top()<<" ";
        pq.pop();
    }
    std::cout<<"]\n";
}


void test1() {
    std::cout<<"\n=============Test1====================\n";
    
    std::priority_queue<int>pq;
    for(int i: {3,5,7, 22, 55, 13, 37, 50, 0, 5,7})
        pq.push(i);
    display(pq);
    
    std::cout<<"\nSize: "<<pq.size()<<'\n';
    std::cout<<"\nTop: "<<pq.top()<<'\n';
    
    pq.pop();
    display(pq);
}

void test2() {
    std::cout<<"\n=============Test2====================\n";
    
    std::priority_queue<Person>pq;
    pq.push(Person{"A",10});
    pq.push(Person{"B",2});
    pq.push(Person{"C",17});
    pq.push(Person{"D",13});
    pq.push(Person{"E",8});
    pq.push(Person{"E",28});
    
    display(pq);
    
    pq.pop();
    display(pq);
}

int main()
{
    test1();
    test2();

 
 return 0;
}