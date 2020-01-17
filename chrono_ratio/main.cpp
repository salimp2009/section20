#include <iostream>
#include <chrono>
#include <ratio>




int main()
{
    
    typedef std::ratio<5,3> Five_Thirds;                            // creating an alias for 5/3 ratio  by using typedef        
                                                        
    std::cout<<Five_Thirds::num<<"/"<<Five_Thirds::den<<'\n';       // num and den stands for numerator/denumerator of ratio
                                        
    std::ratio<42, 42> one;
    std::cout<<one.num<<"/"<<one.den<<'\n';
    
    std::ratio<0>zero;
    std::cout<<zero.num<<"/"<<zero.den<<'\n';
    
    using Alt_Five_Thirds=std::ratio<25,15>;
    std::cout<<Alt_Five_Thirds::num<<"/"<<Alt_Five_Thirds::den<<'\n';       // the output is 5/3

    Alt_Five_Thirds five_thirds_object;                                     // creating an object of type Alt_Five_Thirds
    std::cout<<five_thirds_object.num<<"/"<<five_thirds_object.den<<'\n';   // which is actually ratio<5, 3>
    
    typedef std::ratio<7, -3>Neg;
    std::cout<<Neg::num<<'/'<<"/"<<Neg::den<<'\n';                          // output is -7/3
    
    
    
    
    
    return 0;
}
