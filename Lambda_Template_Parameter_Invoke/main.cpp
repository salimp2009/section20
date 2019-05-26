#include <iostream>

template<typename T>
void call_with_zero(T&& f) { f(0);}

void foo(int a) { std::cout<<"\nfoo is working with value :"<<a; }

struct Bar
{
  //  void print(int a) {std::cout<<"\nBar called out value: "<<a<<'\n'; }
    
    void print() {std::cout<<"\nOverloaded Bar called out with no value: "<<'\n'; }
};

void call_member_function2(std::function<void(Bar)>f)
{
   // Bar b;
    f(Bar{});
}

//template<typename F>
//void call_member_function(F&& f, int a)
//{
//    Bar b;
//    std::invoke(f, b, a);
//}

// Alternative to std::invoke that can take any callable object


int main()
{
    // call_member_function(&Bar::print, 5);
    
    call_member_function2(&Bar::print);
    
    call_with_zero(foo);
    
    auto l = [](int a) {std::cout<<"\nLambda called with value: "<<a<<'\n'; };
    
    call_with_zero(l);
    
    call_with_zero([i=0](int a) mutable {std::cout<<"\nLambda called with value: "<<a+i<<'\n'; });
    
 
 
 return 0;
}