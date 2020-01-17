#include <iostream>
#include "Assert.hpp"

#define DEBUG

int main()
{
    
    int a {-1};
      
    
    if(a<5) {
   // assert(a>=0);
    ASSERT(a<=0);
    }
    else 
    
        std::cout<<"a: "<<a<<'\n';
        
 return 0;
}
