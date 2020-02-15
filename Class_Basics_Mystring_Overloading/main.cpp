#include <iostream>
#include "Mystring.hpp"
#include "MystringUp.hpp"

int main()
{
    Mystring empty_str{"salim"};
    empty_str.display();
    
    std::cout<<empty_str<<'\n';
    
// test for insertion operator overloading std::cin>>
//    std::cout<<"Please enter a name: ";
//    Mystring entr_name;
//    std::cin>>entr_name;
//    std::cout<<entr_name<<'\n';
    
    
    //unique ptr version
    MystringUp up_str{"pamukcu fwfwefwefw dwedsdsds"};
    up_str.display();
    
    MystringUp up_st2{up_str};
    up_st2.display();
    
    std::cout<<up_st2.get_length()<<'\n';
    
    // move assignment for raw pointer version
    empty_str="Demir";
    empty_str.display();
    
    // copy assignment
    Mystring empty_str2;
    empty_str2=empty_str;
    empty_str2.display();
    
    // move assignment
    Mystring empty_str3;
    empty_str3 = Mystring{"SemoSSS"};
    empty_str3.display();
    
//    empty_str3=-empty_str3;
//    empty_str3.display();

    //std::cout<<"Lower case (SALOOO): "<<-Mystring{"SALOOOOOO"}<<'\n';
    
    std::cout<<std::boolalpha<<(empty_str3==Mystring{"SemoSSS"})<<'\n';
    
    std::cout<<std::boolalpha<<(empty_str3!=-Mystring{"SemoSSS"})<<'\n';
    
    std::cout<<empty_str3<<" < "<<empty_str2<<": "
             <<std::boolalpha<<(empty_str3<empty_str2)<<'\n';
             
    std::cout<<empty_str3<<" > "<<empty_str2<<": "
             <<std::boolalpha<<(empty_str3>empty_str2)<<'\n';
    
    empty_str3=empty_str3+" pamukcu";
    empty_str3.display();
    
    empty_str3+=" Family";
    empty_str3.display();
    
    std::cout<<(empty_str++)*3<<'\n';
    empty_str.display();
    
    empty_str*=2;
    empty_str.display();
    
    
    
    
//    empty_str3="Family of: "+ empty_str3;         // error; because overlaoding as a member
                                                    // function will require Mystring variable
                                                    // but we can use overload as non friend operator with two 
                                                    // arguments being c-style strings or any of the options will work
                                                
    
    empty_str3=Mystring{"Family of: "}+empty_str3;  // or we can use in place constructor and create temp object for the first argument
                                                    // passing c-string; first constructor create a temp object and process overloaded object
    empty_str3.display();                            // for that temp object when we need to copy the value into the buffer move constructor moves it
                                                     // into buffer and the is nulled then we the rest of the concentate
    
    return 0;
}
