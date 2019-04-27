#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Example for using variadic arguments... 
// and implement a string conversion; all the arguments passes converted to a string

template<typename T>
std::string to_string_impl(const T& t)           // converts the argument into string 
{
    std::stringstream ss;
    ss<<t; 
    return ss.str();                             // str() returns a copy of the string stored in string object
}


template<typename...Param>
std::vector<std::string> to_string(const Param&...param)  // two parameters defined to make sure there is at least one parameter
{
    
    return {to_string_impl(param)...};             // the parameters will be sent to funct and will get back as a string
                                                   // once all the parameters are converted , a list of strings will be
                                                   // returned although the return type is vector we are just returning a list
}

int main()
{
    const auto vec=to_string("hello", 1, 5.3, 25, 67);   // input to be converted to string
    
    for(const auto& v:vec)                               // print the result from container; vec
        std::cout<<v<<'\n';

 return 0;
}