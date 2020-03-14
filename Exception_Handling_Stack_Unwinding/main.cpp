#include <iostream>

// Basic example to see the effect of throwing and exception
// on the stack
// below example function throw an exception
// calling function a catches
// funct b finished abnormally function a catches it and finishes and main finishes
// function c never starts because function b throws before function c is called
// so the whole thing will seem to work with excetion warnings
// however since function c is never called and since function is not completed 
// the result will be wrong !!! so pay attention to exception and all warnings
// that is why when compiling during debug all warning should be on and ciritical
// assert might be used instead of exception which can be turned off with a macro for a release version
// assert and macro combination is a better choice for most games and game engines and 
// critical software for planes...etc


void func_c(){
    std::cout<<"Starting function c....\n";
    
    std::cout<<"Finishing function c....\n";
}

void func_b(){
    std::cout<<"Starting function b....\n";
    throw 100;
    func_c();
    std::cout<<"Finishing function b....\n";
}

void func_a(){
     std::cout<<"Starting function a....\n";
    try {
    func_b();
    } catch(int& ex) {
        std::cerr<<"Error:"<<ex<<'\n';
    }
    std::cout<<"Finishing function a....\n";
}

int main()
{
    std::cout<<"Starting main....\n";
    func_a();
    std::cout<<"Finishing main....\n";

    return 0;
}
