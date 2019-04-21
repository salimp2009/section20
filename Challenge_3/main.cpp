#include <iostream>
#include <map>
#include <algorithm>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>


template<typename T1, typename T2>
void display(const std::map<T1, T2>& m) {
    std::cout<<std::setw(12)<<std::left<<"\nWord"
             <<std::setw(7)<<std::right<<"Count\n";
    std::cout<<"=================================\n";
    for(const auto& elem:m) 
        std::cout<<std::setw(12)<<std::left<<elem.first
                 <<std::setw(7)<<std::right<<elem.second<<'\n';
    std::cout<<'\n';
}

void display(const std::map<std::string, std::set<int>>& words) {
    std::cout<<std::setw(12)<<std::left<<"\nWord"
             <<"Occurences\n";
    for(const auto& elem:words) {
        std::cout<<std::setw(12)<<std::left<<elem.first
                  <<std::left<<"[";
        for(const auto& set_elem:elem.second) {
            std::cout<<set_elem<<" ";
        }
        std::cout<<"]\n";
    }
}

std::string clean_string(const std::string& s) {
    std::string result{};
    
    for(char c:s) {
        if(c!=':' && c!=';' && c!='.' && c!=',')
            result+=c;
    }
    return result;
}



void part1(){
    std::ifstream in_file("../words.txt");
    if(!in_file) {
        std::cerr<<"\nError openning input file...\n";
        return;
    }
    
    std::string line{};
    std::string word{};
    std::map<std::string, int>words;
    while(std::getline(in_file, line)){
       std::stringstream ss(line);
       while(ss>>word) {
           word=clean_string(word);
           words[word]++;         //[] operator returns reference to the value and it is incremented 
       }                                // since it is a map if the word exists, it update the value otherwise
                                        // new word is added and default value zero is incremented to 1
    }
    display(words);
    in_file.close();
}

void part2() {
    std::ifstream in_file("../words.txt");
    if(!in_file) {
        std::cerr<<"\nError openning input file...\n";
        return;
    }
    
    std::string line{};
    std::string word{};
    std::map<std::string, std::set<int>>words;
    int line_count{0};
    while(std::getline(in_file, line)){
        ++line_count;
       std::stringstream ss(line);
       while(ss>>word) {
           word=clean_string(word);
           words[word].insert(line_count);
       }
    }
    
    display(words);
    in_file.close();
}

int main()
{
    part1();
    part2();
 return 0;
}