#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <iomanip>



int main()
{
    int num{};
    double total{};
    std::string name{};
    
    
    std::string info{"Salim      100      1234.5"};     // put info into a string
    
   
    std::istringstream iss(info);                      // create input string stream object and pass the string info
    
    iss>>name>>num>>total;                            // exctract the variables from the string stream object
    
    std::cout<<"\n=============Inputstring Stream=================\n";
    std::cout<<std::setw(10)<<std::left<<name        // print the results
             <<std::setw(5)<<num
             <<std::setw(10)<<total<<'\n';
             
    
    std::cout<<"\n=============Outputstring Stream=================\n";
    
    std::ostringstream oss{};                  // create output string stream object oss
    
    oss<<std::setw(10)<<std::left<<name        // input the variable into outputstring
       <<std::setw(5)<<num
       <<std::setw(10)<<total<<'\n';
       
    std::cout<<oss.str()<<'\n';               // send the value in output string buffer oss.str() to console (std::cout)
    
    std::cout<<"\n===============Data Validation================\n";
    // the idea; 
    std::string entry{};
    int value{};
    bool done{false};
    
    do {
        std::cout<<"\nPlease enter an integer: "; // ask for an integer
        std::cin>>entry;                          // input into a string to check if it is a valid integer
        std::istringstream validator{entry};      // create input string stream object and pass the input string to verify
        if(validator>>value)  {                    // extract   the value from string stream object into integer variable
            done=true;                            // if the input value is a valid integer the expression becomes true 
        }                                          // set bool to true to get out of the loop
        else 
            std::cout<<"\nNot an integer...\n";   // if the value is not a valid integer warn the user and keep asking
        
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');    // if a value of 12.38 is entered then 12 will be read as integer but .38 will sit in the buffer
                                                                              // to clear the buffer, we ignore left overs from cin buffer all the way upto a newline
                                                                             // std::numeric_limits<std::streamsize>::max is used to make sure
                                                                            // all the left of the stream is ignored; streamsize is platform dependant therefore
    } while(!done);                                                         // we are using the std::numeric_limits<std::streamsize>::max 
    
    std::cout<<"\nYou entered a valid integer: "<<value<<'\n';
    
 return 0;
}
