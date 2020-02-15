#include <iostream>
#include <string>
#include <cstring>


// maximum of two values-call by value
template<typename T>
T const& max(T const &a, T const& b)
{
    return b<a ? a:b;
}

// max of C-style strings-call by value
const char* max(const char* a, const char* b)
{
    return std::strcmp(b,a)<0 ? a:b;
}


// maximum of three values-call by value
template<typename T>
T const& max(T const& a, T const& b, T const& c)
{
    return ::max(max(a,b),c);
}

int main()
{
[[maybe_unused]]    auto m1=::max(7, 42, 68);           // Compiles ok; max(7,42) is called and return a temp value and 
                                                        // the temporaries are created in the main therefore it does not create
                                                        // a problem 
const char* s1{"demir"};
const char* s2{"didem"};
const char* s3{"semos"};

                   auto m2=::max(s1, s2, s3);
                   std::cout<<"m2: "<<m2<<'\n';         // the example was given for a compiler error but 
                                                        // compiler gives only a warning for returnin a reference to a temp object
                                                        // C-strings, max(a,b) creates a new, temporary local value that is returned by reference,
                                                        // but that temporary value expires as soon as the return statement is complete,
                                                        // leaving main() with a dangling reference
                                                        // passing by reference the C-style strings, raw pointer might
                                                        // become a problem therefore often pass by value is preferred
                                                        // another option is to use perferct forwarding by using 
                                                        // r-value references && and std::forward<>() then the types are passed
                                                        // and deduced correctly or make sure there is an exact match for C-style strings
                                                        // and raw pointers
    return 0;                                           




}
