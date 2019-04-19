#include <iostream>
#include <deque>
#include <algorithm>
#include <vector>
#include <iterator>

// template function to display;
template<typename T>
void display(const std::deque<T>& d) {
    std::cout<<"\n[";
    for(const auto elem:d)
        std::cout<<elem<<" ";
    std::cout<<"]\n";
}

void test1() {
    std::cout<<"\n===========Test1===========\n";
    std::deque<int> d{1,2,3,4,5};
    display(d);
    
    d={2,4,5,6};
    display(d);
    
    
    std::deque<int> d1(10,100); // 10 elements with value of 100
    display(d1);
    
    d[0]=100;       // direct access to element is not efficient
    d.at(1)=200;    
}

void test2() {
    std::cout<<"\n===========Test2===========\n";
    std::deque<int> d{0,0,0};
    display(d);
    
    d.push_back(100);
    d.push_front(200);
    display(d);
    
    std::cout<<"\nFront: "<<d.front()<<'\n';
    std::cout<<"\nBack: "<<d.back()<<'\n';
    std::cout<<"\nSize: "<<d.size()<<'\n';
    
    d.pop_back();
    d.pop_front();
    display(d);
}

void test3() {
    // insert all even numbers to the back of deque and 
    // all odd numbers to the front
    
    std::cout<<"\n===========Test3===========\n";
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};
    std::deque<int> d;
    std::deque<int> d1;
    
    for(const auto& v:vec) {
        if(v%2==0) {
            d.push_back(v);
        }
        else {
            d.push_front(v);
        }
    }
    
    display(d);
    
    // partition into two subranges
    std::partition_copy(vec.begin(), vec.end(),
                        std::back_inserter(d1),             // destination if true
                        std::front_inserter(d1),            // destination if false
                        [](int elem){ return elem%2==0;});  // unary predicate
   display(d1); 
}

void test4() {
    std::cout<<"\n===========Test4===========\n";
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};
    std::deque<int> d;
    
    for(const auto& v:vec)
        d.push_front(v);
        
    display(d);
}

void test5() {
    std::cout<<"\n===========Test5===========\n";
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};
    std::deque<int> d;
    
    std::copy(vec.begin(), vec.end(),
               std::front_inserter(d));

    display(d);
    
    d.clear();
    
    std::copy(vec.begin(), vec.end(),
               std::back_inserter(d));

    display(d);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
 
 return 0;
}