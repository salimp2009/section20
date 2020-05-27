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
    
    
    
    //std::cout<<fs::current_path().string()<<":\n";
    
    //std::filesystem::path p{argv[1]};   // p is the file system path; check if exists !!
    std::filesystem::path p{"../../FileSystem_Path_Basics"};
    if(is_regular_file(p))
    {
        std::printf("%s exists with %0.2ju bytes\n", p.string().c_str(), file_size(p));
    }
    
    else if (is_directory(p))
    {
        std::cout<<p<< " is a directory containing: \n";
        //for(const auto&e : fs::directory_iterator{p})
        for(const auto&e : fs::recursive_directory_iterator{p})
        {
            std::cout<<" "<<e.path().extension()
            <<'\n';
            // std::cout<<"\t\t "<<e.path().filename()<<'\n';
            //std::cout<<"\t\t "<<e.path().filename().string()<<'\n';           // alternative way to print; no quotation marks
//            if(is_directory(e.path())) 
//            {
//                std::cout<<e.path()<< " is a directory containing: \n";
//                for(const auto& n: fs::directory_iterator{e.path()})
//                {
//                    std::cout<<"\t\t "<<n.path().filename()<<'\n';              // prints the filename with the quotation marks (" ")
//                    //std::cout<<"\t\t "<<n.path().string()<<'\n';                // alternative; prints the full path with the name of the filename and extension
//                }
//            }
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
