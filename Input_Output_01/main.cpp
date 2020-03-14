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
     ifs.clear();                   // clear all the flags
     
    // NO MORE VALID ...the below ifs.seekg(0) worked ; no need to close and open again
    // just clear all the flags; ifs.clear() and go to the begining or where you want to by ifs.seekg(position)
    
    
    // ifs.close();                // close the file; if you want to re_read the file without closing
                                 //it will read from where it is left therefore it will be the end of file
                                 //the best way to do each reading operation in seperate functions 
    // ifs.open(input_file);       // becaus then the file ifs closes and goes out of scope and you start fresh  
    
    
    // go to begining
    ifs.seekg(0);
    
    // redirect the input file buffer to another stream; e.g std::cout
    std::cout<<ifs.rdbuf()<<'\n';
    
    // go to end; alternative way you go to a position relative to a defined position; beg, end, cur
    ifs.seekg(0, std::ios::end);
    
    //tellg() returns the current position
    std::cout<<"position at opening: "<<ifs.tellg()<<'\n';
    
    // go to beginning of file
    // you can specify any position other than zero relative to begin position
    
    ifs.seekg(0, std::ios::beg);
    std::cout<<"go to beginning: "<<ifs.tellg()<<'\n';
    
    // another alnternative to pass only position than it will be relative to current position
    ifs.seekg(7);
    std::cout<<"position at: "<<ifs.tellg()<<'\n';
    
    ifs.seekg(0, std::ios::beg);
    std::vector<int>pnts_2;
    int x{}, y{}, z{};


    for(;ifs>>x>>y>>z;) {
        pnts_2.push_back(x);
        pnts_2.push_back(y);
        pnts_2.push_back(z);
    }
    
    for(const auto& p:pnts_2)
        std::cout<<p<<" ";
    std::cout<<'\n';
    
    for(const auto& p:pnts)
        std::cout<<p.x<<" "<<p.y<<" "<<p.z<<'\n';
    
    ifs.close();
    return 0;
}
