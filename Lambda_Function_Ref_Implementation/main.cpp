#include <iostream>
#include "Function_ref.hpp"
//#include "function_ref_org.hpp"


int foo(function_ref<int()>f)
{
    return f();
}

int main()
{
    auto l = [i=0]()mutable { return i++;};
    foo(l);
    foo(l);
    foo(l);
 
 return foo(l);
}