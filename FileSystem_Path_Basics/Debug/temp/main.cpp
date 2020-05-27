#include <iostream>
#include <filesystem>
#include <cstdlib>              // for EXIT_FAILURE macro

namespace fs =std::filesystem;
int main(int argc, char* argv[])
{
    
    if(argc <2) 
    {
        std::printf("Usage: %s <path> \n", argv[0]);
        return EXIT_FAILURE;
    }
    
    std::filesystem::path p{argv[1]};   // p is the file system path; check if exists !!
    if(is_regular_file(p))
    {
        std::printf("%s exists with %0.2ju bytes\n", p.string().c_str(), file_size(p));
    }
    
    else if (is_directory(p))
    {
        std::cout<<p<< " is a directory containing: \n";
        for(const auto&e : fs::directory_iterator{p})
        {
            std::cout<<" "<<e.path()<<'\n';
        }
    }
    
    else if(exists(p))
    {
        std::cout<<p<<" is a special file\n";
    }
    else
    {
        std::cout<<"path "<<p<<" does not exist\n";
    }
    return 0;
}
