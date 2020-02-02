#include <iostream>
#include <string>
#include <cstring>


//    int max(int a, int b)
//{
//    std::cout<<"Non-template f\n";
//    return b<a ? a:b;
//}

//    template<typename T>
//    T max(T a, T b)
//    {
//        std::cout<<"template f\n";
//        return b<a ? a:b;
//    }
    
//    // Example for overloading by return type
//    template<typename T1, typename T2>
//    auto max(T1 a, T2 b)
//    {
//        std::cout<<"template auto return f\n";
//        return b<a ? a:b;
//    }
//    
//    // Example for overloading by return type
//    template<typename RT, typename T1, typename T2>
//    RT max(T1 a, T2 b)
//    {
//        std::cout<<"template return type specified f\n";
//        return b<a ? a:b;
//    }
    
//    template<typename T>
//    T max(T a, T b)
//    {
//        std::cout<<"Using pass by value overload...\n";
//        return b<a ? a:b;
//    }
//    
//    template<typename T>
//    T* max(T* a, T* b)
//    {
//        std::cout<<"Using pointer overload...\n";
//        return *b<*a ? a:b;
//    }
//    
//    const char* max(const char* a, const char* b)
//    {
//        std::cout<<"Using C-string overload...\n";
//        return std::strcmp(b, a)<0 ? a:b;
//    }

// Example for perferct forwarding
    template<typename T1, typename T2>
    auto max(T1&& a, T2&& b)
    {
        std::cout<<"using perfect forwarding...\n";
         return b<a ? a:b;
    }

    template<typename T1, typename T2>
    auto callmax(T1&& a, T2&& b)
    {
        return max(std::forward<T1>(a), std::forward<T2>(b));
    }

int main()
{
    // Example for perfect forwarding
    // std::forward<T>() , when we combine these && r-value reference in a template
    // then the arguments passed into function with a conditional std::move()
    // if the argument is an l-value then it will passed by reference
    // if the argument is r-value it will moved with r-value reference(&&)
    
     int aa=7;
    int bb=42;
    
    auto pf1=::callmax(aa, bb);
    std::cout<<"pf1: "<<pf1<<'\n';
                     
    auto pf2=::callmax("salim_forward", "didem_forward");
    std::cout<<"pf2: "<<pf2<<'\n';
                     
    auto pf3=::callmax(45.3, 70);
    std::cout<<"pf3: "<<pf3<<'\n';
    
    
//[[maybe_unused]]    auto m1=::max(aa,bb);       // uses the first template 
//
//    std::string s1="salim";
//    std::string s2="didem";
//[[maybe_unused]]    auto m2=::max(s1,s2);       // uses the first template; does not convert to c-string
//
//    int* p1=&aa;
//    int* p2=&bb;
//[[maybe_unused]]    auto m3=::max(p1,p2);       // uses pointer overload
//    
//    const char* c1="Demir";
//    const char* c2="Sema";
//[[maybe_unused]]    auto m4=::max(c1,c2);       // use c-style overload; if the c-style is disabled then it uses
//                                                // pointer overload
//    
    
// examples for comparing non-template (int) function  & template function (same types)
//    ::max(7,42);            // uses nontemplate function
//    ::max(7.0, 42.0);       // uses template function
//    ::max('a', 'b');        // template function    
//    ::max<double>(7, 42);   // template function
//    ::max('a', 42.7);       // use non-template for 2 ints; char converted to int
//    ::max<>(7, 42);         // uses template although the types are int we force it to use
                            // template and use argument deduction by specifying ::max<>
// examples for return type overloading; 

//auto a=::max(4, 7.2);               // uses the first template with auto return type
//auto b=::max<long double>(7.2, 4);  // uses the second where return type is passed as template parameter
////auto c=::max<int>(4, 7.2);          // error; we force the second template but it also matches the first
//                                    // the max value is double but specify to be int so uses the 2
//                                    // the return type matches one of the types of the arguments
//auto d=::max<int>(7.2, 4);          // works OK ; uses the second template and returns 7
//                                    
//std::cout<<"a: "<<a<<", b: "<<b<<", d: "<<d<<'\n';
    return 0;
}
