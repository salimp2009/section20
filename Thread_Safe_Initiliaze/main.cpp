#include <iostream>

// Examples of Thread-Safe Initiliasation;

// There are three ways in C++ to initialise variables in a thread-safe way.
// • Constant expressions
// • The function std::call_once in combination with the flag std::once_flag 
// • A static variable with block scope


// User defined types can also be constant expressions. 
// For those types there are a few restrictions that must be met 
// to initialise it at compile time;
// • They must not have virtual methods or a virtual base class.
// • Their constructor must be empty and itself be a constant expression.
// • Every base class and each non-static member must be initialized.
// • Their methods, which should be callable at compile time, must be constant expressions.

class MyDouble {
private:
    double myVal1;
    double myVal2;
public:
    constexpr MyDouble(double v1, double v2): myVal1{std::move(v1)}, myVal2{std::move(v2)} { }
    constexpr double getSum() const {return myVal1+myVal2;} 
};


int main()
{
    constexpr double myval=2.2;
    constexpr MyDouble mydouble(5.4, myval);
    constexpr double sum=mydouble.getSum();
    std::cout<<sum<<'\n';
 return 0;
}