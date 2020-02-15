#include "Mystring.hpp"
#include <cstring>
#include <cctype>
#include <algorithm>
#include <functional>
#include <iterator>

    // no arg constructor
    Mystring::Mystring(): str{new char[1]} {*str='\0';}
    
    // constructor
    Mystring::Mystring(const char* s):str{nullptr} {
        if (s==nullptr) {
            str=new char[1];
            *str='\0';
        } else
        str=new char[std::strlen(s)+1];
        std::memcpy(str, s, std::strlen(s)+1);           // std::memcpy is faster than strcpy but use with caution 
        std::cout<<"Constructor working...\n";
      //  std::strcpy(str, s);                            
    }
                                    
    
    // copy constructor; deep copy
    Mystring::Mystring(const Mystring& source):str{nullptr}{
            str=new char[std::strlen(source.str)+1];
            std::memcpy(str, source.str, strlen(source.str)+1);
            std::cout<<"Copy Constructor working...\n";
            // std::strcpy(str, s);
        }
    
    // Move constructor
    Mystring::Mystring(Mystring&& source):str{source.str} {
            source.str=nullptr;
            std::cout<<"Move Constructor working...\n";
            }
    
    Mystring& Mystring::operator=(const Mystring& rhs) {
        if(this==&rhs) return *this;
        delete [] str;
        str=new char[std::strlen(rhs.str)+1];
        std::memcpy(str, rhs.str, std::strlen(rhs.str)+1 );
   //   std::strcpy(str, rhs.str);
        std::cout<<"Copy Assignment working...\n";
        return *this;
    }
    
    Mystring& Mystring::operator=(Mystring&& rhs) {
        if(this==&rhs) return *this;
        delete [] str;
        str=rhs.str;
        rhs.str=nullptr;
        std::cout<<"Move Assignment working...\n";
        return *this;
    }
    
    // destructor
    Mystring::~Mystring() { 
        std::cout<<"destructor for: "<<(str!=nullptr ? str: "nullptr")<<'\n';    
        delete[] str;}
    
    // getters
    void Mystring::display() const {std::cout<<str<<'\n';}
    int Mystring::get_length() const { return std::strlen(str);}
    const char* Mystring::get_string() const { return str;}
    
    // Overloaded operator-; that convert a copy Mystring into lower case
    // and returns a copy of it
    Mystring Mystring::operator-() const {
        char *buffer=new char[std::strlen(str)+1];                  // better to use a shared pointer or even a unie_ptr
        std::memcpy(buffer, str, strlen(str)+1);
//        std::for_each(&buffer[0], (&buffer[0]+std::strlen(buffer)), // Alternative using raw pointer version  
//                [](auto& c){ c=std::tolower(c); } );                // with STL algoritms; it is important to use reference when
                                                            // STL version might come handy if parallel execution policy or upcoming
                                                                      // C++20 ranges to combine several algorithms to have advanced features easier
        for(std::size_t i{0}; i<std::strlen(buffer); ++i)
            buffer[i]=std::tolower(buffer[i]);
        Mystring temp{buffer};
        delete [] buffer;
        return temp;                    // better to use a shared or unique pointer and a return with a Class constructor
    }                                     // rather than a Mystring variable because if return an r-value we will avoid extra copying
                                        // return value optimization might not occur
                                        
    bool Mystring::operator==(const Mystring& rhs) const {
         return (std::strcmp(str, rhs.str)==0);
    } 
    
    bool Mystring::operator!=(const Mystring& rhs) const {
        return !(std::strcmp(str, rhs.str)==0);
    }
    
    bool Mystring::operator<(const Mystring& rhs) const {
         return (std::strcmp(str, rhs.str)<0);
    }
    
    bool Mystring::operator>(const Mystring& rhs) const{
        return (std::strcmp(str, rhs.str)>0);
    }
    
//    bool operator==(const Mystring& lhs, const Mystring& rhs ){
//        if(std::strcmp(lhs.str, rhs.str)==0) 
//            return true;
//        return false;
//    }
      
    Mystring Mystring::operator+(const Mystring& rhs) const {
        char * buffer=new char[std::strlen(str)+std::strlen(rhs.str)+1];
        std::memcpy(buffer, str, std::strlen(str));                               // copy the original into empty buffer
        std::memcpy(buffer+std::strlen(str), rhs.str, std::strlen(rhs.str)+1);    // copy the other string into buffer to end of first string;  at the position starting   
                                                                                 // if the size is not enough, the copying fails; use with caution
//        std::strcat(buffer, str);                                              // strcat is a slower but easier to use                                             
//        std::strcat(buffer, rhs.str);
        Mystring temp{buffer};
        delete[] buffer;
        return temp;
    }
    
    Mystring& Mystring::operator+=(const Mystring&rhs) {
        *this=*this+rhs;
        return *this;
    }
    
    // pre-increment
    Mystring& Mystring::operator++() {
        *this+=*this;
        return *this;            // you return a temp value; no need to create 
                                           // a temp object and return object; return type is value
    }              
   
    // post-increment 
    Mystring Mystring::operator++(int) {
        Mystring old_value{*this};
     //  ++(*this);                       // alternative way to call pre-increment overload to update
        *this+=*this;                     // we return the temp object because we need to store the old vaue
        return old_value;                 // and return old value 
    }                                        
    
    Mystring Mystring::operator*(int n) const {
        Mystring temp;
        for(int i{0}; i<n; ++i)
            temp+=*this;
        return temp;
    }
    
     Mystring& Mystring::operator*=(int n) {
        *this=*this*n;
        return *this;
    }


