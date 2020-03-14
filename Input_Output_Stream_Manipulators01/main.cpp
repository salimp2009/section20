#include <iostream>
#include <ios>
#include <iomanip>
#include <bitset>
#include <string>

int main()
{
    // Example for Bool variable format
    // using cout object method setf() to boolalpha
    // this method sticks unless you change it thru setf() method
    std::cout.setf(std::ios::boolalpha);
    std::cout<<"10==20 : "<<(10==20)<<'\n';
    
    std::cout<<"10==10 : "<<(10==10)<<'\n';
    
    // reset an alternative way
    std::cout<<std::resetiosflags(std::ios::boolalpha);
    std::cout<<"10==10 : "<<(10==10)<<'\n';
    
    //std::cout<<"10==20 : "<<std::boolalpha<<(10==20)<<'\n';
    
    // Example for integers
    int num{255};
    
    std::cout<<std::showbase;
    std::cout<<"dec: "<<std::dec<<num<<'\n';
    std::cout<<"hex: "<<std::hex<<num<<'\n';
    std::cout<<"oct: "<<std::oct<<num<<'\n';
    std::cout<<"bitset<10>: "<<std::bitset<10>(num)<<'\n';
    std::cout<<std::noshowbase;
    
    // reset to defaults
    std::cout<<std::resetiosflags(std::ios::basefield | std::ios::showbase);
    
    std::cout<<num<<'\n';
    
    // Examples for floating numbers;
    // default 6 digits total and rounding occurs
    // but in the background it has the following digits therefore comparing floating
    // numbers an error margin should be used ; the smallest error margin is the machine
    // epsilon is the minimum number that will make a+epsilon>a
    // if any number smaller than epsilon is added it will still show equal
    double num2{1234.5678};
    std::cout<<num2<<'\n';   // displays 1234.57 
    double num3=1234.57;
    
    std::cout<<std::boolalpha<<"num2==num3: "<<(num2==num3)<<'\n';  // display false

    auto Myepsilon=std::numeric_limits<double>::epsilon();
    
    // fixed format
    std::cout<<std::fixed<<num2<<'\n';  // precision will be 6 numbers after the digit by default
    std::cout<<std::fixed<<num3<<'\n';
    std::cout<<std::fixed<<std::setprecision(20)<<Myepsilon<<'\n'; // precision will be 20 numbers after the digits
    
    // scientific format
    std::cout<<std::scientific<<num2<<'\n';  // precision will be 6 numbers after the digit by default
    std::cout<<std::scientific<<num3<<'\n';
    
    std::cout<<std::scientific<<std::setprecision(3)<<num2<<'\n';  // precision will be 3 numbers after the digit by default
    std::cout<<std::scientific<<std::setprecision(3)<<num3<<'\n';   // displays 1.235e+3 for both numbers    
    
    // reset to defaults
    std::cout.unsetf(std::ios::scientific|std::ios::fixed); 
    std::cout<<std::setprecision(6);
    
    std::cout<<num2<<'\n';  
    std::cout<<num3<<'\n';
    
    //setw, align, fill manipulators
    
    std::string hello{"Hello"};
    
    // setw will apply to next data which is num; it does not apply to hello
    // the default alignment is right justified
    // if setw() is not defined the default is left justified
    std::cout<<std::setw(10)<<num<<hello<<'\n';
    
    std::cout<<std::setw(10)<<num
             <<std::setw(10)<<hello
             <<std::setw(10)<<"hello"<<'\n';
     
    // only first items effected setw() but this time it left justified
    // it only effects the next data item only
    std::cout<<std::setw(10)<<std::left<<num
                                        <<hello<<'\n';
    // setw() or std::left does not stick;
    // defaults will apply below 
    std::cout<<num<<hello<<'\n';
    
    // setfill() applies all the following data and should be followed with setw()
    // and it sticks to the rest of the program
     std::cout<<std::setfill('-')
            <<std::setw(10)<<std::left<<num
            <<std::setw(10)<<hello<<'\n';
    // reset the setfill() with a blank
    //std::cout<<std::setfill(' ');
    std::cout<<std::setw(10)<<std::left<<num<<hello<<'\n';
    s
    std::cout<<std::left<<num<<hello<<'\n';
                                
    return 0;
}
