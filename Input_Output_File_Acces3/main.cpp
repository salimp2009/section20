#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ios>
#include <iomanip>
#include <bitset>
#include <cstdint>
#include <algorithm>
#include <string_view>
#include <tuple>

struct Student {

    std::string name;
    std::uint32_t score;
};

std::uint32_t check_response(std::string_view key, std::string_view response) {
    uint32_t score{0};
    std::search(std::begin(response), std::end(response),
                std::begin(key),  std::end(key),
               [&score](const char& res, const char& ky ){ 
                if(res==ky) ++score;    
                return 1;} ); 
    return score;
}

void print_header() {
   std::cout<<std::setw(17)<<std::left<<"Student Name"
             <<std::setw(5)<<std::right<<"Score"<<'\n';
}

int main()
{
    std::ifstream ifs("../poem.txt");
    std::ofstream ofs("../poemCopy.txt");
    if(!ifs) {
        std::cout<<"file does not exist...\n";
        return -1;
    }
    
     if(!ofs) {
        std::cout<<"cannot create output file...\n";
        return -2;
    }
    
    std::string line{};
    int lineNo{0};
    while(std::getline(ifs, line)) {
        ++lineNo;
        std::cout<<line<<'\n';
        ofs<<lineNo<<'\t'<<line<<'\n';
    }
    ifs.clear();
    ifs.close();
    ofs.close();
    
//    std::ifstream file("../responses.txt");
//    
//    if(!file) {
//        std::cerr<<"file reading problems..\n";
//        return -2;
//    }
//    
//    std::string key;
//    file>>key;
//    std::cout<<"key: "<<key<<'\n';
//    
//    Student student{};
//    std::vector<Student>students{};
//    std::vector<std::pair<std::string, int>>students2{};
//    
//    
//    std::string name{};
//    std::string response{};
//    std::uint32_t score{0};
//    while(file>>name>>response) {
//        std::cout<<name<<", response: "<<response<<'\n';
//        score=check_response(key, response);
//        students.emplace_back(Student{name, score});
//        students2.emplace_back(name, score);                // pair alternative just for exercise
//    }
//    
//    print_header();
// 
//    for(const auto& [name, score]: students)
//            std::cout<<std::setw(15)<<std::left<<name
//                    <<std::setw(5)<<std::right<<score<<'\n';
//    print_header();        
//    for(const auto& [name, score]: students2)
//            std::cout<<std::setw(15)<<std::left<<name
//                    <<std::setw(5)<<std::right<<score<<'\n';
//    
//    file.close();
    
    
    return 0;
}
