#include <iostream>
#include <array>

/* Example for template overloading and the order of overloading
// matters when the compiler determines which version to use
// if there is a specialization then it must be before the generic overload
// otherwise the compiler will use the generic before it gets to speciliazed version
// in this case we max for two argument both with generic type T and with int
// when we cal for 3 ints then the compiler will search for the max overload for the first two 
// and there are 2 overloads; one with type T and one with int
// compiler will find the generic one it matches and will use it
// if the int version of the compiler is defined before the generic then the compiler
// would use int version
*/

// 2nd version; if the specialized overload is defined before the generic overload
// then compiler will use the specialized version 
int max(int a, int b)
{
    std::cout<<"using max(int a,int b)...\n";
    return b<a ? a:b;
}

template<typename T>
T max(T a, T b)
{
    std::cout<<"using max<T>(a,b)...\n";
    return b<a ? a:b;
}

template<typename T>
T max(T a, T b, T c)
{
    std::cout<<"using max<T>(a,b,c)...\n";
    return max(max(a,b), c);
}

//int max(int a, int b)
//{
//    std::cout<<"using max(int a,int b)...\n";
//    return b<a ? a:b;
//}

// if you plan to use your function in a compile time
// function or statement such std:: array<> size declaration 
// or static_assert() or raw array[size]...
// then using constexpr can be used otherwise
// if you are using for runtime only not needed; optional
template<typename T1, typename T2>
auto constexpr max(T1 a, T2 b)
{
    return b<a ? a:b;
}

int main()
{
    std::cout<<"max: "<<::max(47,11, 33)<<'\n';
    
    std::array<int, ::max(sizeof(char), 1000u)>arr;       // 1000 is defined as unsigned not to cause a warning
    std::cout<<"array size(): "<<arr.size()<<'\n';       // since sizeof(char) is unsigned int     
    
/*Summary for Template Functions;
//  • Function templates define a family of functions for different template arguments.
//  • When you pass arguments to function parameters depending on template parameters, 
//  function templates deduce the template parameters to be instantiated 
//  for the corresponding parameter types.
//  • Youcanexplicitlyqualifytheleadingtemplateparameters.
//  • You can define default arguments for template parameters. 
//  These may refer to previous template
//  parameters and be followed by parameters not having default arguments.
//  • Youcanoverloadfunctiontemplates.
//  • Whenoverloadingfunctiontemplateswithotherfunctiontemplates,youshouldensurethatonly
//  one of them matches for any call.
//  • Whenyouoverloadfunctiontemplates,limityourchangestospecifyingtemplateparameters
//  explicitly.
//  • Ensurethecompilerseesalloverloadedversionsoffunctiontemplatesbeforeyoucallthem.
*/
    return 0;
}
