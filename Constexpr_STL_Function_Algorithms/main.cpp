#include <iostream>
#include <array>
#include <string_view>
#include <tuple>

// Example of Constexpr for creating Compile time and Run time functions

template<std::size_t N>
constexpr std::size_t count_true(const std::array<bool, N>& a)
{
    std::size_t result{0};
    for(const auto& elem: a)
        if(elem) ++result;
    return result;
}

constexpr auto parse_person(std::string_view s)
{
    const auto mid=s.find_first_of(';');
    return std::make_tuple(s.substr(0, mid), s.substr(mid+1, s.size()-mid));
    
}


int main()
{
    constexpr auto name="Bjarne;Stroustrup";
    
    constexpr auto fst_name=std::get<0>(parse_person(name));
    constexpr auto lst_name=std::get<1>(parse_person(name));
    
    static_assert(fst_name==std::string_view("Bjarne"));
    static_assert(lst_name==std::string_view("Stroustrup"));
    
static_assert(count_true(std::array{true, false, true, false})==2);
 
 return 0;
}