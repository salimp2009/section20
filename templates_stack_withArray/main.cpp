#include <iostream>
#include "StackArray.hpp"
#include <string>
#include <vector>
#include <algorithm>

/*Summary;
// Templates can have templat eparameters that are values rather than types.
// You cannot use floating-point numbers or class-type objects as arguments for nontype template parameters. 
// For pointers/references to string literals, temporaries, and subobjects, restrictions
// apply.
// Using auto enables templates to have nontype template parameters that are values of generic types
*/ 

// example for nontype parameters
// restrictions apply; no doub or floating values; no string literals
// only integral value(including enumerations), pointers to objects/functions/member, 
// lvalue references to objects or function or std::nullptr_t(type of nullptr)
template<auto Val, typename T=decltype(Val)>
T addValue(T x) {
    return Val+x;
}

template<typename T, auto VAT>
double process(T v) {
    return v*VAT;
}

// if pointers to object or refences are used in the template argument
// there are several restrictions; no string literal
// and need to have external or internal linkage
template<char const* name>
class MyClass {
    
};

// arguments for nontype parameters can be any compile time extensions
template<int I, bool B>
class C {
    
};

extern char const s03[]="hi";                  // external link
const char s04[]="HI";                         // internal lnk

int main()
{
 [[maybe_unused]]   C<sizeof(int)+4, sizeof(int)==4>c1;
 [[maybe_unused]]   C<sizeof(int)+4, (sizeof(int)>4)>c2;
    
    
   // MyClass<"hello">x;                       // string literal not allowed for non type parameter
  [[maybe_unused]]  MyClass<s03>x1;            // s03 have external linkage so it is OK
  [[maybe_unused]]  MyClass<s04>x2;
    
    
    std::cout<<addValue<5>(20)<<'\n';
    
    std::cout<<process<double, 5>(20.56);       // typename T ; can be any type but VAT cannot be double
                                                // because is defined as nontype parameter so restrictions apply
    std::vector<int>source{1,2,3,4,5,7,8,910};
    std::transform(source.begin(), source.end(),   // source 
                    source.begin(),                // destination; if it is source than the source wiil be changed 
                    addValue<5>);                            
    
    for(const auto& elem:source)
        std::cout<<elem<<" ";
    std::cout<<'\n';
    
    
    Stack<int, 5u>stckArr1;

    Stack<int, 5u>stacklist{1,2,3,4};
    std::cout<<"stacklist with variad args: "<<stacklist<<'\n';
    
    stckArr1.push(20);
    stckArr1.push(50);
    stckArr1.push(60);
    stckArr1.push(70);
    stckArr1.push(88);
    
   Stack<int, 5u>stckArr2(stckArr1);
   std::cout<<stckArr2<<'\n';
   
   stckArr1.pop();
   std::cout<<stckArr1.top()<<'\n';
   std::cout<<stckArr1<<'\n';
    
   Stack<std::string, 10> stringStack;
   stringStack.push("Salim");
   stringStack.push("Didem");
   stringStack.push("Demir");
   stringStack.push("Sema");
   
   std::cout<<stringStack<<'\n';
   std::cout<<stringStack.top()<<'\n';


    return 0;
}
