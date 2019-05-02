#include <iostream>
#include <utility>
#include <tuple>
#include <string>
#include <vector>

class Foo {
public:
    Foo(std::tuple<int, float>) {
        std::cout<<"\nFoo::Foo(tuple)\n";
    }
    
    template<typename...Args>
    Foo(Args...) {
        std::cout<<"\nFoo::Foo(args...)\n";
    }
};

int main()
{
    std::tuple<int, float>t(1,2.22);
    
    //pass tuple as a whole to the constructor Foo
    std::pair<int, Foo>pr{42, t};
    
    // pass tuple elements using piecewise constructor to the constructor Foo
    
    std::pair<int, Foo>pr2(std::piecewise_construct, std::make_tuple(42), t);
    
    auto p1=std::make_pair(42, 2.77);       // it is better to define the type of the pair
                                            // 2.77 will be considered as double. if float was intended
                                            // thnen use pair<int, flot>p1(42, 2.77)
    
    std::cout<<p1.first<<" "<<p1.second<<'\n';
    
    int i{5};
    
    auto p2=std::make_pair(std::ref(i), std::ref(i)); // creates p2<int&, int&>
    ++p2.first;         // changes the value of i
    ++p2.second;        // changes the value of i one more time
    
    std::cout<<p2.first<<" "<<p2.first<<'\n';
    
    std::string s{"SaLİM"};
    std::string s1{"class"};
    
    auto p3=std::make_pair(std::move(s), std::move(s1)); // both t and s wont be used anymore
    
    std::cout<<std::get<0>(p3)<<" "<<std::get<1>(p3)<<'\n';  // get<0>(p3) is similar to p3.first
                                                             // get<1>(p3) is similar to p3.second
                                                             
                                                             
    std::tuple<int, float, std::string>t3{45, 90.76, "Salim"}; // tuples can get any number of elements
    
    std::cout<<std::get<0>(t3)<<" "<<std::get<1>(t3)<<" "<<std::get<2>(t3)<<'\n';  // tuples cannot use t3.first, t3.second; use std::get<0>(t3)..etc
                                                                                   // range based loops and iterators dont work on tuple elements
                                                                                   // unless a custom template function is used 
    // structed binding [i, u]=..
    auto [i1, f1, name]=t3;                                                        // use C++17 feature structural bindings or std::tie to access elements of tuple
    std::cout<<i1<<" "<<f1<<" "<<name<<'\n';
    
    // changing the value of binded element (i1) doesnt effect the value tuples unless we use auto & [ ] to bind 
    i1=25;
     std::cout<<i1<<" "<<std::get<0>(t3)<<'\n';
    
    int i2{};
    float f2{};
    std::string name2{};
    
    // std::tie extracts the values out of tuple and assigns it to variables specified
    // std::tie can be used with pairs as well
    std::tie(i2, f2, name2)=t3;
    std::cout<<i2<<" "<<f2<<" "<<name2<<'\n';
    
    
    // std::ignore is used to ignore the value of the tuple it refers to; used with std::tie
    // std::ignore can be used with pairs 
    std::string c;
    std::tie(std::ignore, std::ignore, c)=t3; 
    std::cout<<c<<'\n';
    
    // tuples cannot be initialized with initializer list
//    std::vector<std::tuple<int, float>>vec{{1,2.2}, {1,3.3}};  // this will give ERROR but it does not ??
      std::vector<std::tuple<int, float>>vec{std::make_tuple(1,2.2), std::make_tuple(1,3.3)};
    
    std::cout<<"\nVector elements: ";
    for(const auto& elem:vec)
        std::cout<<"["<<std::get<0>(elem)<<","<<std::get<1>(elem)<<"] ";
    std::cout<<"\n";
    
    
 return 0;
}