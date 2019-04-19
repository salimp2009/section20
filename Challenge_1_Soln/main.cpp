#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cctype>
#include <string>
#include <iomanip>

bool is_palindrome(const std::string& s){
    std::deque<char>d;
 
    for(char c:s) {
        if(std::isalpha(c)) {
            d.push_back(std::toupper(c));
        }        
    }
    
    char c1{};
    char c2{};
    
    while(d.size()>1) {   // check all elements at front and back & remove from container 
        c1=d.front();     // if elements are equal continue if not return false
        c2=d.back();
        d.pop_front();
        d.pop_back();
        if(c1!=c2) return false;
    }
    return true;        // if there is one or zero elements left then it is a palindrome, return true
}


int main()
{
    std::vector<std::string> test_strings{ "a","aa","aba","abba","abbcbba","ab","abc","radar",
            "bob", "ana","avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
            "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!","This is a palindrome","palindrome" };
        
        std::cout<<std::boolalpha;
        std::cout<<std::setw(8)<<std::left<<"Test"<<"String"<<'\n';
        for(const auto& s:test_strings) {
            std::cout<<std::setw(8)<<std::left<<is_palindrome(s)<<" "<<s<<'\n';
        }
        std::cout<<'\n';
 
 
 return 0;
}