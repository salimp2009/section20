#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cctype>
#include <string>
#include <iomanip>

bool is_palindrome(const std::string& word) {
    std::stack<char>words;
    std::queue<char>words_rev;
    for(char c:word) {
        if(std::isalpha(c)) {
            words.push(std::toupper(c));
            words_rev.push(std::toupper(c));
        }
    }
    
    while(!words.empty()) {
        if(words.top()!=words_rev.front()) return false;
        words.pop();
        words_rev.pop();
    }
    return true;
}

int main()
{
    std::vector<std::string> test_strings{ "a","aa","aba","abba","abbcbba","ab","abc","radar",
            "bob", "ana","avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
            "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!","This is a palindrome","palindrome" };
    
    std::cout<<std::boolalpha;
    std::cout<<std::setw(10)<<std::left<<"Result"<<"String\n";
    for(const auto& s:test_strings)
        std::cout<<std::setw(10)<<std::left<<is_palindrome(s)
             <<" "<<std::left<<s<<'\n';
    std::cout<<'\n';
             
 
 return 0;
}