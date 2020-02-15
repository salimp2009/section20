#ifndef _MYSTRING_UP_H
#define _MYSTRING_UP_H

#include <iostream>
#include <memory>

class MystringUp
{
private:
 //   char* str;          // pointer to C-style string char[]
    std::unique_ptr<char[]> str;
public:
    MystringUp();
    MystringUp(const char* s);
    MystringUp(const MystringUp& source);
    MystringUp(MystringUp&& source);
//    ~MystringUp();
    
    void display() const;
    int get_length() const;
    const char* get_string() const;
   
};



#endif // _MYSTRING_UP_H
