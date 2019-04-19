#include <iostream>
#include <fstream>
#include <string>


int main()
{
    std::ifstream in_file{"../poem.txt"};               // '../peom.txt' is used since Codelite12 working directory structure
    std::ifstream in_file2{"../poem.txt"};              // no need to use the extra  ../
    std::ofstream out_file{"../poem_out.txt"};
    std::ofstream out_file2{"../poem_out2.txt"};
    
    
    if(!in_file){
        std::cerr<<"\nError openning input file...\n";
        return 1;
    }
    
    if(!out_file) {
        std::cerr<<"\nError openning output file...\n";
        return 2;
    }
    
    if(!out_file2) {
        std::cerr<<"\nError openning output file...\n";
        return 3;
    }
    
    std::string line{};
    while(std::getline(in_file, line)) {
        out_file<<line<<'\n';
    }
    
    char c;
    while(in_file2.get(c)) {
        out_file2.put(c);
    }  
 
    std::cout<<"\nFiles Copied...\n";
    
    in_file.close();
    out_file.close();
    in_file2.close();
    out_file2.close();
    
 return 0;
}