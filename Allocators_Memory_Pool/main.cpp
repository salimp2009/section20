#include <iostream>
#include "GAllocator.hpp"
#include "StackMemoryPool.hpp"
#include "StackAllocator.hpp"
#include <vector>
#include <string>
#include <filesystem>


std::size_t totalAllocatedSize{0};

struct Foo
{
  Foo(int value):mvalue{value} { }  
  int mvalue;      
};

int main()
{
    // Example to test filesytem works on Mac; and it works :)
    namespace fs=std::filesystem;
    fs::path testDir{"../tmp/test"};  // define a path (may not exist yet) ../ is specific to Codelight 
                                      // to create the directory under where main is 
                                      //otherwise it is in Debug or Release folder since the exe file is created there
    create_directories(testDir);      // create a directory or directories ; 
                                      // Note both functions one works for single directory the other multiple
                    
    
    
    // Example for GAllocator ; detailed standart STL Allocator
    std::vector<Foo, GAllocator<Foo>>vec;
    vec.resize(10, Foo{25});
    
    printf("Total Allocated Size= %lu\n", totalAllocatedSize);
    
    // Example for Memory Pool with a userdefined Allocator and STL compatible (use false for STL containers)
    StackAllocator<char, false>alloc(256); // false is needed for STL container since they try to allocate on heap on every add , move, copy 
    typedef std::basic_string<char, std::char_traits<char>, StackAllocator<char, false>> Str;
    
    Str str(alloc);
    
    str="lalalala";
    str="lalalalaloooooooooooooooooooooooooooooooooooooooooooooooooooooo";
    
    
    return 0;
}
