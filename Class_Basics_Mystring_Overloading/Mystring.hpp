#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <iostream>
#include <memory>

class Mystring
{
    // alternative version operator==() as a friend
//    friend bool operator==(const Mystring& lhs, const Mystring& rhs );
   
    friend std::ostream& operator<<(std::ostream& os, const Mystring& obj) {
        os<<obj.str;
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Mystring& obj) {
      //  char *buffer=new char[1000];      // alternative we can store it in a buffer to do some checking before storing
        is>>obj.str;            // reading directly to object private data; no extra constructor or move/ copy assignments
       // obj=buffer;           // same as below both uses Move assignmet if there is one if not then copy assignmetn
       // obj=Mystring{buffer};
       // delete[] buffer;      // better to use smart pointer here
        return is;
    }
    
private:
    char* str;                          // pointer to C-style string char[]
//    std::unique_ptr<char[]> str;
public:
    Mystring();
    Mystring(const char* s);
    Mystring(const Mystring& source);
    Mystring(Mystring&& source);
    
    Mystring& operator=(const Mystring& rhs);
    Mystring& operator=(Mystring&& rhs);
    
    ~Mystring();
    
    // Overload operator -; that convert a copy Mystring into lower case
    // and returns a copy of it
    Mystring operator-() const;
    
    // overloaded + to concatenate ; note the left side must be a Mystring class
    // to overcome we can overloade + operator as non-member function
    // operator +(const Class& rhs); unary operators will get   
    Mystring operator+(const Mystring& rhs) const;      // value of lhs object does not change
    Mystring& operator+=(const Mystring&rhs);           // value of lhs object changes
    
    Mystring& operator++();              // pre-increment
    Mystring operator++(int);           // post-increment
    
    Mystring operator*(int n) const;          // string copied n times; return value; value of lhs does not change
    Mystring& operator*=(int n);         // string copied n times; return refence; value of lhs changes
    
    bool operator==(const Mystring& rhs) const;
    bool operator!=(const Mystring& rhs) const;
    bool operator<(const Mystring& rhs) const;
    bool operator>(const Mystring& rhs) const;
    
    
    
    void display() const;
    int get_length() const;
    const char* get_string() const;
   
};

#endif // _MYSTRING_H_
