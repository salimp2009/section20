#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <set>

// Vector Properties and STL 

// if user specified type is used with STL then make sure
// to overload operator< and operator== in order to use algorithms & iterators

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

void display2(const std::vector<int>& vec) {
    std::cout<<"\n[";
    std::for_each(vec.cbegin(), vec.cend(), 
                  [](int elem){std::cout<<elem<<" ";});
    std::cout<<"]\n";
}

template<typename T>
void display(const std::vector<T>& vec) {
    std::cout<<"\n[";
    for(const auto& v:vec)
        std::cout<<v<<" ";
    std::cout<<"]\n";
}

template<>
void display(const std::vector<int>& vec) {
    std::cout<<"\n[";
    std::copy(vec.begin(), vec.end(), 
                  std::ostream_iterator<int>(std::cout, " "));
    std::cout<<"]\n";
}

void test1() {
    std::cout<<"\n==========Test 1===========\n";
    
    std::vector<int>vec{1,2,3,4,5};
    display(vec);
    
    vec={2,4,5,6};
    display2(vec);
    
    std::vector<int>vec1(10, 100);
    display(vec1);
}

void test2() {
    std::cout<<"\n==========Test 2===========\n";
    
    std::vector<int>vec{1,2,3,4,5};
    display(vec);
    
    std::cout<<"\nvec size: "<<vec.size()<<'\n';
    std::cout<<"\nvec max_size: "<<vec.max_size()<<'\n';
    std::cout<<"\nvec capacity: "<<vec.capacity()<<'\n';
    
    vec.push_back(6);
    display(vec);
    std::cout<<"\nvec size: "<<vec.size()<<'\n';
    std::cout<<"\nvec max_size: "<<vec.max_size()<<'\n';
    std::cout<<"\nvec capacity: "<<vec.capacity()<<'\n';
    
    vec.shrink_to_fit();
    display(vec);
    std::cout<<"\nvec size: "<<vec.size()<<'\n';
    std::cout<<"\nvec max_size: "<<vec.max_size()<<'\n';
    std::cout<<"\nvec capacity: "<<vec.capacity()<<'\n';
    
    vec.reserve(100);
    display(vec);
    std::cout<<"\nvec size: "<<vec.size()<<'\n';
    std::cout<<"\nvec max_size: "<<vec.max_size()<<'\n';
    std::cout<<"\nvec capacity: "<<vec.capacity()<<'\n';
}

void test3() {
    std::cout<<"\n==========Test 3===========\n";
    
    std::vector<int>vec{1,2,3,4,5};
    display(vec);
    
    vec[0]=100;
    vec.at(1)=200;
    
    display(vec);

}

void test4() {
    std::cout<<"\n==========Test 4===========\n";
    std::vector<Person>friends;
    
    Person p1{"Salim", 46};
    display(friends);
    
    friends.push_back(p1);
    display(friends);
    
    friends.push_back(Person{"Demir", 12});
    display(friends);
    
    friends.emplace_back("Didem", 45);
    display(friends);
    
}

void test5() {
    std::cout<<"\n==========Test 5===========\n";
    std::vector<Person>friends {
        {"Salim", 46},
        {"Demir", 12},
        {"Didem", 45},
        {"Sema", 65}
    };
    
    display(friends);
    std::cout<<"\nFront : "<<friends.front()<<'\n'; // returns a reference to first element
    std::cout<<"\nBack : "<<friends.back()<<'\n';   // returns a reference to last  element
    
    friends.pop_back();
    display(friends);
}

void test6() {
     std::cout<<"\n==========Test 6===========\n";
    std::vector<int>vec{1,2,3,4,5};
    display(vec);
    
    vec.clear();  // remove all elemennts
    display(vec);
    
    vec={1,2,3,4,5,6,7,8,9,10};
    vec.erase(vec.begin(), vec.begin()+2);
    display(vec);
    
    vec={1,2,3,4,5,6,7,8,9,10};
    // erase all even numbers
    auto it=vec.begin();
    while(it!=vec.end()) {
        if(*it%2==0) 
            vec.erase(it);
        else
            ++it;
    }
    
    display(vec);
    
    std::swap(vec[0], vec[1]);
    display(vec);
}

void test7() {
    std::cout<<"\n==========Test 7===========\n";
    
    std::vector<int>vec1{1,2,3,4,5};
    std::vector<int>vec2{10,20,30,40,50,60, 70, 80};
    std::vector<int>vec3;
    
    std::transform(vec1.begin(), vec1.end(),
                   std::back_inserter(vec3),
                  std::bind(std::multiplies<int>(), std::placeholders::_1, 10 ));
    
    display(vec1);
    display(vec2);
  //  display(vec3);
    
    vec1.swap(vec2);  // for swap vectors can be different size 
    display(vec1);
    display(vec2);
    
}

void test8() {
    std::cout<<"\n==========Test 8===========\n";
    
    std::vector<int>vec1{5,1,3,2,6,2,1};
    display(vec1);
    
    std::sort(vec1.begin(), vec1.end());
    display(vec1);

}

void test9() {
     std::cout<<"\n==========Test 9===========\n";
    std::vector<int>vec1{1,2,3,4,5};
    std::vector<int>vec2{10,20};
    display(vec1);
    display(vec2);
    
    std::copy(vec1.begin(), vec1.end(), std::back_inserter(vec2));
    display(vec1);
    display(vec2);

   // copy_if the element is even
    vec1={1,2,3,4,5};
    vec2={10,20};
    std::copy_if(vec1.begin(), vec1.end(),
                std::back_inserter(vec2),
                [](int x){return x%2==0;});
    display(vec1);
    display(vec2);
}   
    
void test10() {
    std::cout<<"\n==========Test 10===========\n";
    
    std::vector<int>vec1{1,2,3,4,5};
    std::vector<int>vec2{10,20,30,40,50};
    std::vector<int>vec3;
    
    display(vec1);
    display(vec2);
    display(vec3);
    
    std::transform(vec1.begin(), vec1.end(),
                   vec2.begin(),
                    std::back_inserter(vec3),
                    [](int x, int y){return x*y;});
                    
    display(vec1);
    display(vec2);
    display(vec3);
}

void test11() {
    // insert vec2 into vec1 right before 5
    std::cout<<"\n==========Test 11===========\n";
    
    std::vector<int>vec1{1,2,3,4,5,6,7,8,9,10};
    std::vector<int>vec2{100,200,300,400};
    display(vec1);
    display(vec2);

    auto it=std::find(vec1.begin(), vec1.end(), 5);
    
    if(it!=vec1.end())
        vec1.insert(it, vec2.begin(), vec2.end());
    else
        std::cout<<"\nNumber not found in vec1..\n";
        
    display(vec1);
}
    

int main()
{
    std::set<Person> friends;
    Person p1{"Salim", 46};
    
     auto [it, b]=friends.insert(p1);  // structured bindings
     
     std::cout<<*it<<" "<<b<<'\n';
    
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
 return 0;
}