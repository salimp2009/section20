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
    
    
}


int main()
{
    

 
 return 0;
}