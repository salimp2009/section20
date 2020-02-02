#include <iostream>
#include <string>
#include "max1.hpp"
#include <complex>
#include <type_traits>


// default value for the template parameter can defined
// if a function is instantiated with no argument
// then the template can not automatically deduce the type
// therefore it gives and error but when we define a default type for parameter
// then the function can be instantiated without any argument
template<typename T=std::string>
void f(T s=" ") { }

// if two different types are used we define template for as many parameter as needed
// but the return type can either be auto deduced or use common_type traits or define another
// paramater for return type
// template auto has its own rules; it always decays which means it the type has 'const' specifier or is a reference
// those are ignore and just plain type is used
// alternatives are using std:: decay and decltype to determine the type and use conditional statement with a true
// value

// alternative with decltype and decay
// template<typename T1, typename T2>
// auto max(T1 a, T2 b)->typename std::decay<decltype(true?a:b)>::type  //-> operator specifies the return type
// {                                                                   // true?a:b is enough to determine since it 
//                                                                     // it is declaration and compiler uses true case   
//     return a > b ? a:b;                                            // for declaration for type but true case will be determine
//                                                                    // when values are passed
// }
//template<typename T1, typename T2>
//auto max(T1 a, T2 b)
//{
//    return a > b ? a:b;
//}

// 2nd alternative to auto is to use std::common_type<>::tpye from type traits
//template<typename T1, typename T2>
//typename std::common_type<T1,T2>::type  max(T1 a, T2 b)
//{
//    return a > b ? a:b;
//}

// 3rd alternative is to use return type with default value using common_type or 
// std:decay<decltype()>::type or alias std::decay_t<decltype()>
// std::common_type_t is an alias for std::common_type<>::type
// std::common_type also decays therefore references or const specifiers are removed

template<typename T1, typename T2,
       // typename RT=std::common_type_t<T1, T2>>     
      typename RT=std::decay_t<decltype(true?T1():T2())>> // T1() calls default contructor for type T1 
RT max(T1 a, T2 b)
{
    return a > b ? a:b;
}

int main()
{
    f(1);
    f();            // when no argument is passed the template can still instantiate  
                    // with the default value

    
    // max is defined to work the same type of arguments
    // the types of value has to match otherwise compiler error
    // :: in front of max() is used to explicitly tell the compiler look for global space
    // because there is a std::max in library .  
    // if one argument type is defined in namespace std (such as std::string),
    // according to the lookup rules of C++, both the global and 
    // the max() template in std are found
    
    std::cout<<::max(3,5)<<'\n';
    
    // if two different types can be casted to each other we can specify the type tp be used
    // then the compiler will do a static_cast<> which may cause loss of data or accuracy
    
    std::cout<<::max(3,3.6)<<'\n';             // uses overloaded max with two differentt types and returns 3.6
    std::cout<<::max<double>(3,3.6)<<'\n';     // returns 3.6
    std::cout<<::max<double, int, long double>(7.2, 4)<<'\n'; // implicityl specify the return type as long double
    
    
    std::cout<<::max("salim", "Didem")<<'\n';          // return the lexical order
    std::cout<<::max("Demir", "didem")<<'\n';          // returns didem; lexical comparision is  case sensitive 
                                                       // lower case comes before the capital ones
    std::string name1{"Salim"};
    std::string name2{"Demir"};
    
    std::cout<<::max(name1, name2)<<'\n';
    
    const int i2{20};
    std::cout<<::max(18,i2)<<'\n';                  // i2 will deduced as int for the template parameter
    
    const int& ir=i2;
    std::cout<<::max(ir,i2)<<'\n';              // both ir and i2 will be deduced as int in template
    
    // this gives compiler error since types dont match const char* versus string
    // therefore we have to specify the type of max<type>() 
    // and it const char* will be converted to string
    std::cout<<::max<std::string>("salim", name1)<<'\n';
    
    
    // for each call compiler instantiante an instance of the template for the given type
    // Note also that void is a valid template argument provided the resulting code is valid
    


// complex number does not support > operation therefore this will not compile
//    std::complex<float>c1, c2;
//    c1={1.2, 3.5};
//    c2={2.4, 4.6};
//    std::cout<<::max(c1, c2);

/* Thus, templates are “compiled” in two phases:
// 1. Without instantiation at definition time, the template code itself is checked for correctness 
//    ignoring the template parameters. This includes:
//  – Syntaxerrorsarediscovered,suchasmissingsemicolons.
//  – Using unknown names (type names, function names, ...) that don’t depend on template 
//    parameters are discovered.
//  – Staticassertionsthatdon’tdependontemplateparametersarechecked.
// 2. At instantiation time, the template code is checked (again) to ensure 
//    that all code is valid. That is, now especially, all parts that depend
//    on template parameters are double-checked.
*/                                                
    return 0;
}
