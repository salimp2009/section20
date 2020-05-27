#include <iostream>
#include <array>
#include <type_traits>


template<auto N> 
class S 
{ 
    public:
    typedef decltype(N) type;
    std::array<type, N> elems;

};

template<typename T, auto N>
class A
{
public:
  A()=default;
  A(const std::array<T, N>&) { }  
  A(T(&)[N]) { }
    
};

int main()
{
    S<42> s1{{42,5}};
    std::cout<<std::boolalpha<<std::is_same_v<decltype(s1)::type, S<5>::type ><<'\n';   // returns true
    
    
    A a1{"hello"};      // the type of a1 is deduced as A<const char, 6>
    
    std::array<double, 5> arrayDouble;
    A a2{arrayDouble};  // the type of a2 is deduced as A<double, 5>
    
    
    return 0;
}
