#include <iostream>
#include "Utility.hpp"

int main()
{
    
    std::vector vec{1,2,3,4,5,1,2,1};
    display(vec);
    
    std::replace(vec.begin(), vec.end(), 1, 100);
    display(vec); 
    
    std::string s1{"this is a tesT"};
    std::transform(s1.begin(), s1.end(),
                    s1.begin(), ::toupper);
    std::cout<<"after the transform s1: "<<s1<<'\n';

    return 0;
}
