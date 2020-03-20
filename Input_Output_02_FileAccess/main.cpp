#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ios>
#include <iomanip>
#include <bitset>

int main()
{
    std::ifstream ifs("../input_file.txt");
    
    if(!ifs) {
        std::cerr<<"File does not exist..!!!\n";
        return -1;
    }
    
    // redirect buffer to from read file stream (ifs) to std::cout
    std::cout<<ifs.rdbuf()<<'\n';
    
    ifs.seekg(0, std::ios::beg);
    
    
    std::ofstream osf("../output_file.txt");
    
    double num{0};
   while(ifs>>num) {
        std::cout<<num<<" ";
        osf<<num<<" ";
   }
   
   std::cout<<'\n';
   
   ifs.close();
   osf.close();
   
 
    
    return 0;
}
