#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

int main()
{
    int num{0};
    double total{0};
    std::string name{0};
    std::string info{"Moe 100 1234.5"};
    
    std::istringstream iss{info};       // connect the string stream to object
    iss>>name>>num>>total;              // read / exctract the contents from string stream into variable (like reading from file)
    std::cout<<iss.str()<<'\n';         // access the data in the string stream buffer
    
    std::cout<<name<<","<<num<<", "<<total<<'\n';
    
    //output string stream example
    
    // create a output string stream object (just like ostream)
    std::ostringstream oss{};
   
    // write the data from variables into oss just like writing to file
    oss<<"output from oss: "<<name<<'\t'<<num<<std::setw(10)<<std::right<<total<<'\n';  
    
    // access the data in the oss buffer and direct it to cout(console) to print out
    std::cout<<oss.str()<<'\n';   


    // data validation using string stream
    // alternative way is to use std::from_chars() that came with c++17
    // or type traits std::integral can be used by using templated function
    int value{0};
    std::string entry{};
    bool done{false};
    do {
        std::cout<<"please enter an integer: ";
        std::cin>>entry;
        std::istringstream validator{entry};
        if(validator>>value) {
            done=true;
        std::cout<<"you entered: "<<value<<'\n';
        }
        else
            std::cout<<"Sorry not a valid integer..please try again!!!\n";
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        
    } while(!done);

    return 0;
}
