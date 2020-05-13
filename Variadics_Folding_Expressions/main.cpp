#include <iostream>
#include <string>
#include <complex>
#include <optional>

template<typename... T>
constexpr void foldsumLeft(T... args)
{
    if constexpr(sizeof... (args)==0) 
        std::cout<<"empty pack result : "<<0<<'\n';
    else
        std::cout<<"sum of Left Folding: "<<(args+ ...)<<'\n';                     // expands to s+ ...(s3+(s1+s2))
}

template<typename... T>
constexpr void foldsumRight(T... args)
{
    if constexpr(sizeof... (args)==0) 
        std::cout<<"empty pack result : "<<0<<'\n';
    else
        std::cout<<"sum of Right Folding: "<<(... +args)<<'\n';                    // expands to ((s1+s2)+s3)... +s
}

template<typename... T>
constexpr void foldDoubled(T... args)
{
    if constexpr(sizeof... (args)==0) 
        std::cout<<"empty pack result : "<<0<<'\n';
    else
        std::cout<<"sum of Doubled Folding: "<<((args+args)+ ...)<<'\n';                    
}

template<typename... T>
constexpr void printDouble(T&&... args) {
    if constexpr (sizeof... (args)!=0)
        ((std::cout<<args+args<<' '), ...)<<'\n';
    else
        std::cout<<"empty list:nothing to print...\n";
}

template<typename T1, typename... TN>
constexpr bool isHomogeneous(T1, TN...) {
    
    return (std::is_same_v<T1, TN> && ...);
}


// DONT DO THE FOLDING Expression like this !!!
// When you print the expression evaluate 1<<'\n'
// which means left shift 10 bits (ASCI value of n)
// '\n' out of paranthesis whether you use left  fold or right fold
template<typename... T>
constexpr std::optional<int> printAny(T&&... args)
{
    if constexpr (sizeof...(args)!=0)
       std::cout<<(args<< ... <<'\n');      // do not put '\n' inside the paranthesis 
                                            // it might evaluate wrong/unexpected results
    return false;
}


int main()
{

    std::cout<<std::boolalpha<<isHomogeneous(43, -1, "HELLO")<<'\n';
    std::cout<<std::boolalpha<<isHomogeneous("Salim", " ", "HELLO")<<'\n';
    
    foldsumLeft(1, 3, 4, 5);
    foldsumLeft(1);
    foldsumRight(12.35, 45.55, 65);
    foldsumRight();
    
    foldDoubled(1, 3, 4, 5);
    
    using namespace std::literals;
    printDouble(7.5, "hello"s, std::complex<float>(4,2));
    printAny(1);
    
    return 0;
}
