#include "MystringUp.hpp"
#include <cstring>

    // no arg constructor
    MystringUp::MystringUp():str{std::make_unique<char[]>(1)} {str[0]='\0';}
    
    // constructor
    MystringUp::MystringUp(const char* s):str{nullptr} {
        if (s==nullptr) {
            str=std::make_unique<char[]>(1);
            str[0]='\0';
        } else
        
        str=std::make_unique<char[]>(std::strlen(s)+1);
        std::memcpy(str.get(), s, std::strlen(s)+1);           // std::memcpy is faster than strcpy but use with caution 
    }
                                    
    
    // copy constructor; deep copy
    MystringUp::MystringUp(const MystringUp& source):str{nullptr}{
            str=std::make_unique<char[]>(std::strlen(source.str.get())+1);
            
          std::memcpy(str.get(), source.str.get(), std::strlen(source.str.get())+1);   
//        std::strcpy(str.get(), source.str.get());
        }
    
    // Move constructor
    MystringUp::MystringUp(MystringUp&& source):str{std::move(source.str)} {
                    source.str=nullptr;
            }
    
    // destructor
    // MystringUp::~MystringUp() { delete[] str;}
    
    // getterss
    void MystringUp::display() const { std::cout<<str.get()<<'\n';}
    int MystringUp::get_length() const { return std::strlen(str.get());}
    const char* MystringUp::get_string() const {return str.get();}

