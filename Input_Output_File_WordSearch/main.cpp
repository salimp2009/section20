#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <ios>
#include <iomanip>
#include <tuple>
#include <functional>


// this does not give the result; not an optimal way to do it but need to try to search bgger files
// with parallel algorithms
void my_search_word(std::string_view line, std::string_view search_word, int& total_searched, int& total_found) 
{
   ++total_searched;
    auto pos=std::search(std::begin(line), std::end(line), 
                         std::begin(search_word), std::end(search_word),
                        [&](const auto& elem, const auto& search) { 
                            return elem==search;});
    while(pos!=std::end(line)) 
    {
        std::cout<<"found: "<<line<<'\n';
        ++total_found;
        ++pos;
        pos=std::search(pos+search_word.size(), std::end(line), 
                        std::begin(search_word), std::end(search_word),
                        [&](const auto& elem, const auto& search) { 
                            return elem==search;});
    }
        
}

std::size_t searching_word(std::string_view line, std::string_view search_word) {
     
      return line.find(search_word);
}


int main()
{

    std::ifstream file("../romeoandjuliet.txt");
    
    if(!file) {
        std::cerr<<"file reading problems...\n";
        return -1;
    }
    
    std::ofstream ofs("../romeoandjulietCopy.txt");
    
     if(!ofs) {
        std::cerr<<"outfile creating problems...\n";
        return -2;
    }
    
    std::cout<<"Please enter the word to search for: ";
    std::string search_word{};
    std::cin>>search_word;
    
    std::string line{};
    
    int total_searched{0};
    int total_found{0};
    
    while(file>>line) {
//        auto n=searching_word(line, search_word);
//        if(n!=std::string::npos) ++total_found;
//        ++total_searched;
        
        // alternative;
        my_search_word(line, search_word, total_searched, total_found);
    }
    
    std::cout<<"Searched for: "<<search_word<<'\n';
    std::cout<<"Found: "<<total_found<<" times"<<'\n';
    std::cout<<"Total searched: "<<total_searched<<'\n';
    
    file.clear();
    file.seekg(0, std::ios::beg);
    std::cout<<file.tellg()<<'\n';            // check the current read position is at the begining
    
    std::size_t lineNo{0};
//     while(std::getline(file, line)) {
//            ++lineNo;
//            ofs<<lineNo<<'\t'<<line<<'\n';
//         }

// Alternative; no line numbers on empty/blank lines         
    while(std::getline(file, line)) {
        if(line=="" | line=="\r") {            // Windows uses different delimiters; need to add \r
            std::cout<<std::boolalpha<<"line empty(): "<<line.empty()<<'\n';
            ofs<<'\n';
        } else {
            ++lineNo;
            ofs<<lineNo<<'\t'<<line<<'\n'; 
        }
    }
    
    file.close();
    
    return 0;
}
