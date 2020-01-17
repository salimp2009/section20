// #include <iostream>  // included in PairPrint.hpp
// #include <utility>   // included in PairPrint.hpp
   

#include "PairPrint.hpp"
// #include <tuple>
#include <functional>
#include <string>
#include <vector> 
#include "Tuple_Print.hpp"

class Foo
{
  public:
  Foo(std::tuple<int,float>) {
      std::cout<<"Foo::Foo(tuple)"<<'\n';
  }  
  template<typename...Args>
  Foo(Args...args) {
      std::cout<<"Foo::Foo(args...)"<<'\n';
  }
  
};

void f(std::pair<int, const std::string> p)
{
    std::cout<<"printing from the function f:"<<p<<'\n';
}


int main()
{
    // example for piecewise construct that 
    // allows two tuples to pass their elements as the first & second elements of the pair
    // therefore if a tuple is passed via piecewise construct the elements of the pair will not be a tuple
    // but the individual elements of the tuple will be used
    // if the tuple is passed as a whole then the element of pair is a tuple
    
    std::tuple<int, float>t(2, 2.22);
    
    std::pair<int,Foo>p3(42, t);                                // tuple is passed as whole to second element of pair
                                                                // thru the constructor of Foo
    std::pair<int, Foo>p4(std::piecewise_construct, std::make_tuple(42), t);
    std::cout<<"p4 first element is an integer: "<<std::get<0>(p4)<<'\n';
    
    std::pair<int, double>p1(7, 2.2);
    
    std::cout<<p1<<'\n';                                        // print pair using overloaded ostream 
    std::cout<<p1.first<<", "<<std::get<1>(p1)<<'\n';
    
                                                                    // create an alias using typedef, 
    typedef std::pair<int, float> IntFloatPair;                     // alternative: using IntFloatPair=std::pair<int, float>;
    
    std::cout<<std::tuple_size<IntFloatPair>::value<<'\n';          // tuple interface can be used for total element numbers using alias
    std::cout<<std::tuple_size<std::pair<int,float>>::value<<'\n';  // alternatively using std::pair
                                                                
    // std::tuple_element<1, IntFloatPair>::type can be used to determine type of the elements of the pair but
    // this can be used for type assignment or type comparision or assertion; 
    // the type cannot be print via std::cout ????
    
    
    auto p2=std::make_pair(20, "salim");                            // make_pair is used to create a pair by using move symentics if possible otherwise copy is used
    std::cout<<p2<<'\n';                                            // "salim" is converted to const char*
                                                                    // The make_pair() function makes it convenient
                                                                    // to pass two values of a pair directly 
                                                                    // to a function that requires a pair as its argument. 
    int i{5};
    auto p5=std::make_pair(std::ref(i), std::ref(i));                 // elements of pair will be reference to i  
    std::cout<<"p5 original: "<<p5;                                   // ref() & cref() are helper functions of std::reference_wrapper< >   
    ++p5.first;                                                       // any change to pair elements will change the value of i   
    ++p5.second;                                                      // any change to i will also chage elemnts of pair 
   
    std::cout<<"Changed i thru pair: "<<i
             <<"\np5 revised: "<<p5<<'\n';
             
             
    std::tuple<int, float, std::string>t1(2, 32.2, "salim");
    std::cout<<std::get<0>(t1)<<" "<<std::get<1>(t1)<<" "<<std::get<2>(t1)<<'\n';
    
    
    auto t2=std::make_tuple(3.2, 2, "demir");
    std::cout<<std::get<0>(t2)<<" "<<std::get<1>(t2)<<" "<<std::get<2>(t2)<<'\n';
    
    std::string s1{"didem"};
    
    std::pair<std::string&, std::string>pair_ref(s1, "demir");  // can use reference to a variable
    std::cout<<"pair_ref: "<<pair_ref<<'\n';
    
    s1="demir";                                                 // if the variable change pair is changed to
    std::cout<<"pair_ref: "<<pair_ref<<'\n';
    
    std::tuple<std::string&>t3(s1);                             // if tuple refers to a variable it has to be know during compile time
    std::cout<<"t3: "<<std::get<0>(t3)<<'\n';
    
    std::get<0>(t3)+=" & semos";                                // get<>() can be used to modify tuple elements
    std::cout<<"Revised t3: "<<std::get<0>(t3)<<'\n';
    
    f({30, "didem"});                                            // f() gets a pair using initializer lists
    
    auto p6=std::make_pair('s', 'p');
    char c{};
    std::tie(std::ignore, c)=p6;                                 // std::tie binds the elements of pair to specified variable
    std::cout<<"c:"<<c<<", p6="<<p6<<'\n';                      // std::ignore ignores the value
                                                                
                                                                
    auto [u, v]=p6;                                             // structured bindings can be used with C++17                                           
    std::cout<<"u: "<<u<<", v:"<<v<<'\n';                      
    
    auto p7 =std::make_pair(std::move(u), std::move(v));
    
    std::cout<<"p7= "<<p7<<'\n';
    
    
    std::tuple<int, float, std::string>t5={4, 4.22, "demir"};                // copy initialization and returning from a  function 
    std::cout<<"Printing t5= "<<t5<<'\n';                                                                            // via list was not working until C++17; now works
                                                                            //std::make_tuple() was used to return from a function before C++17 
    std::vector<std::tuple<int, float>>vec2={{1,2.2}, {2, 3.4}};
    
    for(const auto& elem:vec2)
        std::cout<<std::get<0>(elem)<<", "<<std::get<1>(elem)<<'\n';
        
    int n{5};
    
    auto tt=std::tuple_cat(std::make_tuple(42, 4.7, "demir"), std::tie(n)); // std::tuple_cat combines several tuples into one
    std::cout<<std::tuple_size<decltype(tt)>::value<<'\n';                        // std::tuple_size return the number of types
                                                                            // decltype() return the type of a variable, expression, function..etc
                                                                                // Inspects the declared type of an entity or the type and value category of an expression
    
    std::cout<<"Printing tuple tt= "<<tt<<'\n';
    
    return 0;                                                   
    
}
