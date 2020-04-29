#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <type_traits>
#include <functional>
#include <set>
#include <map>
#include <utility>
#include <fstream>
#include <sstream>
#include <string_view>

// TO BE USED with any container std::cont<T>
// e.g; std::set or list
template<typename Cont>
void display(const Cont& cont) 
{
    for(const auto& elem: cont)
      std::cout<<elem<<" ";
    std::cout<<'\n';
}



template<typename T1, typename T2>
void display3(const std::map<T1, T2>& cont) 
{
    for(const auto& elem: cont)
        std::cout<<"Key: "<<elem.first<<", Value: "<<elem.second<<'\n';
    std::cout<<'\n';
}


// to be used with std::map<std::string, std::set<T>
template<typename T1, typename T2>
void display4(const std::map<T1, T2>& cont) 
{
    for(const auto& elem: cont) {
        std::cout<<"Key: "<<elem.first<<":";
        display(elem.second);
    }
    std::cout<<'\n';
}

std::string clean_word(std::string_view word) {
    std::string result;
//    for(auto& c:word) {
//        if(c!=';' && c!=':' && c!='.' && c!=',')
//            result+=c;
//    }
    
    std::for_each(word.cbegin(), word.cend(), 
                    [&result](const auto& c){ if(c!=';' && c!=':' && c!='.' && c!=',') 
                                            result+=c;} );
    return result;
}

void part1()
{
   std::ifstream file("../words.txt");
   
   if(!file) {
       std::cerr<<"File does not exist!...\n";
       return;
   }
    
    std::map<std::string, int>words;
    std::map<std::string, std::set<int>> words2;
    std::string line{};
    std::string word{};
    int line_count{0};
    
    while(std::getline(file, line))
    {
        ++line_count;
        std::stringstream ss(line);
        while(ss>>word) 
        {
            word=clean_word(word);
            words[word]++;
            words2[word].insert(line_count);
        }
    }
    //display3(words);
    display4(words2);
    file.close();
}


int main()
{
    part1();
    //part2();          // not used 

    return 0;
}
