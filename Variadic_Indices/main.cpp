#include <iostream>
#include <vector>
#include <utility>

template<typename Cont, typename... Idx>
constexpr void printElems(Cont const& coll, Idx... idx) {
    ((std::cout<<coll[idx]<<' '), ...)<<'\n';
}

template<std::size_t... Idx, typename Cont>     // nontype parameter Idx is passes as template parameter
constexpr void printElems(Cont const& coll) {
    ((std::cout<<coll[Idx]<<' '), ...)<<'\n';
}


int main()
{
    std::vector v1{1,5,7,9,13};
    printElems(v1, 0,1,3);          // will print the passed collection w/ the given index numbers
    printElems<0,1,3>(v1);          // the Index number has to be passed inside function type and collection is passed as argument
    
    
    return 0;
}
