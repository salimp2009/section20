#include <iostream>
#include <vector>
#include <utility>
#include <array>

template<typename Cont, typename... Idx>
constexpr void printElems(Cont const& coll, Idx... idx) {
    ((std::cout<<coll[idx]<<' '), ...)<<'\n';
}

template<std::size_t... Idx, typename Cont>     // nontype parameter Idx is passes as template parameter
constexpr void printElems(Cont const& coll) {
    ((std::cout<<coll[Idx]<<' '), ...)<<'\n';
}


template<typename Cont, std::size_t... Indx>
auto printAll_impl(const Cont& cont, std::index_sequence<Indx...>)
{
    ((std::cout<<cont[Indx]<<' '), ...)<<'\n';
    
}

template<typename Cont>
auto printAllElems(const Cont& cont)
{
  //  auto size=cont.size();
    

    constexpr auto size=((sizeof cont)-1) / sizeof(typename Cont::value_type);
    std::cout<<"printAll: "<<size<<'\n';
    printAll_impl(cont, std::make_index_sequence<size>{});
}


int main()
{
    std::vector v1{1,5,7,9,13};
    printElems(v1, 0,1,3);          // will print the passed collection w/ the given index numbers
    printElems<0,1,3>(v1);          // the Index number has to be passed inside function type and collection is passed as argument
    
    
    std::array<int, 4> arr1{11,14,15,17};
    
[[maybe_unused]]    int arr[4]={11,13,15,17};
    printAllElems(v1);
printAllElems(arr1);
    
    return 0;
}
