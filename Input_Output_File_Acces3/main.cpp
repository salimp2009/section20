#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ios>
#include <iomanip>
#include <bitset>


int main()
{
    std::ifstream ifs("../poem.txt");
    
    if(!ifs) {
        std::cout<<"file does not exist...\n";
        return -1;
    }
    
    std::string line{};
    while(std::getline(ifs, line)) {
        std::cout<<line<<'\n';
    }
    ifs.clear();
    ifs.seekg(0);
    std::cout<<ifs.tellg()<<'\n'; 
   
    char c;
    while(ifs.get(c)) {
        std::cout<<c;
    }
    
    ifs.close();
    
    return 0;
}
