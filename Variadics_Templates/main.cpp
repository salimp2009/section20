#include <iostream>

template<typename T>
constexpr void print(T&& arg) {
    std::cout<<arg<<'\n';
}


template<typename TFirst, typename...TArgs>
constexpr void print(TFirst&& firstArg, TArgs&&... args)
{
    print(std::forward<TFirst>(firstArg));              // will call print() for the arg 
    print(std::forward<TArgs>(args)...);                // print() will be called for each argument one by one
    
    std::cout<<"number of remaining types: "<<sizeof...(TArgs)<<'\n';
    std::cout<<"number of arguments:       "<<sizeof...(args)<<'\n';
}

template<typename... T>
constexpr void printAll(T&&... args) {
    ((std::cout<< args <<' '), ... )<<'\n';
}

// using compile-time if; C++17 feature
// if constexpr()
template<typename TFirst, typename...TArgs>
constexpr void printCompIf(TFirst&& firstarg, TArgs&&... args) 
{
    std::cout<<firstarg<<' ';
    if constexpr(sizeof...(args)>0) 
        printCompIf(args...);
}

int main()
{
    print(5, 'c', std::string("Salim"), 5.7);
    printAll(25, 'd', std::string("Demir"), 77.7889);
    printAll(75);
    
    std::cout<<"Compile time if constexpr()"<<'\n';
    printCompIf(425.45, 'd', std::string("Demir"), 777889);
    
    std::cout<<'\n';
    return 0;
}
