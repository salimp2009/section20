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
 
    std::copy_if(s.begin(), s.end(),
              std::back_inserter(d),
              [](unsigned char elem){ return std::isalpha(elem);});  
    
    return std::equal(d.begin(), d.end(),
                      d.rbegin(),
                      [](unsigned char x, unsigned char y){ return std::toupper(x)==std::toupper(y) ; });  
}


int main()
{
    
    std::vector<std::string> test_strings{ "a","aa","aba","abba","abbcbba","ab","abc","radar",
            "bob", "ana","avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
            "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!","This is a palindrome","palindrome" };
        
        std::cout<<std::boolalpha;
        std::cout<<std::setw(8)<<std::left<<"Test"<<"String"<<std::endl;
        for(const auto& s:test_strings) {
            std::cout<<std::setw(8)<<std::left<<is_palindrome(s)<<s<<std::endl;
        }
        std::cout<<'\n';
 
 
 return 0;
}