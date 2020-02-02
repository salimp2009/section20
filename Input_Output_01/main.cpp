#include <iostream>
#include <fstream>
#include <string>
#include <vector>
struct Points
{
// Default constructors are provided below are just optional
    Points()=default;
    Points(int x1, int y1, int z1):x{x1}, y{y1}, z{z1} { }  

  int x{0};  
  int y{0};
  int z{0}; 
  
  friend std::istream& operator>>(std::istream& ist, Points& pts) {
        ist>>pts.x>>pts.y>>pts.z;
        return ist;
    }
};


int main()
{
    constexpr const char* input_file="../input_file.txt";
   std::ifstream ifs(input_file);
    if(!ifs){
        std::cerr<<"Invalid filename..!!!!";
        return -1;
    }
    
    std::vector<Points>pnts{};
    
    Points p{};
    for(;ifs>>p;)
        pnts.push_back(p);
    ifs.close();                // close the file; if you want to re_read the file without closing
                                // it will read from where it is left therefore it will be the end of file
                                // the best way to do each reading operation in seperate functions 
    ifs.open(input_file);       // becaus then the file ifs closes and goes out of scope and you start fresh  
    
    
    std::vector<int>pnts_2;
    int x{}, y{}, z{};
 
    std::ifstream input(input_file);

    for(;ifs>>x>>y>>z;) {
        pnts_2.push_back(x);
        pnts_2.push_back(y);
        pnts_2.push_back(z);
    }
    
    for(const auto& p:pnts_2)
        std::cout<<p<<'\n';
    std::cout<<'\n';
    
    for(const auto& p:pnts)
        std::cout<<p.x<<" "<<p.y<<" "<<p.z<<'\n';
    std::cout<<'\n';
    
    ifs.close();
    return 0;
}
