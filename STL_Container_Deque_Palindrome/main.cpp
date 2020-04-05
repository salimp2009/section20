#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <cctype>
#include <string_view>
#include <iomanip>
#include <type_traits>

bool is_palindrome(std::string_view sv)
{
    std::deque<char>deq;
   
    for(const auto& c:sv) {
        //if(std::is_integral_v<decltype(c)>) {
        if(std::isalpha(c)) 
            deq.push_back(std::toupper(c));
    }
    char c1{};
    char c2{};
    while(deq.size()>1) {
        c1=deq.front();
        c2=deq.back();
        deq.pop_back();
        deq.pop_front();
        if(c1!=c2) return false;
    }
     return true;   
}

int main()
{
        std::vector<std::string> test_strings{ "a","aa","aba","abba","abbcbba","ab","abc","radar",
            "bob", "ana","avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
            "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!","This is a palindrome","palindrome" };

    for(const auto& s:test_strings)
        std::cout<<std::setw(20)<<std::left<<s<<' '
                 <<std::boolalpha<<std::setw(5)<<std::right<<is_palindrome(s)<<'\n';
    std::cout<<'\n';

    return 0;
}
